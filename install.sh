#!/bin/bash

# ============================================================================
# Metetch Installation Script
# Copyright (c) 2025 techoraye - All Rights Reserved
# Licensed under METETCH PROPRIETARY LICENSE
# This software and source code are proprietary and confidential
# See LICENSE file for details
# ============================================================================

set -e

# Check if running with sudo
if [ "$EUID" -ne 0 ]; then 
    echo -e "\033[0;31m✗\033[0m This script must be run with sudo"
    echo -e "\033[0;34mℹ\033[0m Run: sudo $0"
    exit 1
fi

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
INSTALL_DIR="/usr/local/bin"
CONFIG_DIR="$HOME/.config/metetch"
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$PROJECT_DIR/build"
BINARY_NAME="metetch"
VERSION="0.5.0"

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
    
    case "$distro" in
        ubuntu|debian)
            print_info "Using apt (Debian/Ubuntu)..."
            apt-get update > /dev/null 2>&1 || true
            apt-get install -y build-essential cmake libcurl4-openssl-dev libncurses-dev libtinfo-dev pkg-config
            ;;
        arch|manjaro)
            print_info "Using pacman (Arch/Manjaro)..."
            pacman -Sy --noconfirm base-devel cmake curl ncurses
            ;;
        fedora|rhel|centos)
            print_info "Using dnf/yum (Fedora/RHEL/CentOS)..."
            if command -v dnf &> /dev/null; then
                dnf install -y gcc-c++ cmake libcurl-devel ncurses-devel libtinfo-devel pkg-config
            else
                yum install -y gcc-c++ cmake libcurl-devel ncurses-devel libtinfo-devel pkg-config
            fi
            ;;
        opensuse*|sles)
            print_info "Using zypper (openSUSE/SLES)..."
            zypper install -y gcc-c++ cmake libcurl-devel ncurses-devel libtinfo-devel pkg-config
            ;;
        alpine)
            print_info "Using apk (Alpine Linux)..."
            apk add --no-cache build-base cmake curl-dev ncurses-dev linux-headers pkgconfig
            ;;
        void)
            print_info "Using xbps (Void Linux)..."
            xbps-install -Sy base-devel cmake curl-devel ncurses-devel pkg-config
            ;;
        gentoo)
            print_info "Using emerge (Gentoo)..."
            emerge --sync > /dev/null 2>&1 || true
            emerge -qv dev-build/cmake net-misc/curl sys-libs/ncurses
            ;;
        *)
            print_warning "Unknown distro: $distro"
            print_warning "Attempting generic installation..."
            if command -v apt-get &> /dev/null; then
                apt-get update && apt-get install -y build-essential cmake libcurl4-openssl-dev libncurses-dev libtinfo-dev pkg-config
            elif command -v pacman &> /dev/null; then
                pacman -Sy --noconfirm base-devel cmake curl ncurses
            elif command -v dnf &> /dev/null; then
                dnf install -y gcc-c++ cmake libcurl-devel ncurses-devel libtinfo-devel pkg-config
            elif command -v zypper &> /dev/null; then
                zypper install -y gcc-c++ cmake libcurl-devel ncurses-devel libtinfo-devel pkg-config
            else
                print_error "Could not detect package manager. Please install dependencies manually."
                exit 1
            fi
            ;;
    esac
    
    print_success "Dependencies installed"
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
    cp -r "$PROJECT_DIR"/{src,include,CMakeLists.txt} "$TMP_BUILD/" 2>/dev/null || true
    
    mkdir -p "$TMP_BUILD/build"
    cd "$TMP_BUILD/build"
    
    print_info "Configuring with CMake..."
    cmake .. > /dev/null 2>&1 || { print_error "CMake configuration failed!"; exit 1; }
    
    print_info "Compiling (using $(nproc) cores)..."
    make -j$(nproc) > /dev/null 2>&1 || { print_error "Build failed!"; exit 1; }
    
    if [ -f "$TMP_BUILD/build/$BINARY_NAME" ]; then
        print_success "Build completed successfully"
        # Copy back to project build directory
        mkdir -p "$BUILD_DIR"
        cp "$TMP_BUILD/build/$BINARY_NAME" "$BUILD_DIR/$BINARY_NAME" 2>/dev/null || cp "$TMP_BUILD/build/$BINARY_NAME" /tmp/metetch_binary_$$
        BUILD_BINARY="${BUILD_DIR}/${BINARY_NAME}"
        if [ ! -f "$BUILD_BINARY" ]; then
            BUILD_BINARY="/tmp/metetch_binary_$$"
        fi
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
    
    mkdir -p "$CONFIG_DIR"
    
    if [ ! -f "$CONFIG_DIR/config.ini" ]; then
        cat > "$CONFIG_DIR/config.ini" << EOF
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
EOF
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
    for file in "${files[@]}"; do
        if [ -f "$file" ]; then
            sha256sum "$file" >> "$PROJECT_DIR/CHECKSUMS.sha256"
            print_success "Checksummed: $file"
        fi
    done
    
    print_success "Checksums regenerated at $PROJECT_DIR/CHECKSUMS.sha256"
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
    echo -e "${GREEN}╔════════════════════════════════════════╗${NC}"
    echo -e "${GREEN}║${NC}   ${YELLOW}🎉 Metetch Ready to Use! 🎉${NC}     ${GREEN}║${NC}"
    echo -e "${GREEN}╚════════════════════════════════════════╝${NC}"
    echo ""
    echo -e "${BLUE}Next steps:${NC}"
    echo "  1. Run: ${YELLOW}metetch${NC}"
    echo "  2. Configure: ${YELLOW}metetch --config${NC}"
    echo "  3. Get help: ${YELLOW}metetch --help${NC}"
    echo ""
    echo -e "${BLUE}Binary location:${NC} ${YELLOW}$INSTALL_DIR/$BINARY_NAME${NC}"
    echo -e "${BLUE}Config location:${NC} ${YELLOW}$CONFIG_DIR/config.ini${NC}"
    echo ""
    echo -e "${BLUE}To uninstall:${NC} ${YELLOW}sudo metetch --uninstall${NC}"
    echo ""
}

main "$@"
