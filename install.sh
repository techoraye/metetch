#!/bin/bash

# ============================================================================
# Metetch Installation Script
# Copyright (c) 2025 techoraye - All Rights Reserved
# Licensed under METETCH PROPRIETARY LICENSE
# This software and source code are proprietary to techoraye.
# See LICENSE file for details
# ============================================================================

set -e

# Check if running with sudo
if [ "$EUID" -ne 0 ]; then 
    echo -e "\033[0;31m✗\033[0m This script must be run with sudo"
    echo -e "\033[0;34mℹ\033[0m Run: sudo $0"
    exit 1
fi

# ============================================================================
# Colors - Synchronized with include/colors.h
# ============================================================================
# Standard colors (from colors.h BOLD variants)
RED='\033[0;31m'          # STATUS_CRIT color
GREEN='\033[0;32m'        # STATUS_OK variant
YELLOW='\033[1;33m'       # BOLD_YELLOW - used for emphasis
BLUE='\033[0;34m'         # Blue standard
CYAN='\033[1;36m'         # Bold cyan
MAGENTA='\033[1;35m'      # Bold magenta
WHITE='\033[1;37m'        # Bold white
NC='\033[0m'              # No Color (RESET)

# Configuration
INSTALL_DIR="/usr/local/bin"
# Get the actual user's home directory (not root's)
ACTUAL_USER="${SUDO_USER:-$USER}"
ACTUAL_HOME=$(getent passwd "$ACTUAL_USER" | cut -d: -f6)
CONFIG_DIR="$ACTUAL_HOME/.config/metetch"
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$PROJECT_DIR/build"
BINARY_NAME="metetch"
VERSION="0.5.3"

# Functions
print_header() {
    echo -e "${BLUE}╔════════════════════════════════════════╗${NC}"
    echo -e "${BLUE}║${NC}     ${YELLOW}⚡ METETCH INSTALLATION SCRIPT ⚡${NC}     ${BLUE}║${NC}"
    echo -e "${BLUE}╚════════════════════════════════════════╝${NC}"
}

print_info() {
    echo -e "${BLUE}ℹ${NC} $1"
}

print_success() {
    echo -e "${GREEN}✓${NC} $1"
}

print_error() {
    echo -e "${RED}✗${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}⚠${NC} $1"
}

detect_distro() {
    # Detect if running inside a Flatpak sandbox
    if [ -n "$FLATPAK_ID" ] || [ -f "/.flatpak-info" ]; then
        echo "flatpak"
        return
    fi
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        echo "${ID}"
    elif command -v lsb_release &> /dev/null; then
        lsb_release -si | tr '[:upper:]' '[:lower:]'
    elif [ -f /etc/lsb-release ]; then
        . /etc/lsb-release
        echo "${DISTRIB_ID}" | tr '[:upper:]' '[:lower:]'
    else
        echo "unknown"
    fi
}

install_dependencies() {
    local distro=$(detect_distro)
    
    print_info "Detected distro: ${distro}"
    print_info "Installing required dependencies..."
    echo ""
    
    print_info "Detecting package manager and installing dependencies..."

    detect_pkg_manager() {
        if command -v apt-get &> /dev/null; then echo "apt"; return; fi
        if command -v pacman &> /dev/null; then echo "pacman"; return; fi
        if command -v dnf &> /dev/null; then echo "dnf"; return; fi
        if command -v yum &> /dev/null; then echo "yum"; return; fi
        if command -v zypper &> /dev/null; then echo "zypper"; return; fi
        if command -v apk &> /dev/null; then echo "apk"; return; fi
        if command -v xbps-install &> /dev/null; then echo "xbps"; return; fi
        if command -v emerge &> /dev/null; then echo "emerge"; return; fi
        if command -v eopkg &> /dev/null; then echo "eopkg"; return; fi
        if command -v pkg &> /dev/null; then echo "pkg"; return; fi
        echo "unknown"
    }

    pm=$(detect_pkg_manager)
    print_info "Detected package manager: ${pm}"

    # Define generic package names we need for building
    # build tools, cmake, curl/libcurl, ncurses/dev, pkg-config
    case "$pm" in
        apt)
            apt-get update > /dev/null 2>&1 || true
            apt-get install -y build-essential cmake libcurl4-openssl-dev libncurses-dev libtinfo-dev pkg-config
            ;;
        pacman)
            pacman -Sy --noconfirm base-devel cmake curl ncurses pkgconf
            ;;
        dnf)
            dnf install -y @development-tools cmake libcurl-devel ncurses-devel pkgconfig 2>/dev/null || \
            dnf install -y gcc-c++ cmake libcurl-devel ncurses-devel pkg-config
            ;;
        yum)
            yum install -y gcc-c++ cmake libcurl-devel ncurses-devel pkg-config
            ;;
        zypper)
            zypper install -y gcc-c++ cmake libcurl-devel ncurses-devel pkg-config
            ;;
        apk)
            apk add --no-cache build-base cmake curl-dev ncurses-dev linux-headers pkgconfig
            ;;
        xbps)
            xbps-install -Sy base-devel cmake curl-devel ncurses-devel pkg-config
            ;;
        emerge)
            emerge --sync > /dev/null 2>&1 || true
            emerge -qv dev-build/cmake net-misc/curl sys-libs/ncurses
            ;;
        eopkg)
            eopkg install -y cmake curl-devel ncurses-devel pkgconfig || true
            ;;
        pkg)
            pkg install -y gcc cmake curl ncurses pkgconf || true
            ;;
        *)
            print_warning "Unknown package manager: ${pm}"
            print_warning "Attempting to use known installers if available..."
            if command -v apt-get &> /dev/null; then
                apt-get update && apt-get install -y build-essential cmake libcurl4-openssl-dev libncurses-dev libtinfo-dev pkg-config
            elif command -v pacman &> /dev/null; then
                pacman -Sy --noconfirm base-devel cmake curl ncurses pkgconf
            elif command -v dnf &> /dev/null; then
                dnf install -y gcc-c++ cmake libcurl-devel ncurses-devel pkg-config
            elif command -v zypper &> /dev/null; then
                zypper install -y gcc-c++ cmake libcurl-devel ncurses-devel pkg-config
            else
                print_error "Could not detect package manager. Please install the following packages manually: build tools, cmake, libcurl-dev, ncurses-dev, pkg-config"
                exit 1
            fi
            ;;
    esac

    print_success "Dependencies installed (or attempted)."
}

check_dependencies() {
    print_info "Checking dependencies..."
    echo ""
    
    local missing=0
    local missing_list=""
    
    # Check for build essentials
    if ! command -v g++ &> /dev/null; then
        missing=1
        missing_list="${missing_list}  - g++\n"
    else
        print_success "g++ found"
    fi
    
    if ! command -v cmake &> /dev/null; then
        missing=1
        missing_list="${missing_list}  - cmake\n"
    else
        print_success "cmake found"
    fi
    
    if ! pkg-config --exists libcurl 2>/dev/null; then
        missing=1
        missing_list="${missing_list}  - libcurl development files\n"
    else
        print_success "libcurl found"
    fi
    
    if ! pkg-config --exists ncurses 2>/dev/null; then
        missing=1
        missing_list="${missing_list}  - ncurses development files\n"
    else
        print_success "ncurses found"
    fi
    
    if [ $missing -eq 1 ]; then
        print_warning "Missing dependencies:"
        echo -e "$missing_list"
        install_dependencies
    else
        print_success "All dependencies found"
    fi
}

build_project() {
    print_info "Building Metetch v${VERSION}..."
    
    # Clean build - use a temporary directory to avoid permission issues
    TMP_BUILD="/tmp/metetch_build_$$"
    mkdir -p "$TMP_BUILD"
    
    print_info "Setting up build environment..."
    
    # Check if source files exist
    if [ ! -d "$PROJECT_DIR/src" ] || [ ! -d "$PROJECT_DIR/include" ] || [ ! -f "$PROJECT_DIR/CMakeLists.txt" ]; then
        print_error "Source files not found! Please ensure src/, include/, and CMakeLists.txt exist in $PROJECT_DIR"
        rm -rf "$TMP_BUILD"
        exit 1
    fi
    
    cp -r "$PROJECT_DIR"/{src,include,CMakeLists.txt} "$TMP_BUILD/" 2>/dev/null || {
        print_error "Failed to copy source files!"
        rm -rf "$TMP_BUILD"
        exit 1
    }
    
    mkdir -p "$TMP_BUILD/build"
    cd "$TMP_BUILD/build"
    
    print_info "Configuring with CMake..."
    if ! cmake .. > /dev/null 2>&1; then
        print_error "CMake configuration failed!"
        print_info "Running cmake with verbose output for debugging:"
        cmake ..
        rm -rf "$TMP_BUILD"
        exit 1
    fi
    
    print_info "Compiling (using $(nproc) cores)..."
    if ! make -j$(nproc) > /dev/null 2>&1; then
        print_error "Build failed!"
        print_info "Running make with verbose output for debugging:"
        make VERBOSE=1
        rm -rf "$TMP_BUILD"
        exit 1
    fi
    
    if [ -f "$TMP_BUILD/build/$BINARY_NAME" ]; then
        print_success "Build completed successfully"
        # Copy back to project build directory
        mkdir -p "$BUILD_DIR"
        cp "$TMP_BUILD/build/$BINARY_NAME" "$BUILD_DIR/$BINARY_NAME" 2>/dev/null || {
            cp "$TMP_BUILD/build/$BINARY_NAME" "/tmp/metetch_binary_$$"
        }
        BUILD_BINARY="${BUILD_DIR}/${BINARY_NAME}"
        if [ ! -f "$BUILD_BINARY" ]; then
            BUILD_BINARY="/tmp/metetch_binary_$$"
        fi
        # Cleanup temp build directory
        rm -rf "$TMP_BUILD"
    else
        print_error "Build failed - binary not found!"
        rm -rf "$TMP_BUILD"
        exit 1
    fi
}

install_binary() {
    print_info "Installing binary to $INSTALL_DIR..."
    
    # Use the binary from wherever it was built
    BINARY_SOURCE="${BUILD_BINARY:-$BUILD_DIR/$BINARY_NAME}"
    
    if [ ! -f "$BINARY_SOURCE" ]; then
        print_error "Binary not found at $BINARY_SOURCE"
        exit 1
    fi
    
    # Copy binary (script is running as root)
    cp "$BINARY_SOURCE" "$INSTALL_DIR/$BINARY_NAME"
    chmod +x "$INSTALL_DIR/$BINARY_NAME"
    
    # Cleanup temp binary if it was used
    if [ -f "/tmp/metetch_binary_$$" ]; then
        rm -f "/tmp/metetch_binary_$$"
    fi
    
    print_success "Binary installed to $INSTALL_DIR/$BINARY_NAME"
}

create_config_dir() {
    print_info "Setting up configuration directory..."
    
    # Create config directory with proper ownership
    mkdir -p "$CONFIG_DIR"
    chown -R "$ACTUAL_USER:$(id -gn "$ACTUAL_USER")" "$CONFIG_DIR"
    
    if [ ! -f "$CONFIG_DIR/config.ini" ]; then
        cat > "$CONFIG_DIR/config.ini" << 'EOF'
# Metetch Configuration File
# Location: ~/.config/metetch/config.ini

# Display real-time clock in OS section
show_realtime_in_os=0

# Show GPU information
show_gpu=1

# Show disk usage
show_disk=1

# Color theme (default, dark, light)
theme=default

# Preset Configurations
# Default: Standard display with all main features
preset_default=gpu_monitoring,disk_monitoring,network_monitoring,battery_display,cpu_advanced,package_count,uptime_display,memory_display,load_display,processes_display,display_info

# Minimal: Compact view with only essential information
preset_minimal=memory_display,disk_monitoring,cpu_advanced,network_monitoring

# Full: Everything enabled including advanced features
preset_full=gpu_monitoring,disk_monitoring,network_monitoring,battery_display,cpu_advanced,security_info,package_count,uptime_display,memory_display,load_display,processes_display,audio_display,display_info
EOF
        # Set proper ownership for config file
        chown "$ACTUAL_USER:$(id -gn "$ACTUAL_USER")" "$CONFIG_DIR/config.ini"
        chmod 644 "$CONFIG_DIR/config.ini"
        print_success "Configuration file created at $CONFIG_DIR/config.ini"
    else
        print_success "Configuration file already exists"
    fi
}

regenerate_checksums() {
    print_info "Regenerating SHA256 checksums..."
    
    cd "$PROJECT_DIR"
    
    # Files to checksum
    local files=(
        "README.md"
        "BUILD.md"
        "install.sh"
        "Makefile"
        "CMakeLists.txt"
        "LICENSE"
        "SETUP.md"
        "VERIFY.sh"
    )
    
    # Remove old checksums
    rm -f "$PROJECT_DIR/CHECKSUMS.sha256"
    
    # Generate new checksums
    local checksummed=0
    for file in "${files[@]}"; do
        if [ -f "$file" ]; then
            sha256sum "$file" >> "$PROJECT_DIR/CHECKSUMS.sha256"
            print_success "Checksummed: $file"
            checksummed=$((checksummed + 1))
        else
            print_warning "File not found (skipping): $file"
        fi
    done
    
    if [ $checksummed -gt 0 ]; then
        print_success "Checksums regenerated at $PROJECT_DIR/CHECKSUMS.sha256 ($checksummed files)"
    else
        print_warning "No files were checksummed"
    fi
}

main() {
    print_header
    echo ""
    
    check_dependencies
    echo ""
    
    build_project
    echo ""
    
    install_binary
    echo ""
    
    create_config_dir
    echo ""
    
    regenerate_checksums
    echo ""
    
    print_success "Installation complete!"
    echo ""
    echo -e "${CYAN}╔════════════════════════════════════════╗${NC}"
    echo -e "${CYAN}║${NC}   ${YELLOW}🎉 Metetch Ready to Use! 🎉${NC}     ${CYAN}║${NC}"
    echo -e "${CYAN}╚════════════════════════════════════════╝${NC}"
    echo ""
    echo -e "${CYAN}Next steps:${NC}"
    echo -e "  1. Run: ${YELLOW}metetch${NC}"
    echo -e "  2. Configure: ${YELLOW}metetch --config${NC}"
    echo -e "  3. Get help: ${YELLOW}metetch --help${NC}"
    echo ""
    echo -e "${CYAN}Binary location:${NC} ${YELLOW}$INSTALL_DIR/$BINARY_NAME${NC}"
    echo -e "${CYAN}Config location:${NC} ${YELLOW}$CONFIG_DIR/config.ini${NC}"
    echo ""
    echo -e "${CYAN}To uninstall:${NC} ${YELLOW}sudo metetch --uninstall${NC}"
    echo ""
}

main "$@"