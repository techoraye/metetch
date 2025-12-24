#!/bin/bash

# ============================================================================
# Metetch File Verification Script
# Copyright (c) 2025 techoraye
# Licensed under the MIT License
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
# ============================================================================

set -e

# ============================================================================
# Colors - Synchronized with include/colors.h
# ============================================================================
RED='\033[0;31m'          # STATUS_CRIT color
GREEN='\033[0;32m'        # STATUS_OK variant
YELLOW='\033[1;33m'       # BOLD_YELLOW - used for emphasis
BLUE='\033[0;34m'         # Blue standard
CYAN='\033[1;36m'         # Bold cyan
NC='\033[0m'              # No Color (RESET)

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

print_header() {
    echo -e "${BLUE}╔════════════════════════════════════════╗${NC}"
    echo -e "${BLUE}║${NC}   ${YELLOW}🔒 METETCH FILE VERIFICATION 🔒${NC}   ${BLUE}║${NC}"
    echo -e "${BLUE}╚════════════════════════════════════════╝${NC}"
}

print_check() {
    echo -e "${GREEN}✓${NC} $1"
}

print_error() {
    echo -e "${RED}✗${NC} $1"
}

print_info() {
    echo -e "${BLUE}ℹ${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}⚠${NC} $1"
}

detect_distro() {
    # Detect Flatpak runtime
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

verify_checksums() {
    echo ""
    echo -e "${BLUE}Verifying file integrity...${NC}"
    echo ""
    
    cd "$SCRIPT_DIR"
    
    if [ ! -f "CHECKSUMS.sha256" ]; then
        print_error "CHECKSUMS.sha256 not found!"
        exit 1
    fi
    
    # Try different sha256sum commands based on what's available
    local sha_cmd=""
    if command -v sha256sum &> /dev/null; then
        sha_cmd="sha256sum"
    elif command -v shasum &> /dev/null; then
        sha_cmd="shasum -a 256"
    elif command -v sha256 &> /dev/null; then
        # BSD sha256
        sha_cmd="sha256"
    else
        print_error "No SHA256 checksum tool found (sha256sum, shasum, or sha256)"
        exit 1
    fi
    
    print_info "Using checksum tool: $sha_cmd"
    
    local failed=0
    while IFS= read -r line; do
        if [ -z "$line" ]; then
            continue
        fi
        
        # Parse checksum line (format: "hash  filename" or "filename = hash")
        local hash filename
        if [[ "$line" =~ ^([a-f0-9]+)[[:space:]]+(.+)$ ]]; then
            hash="${BASH_REMATCH[1]}"
            filename="${BASH_REMATCH[2]}"
        elif [[ "$line" =~ ^(.+)[[:space:]]*=[[:space:]]*([a-f0-9]+)$ ]]; then
            filename="${BASH_REMATCH[1]}"
            hash="${BASH_REMATCH[2]}"
        else
            continue
        fi
        
        if [ ! -f "$filename" ]; then
            print_error "File not found: $filename"
            failed=1
            continue
        fi
        
        # Calculate hash based on tool available
        local computed_hash
        if [ "$sha_cmd" = "sha256sum" ]; then
            computed_hash=$(sha256sum "$filename" | awk '{print $1}')
        elif [ "$sha_cmd" = "shasum -a 256" ]; then
            computed_hash=$(shasum -a 256 "$filename" | awk '{print $1}')
        elif [ "$sha_cmd" = "sha256" ]; then
            # BSD sha256
            computed_hash=$(sha256 -q "$filename")
        fi
        
        if [ "$computed_hash" = "$hash" ]; then
            print_check "$filename"
        else
            print_error "$filename (hash mismatch)"
            failed=1
        fi
    done < CHECKSUMS.sha256
    
    if [ $failed -eq 0 ]; then
        echo ""
        print_check "All files verified successfully!"
        return 0
    else
        echo ""
        print_error "Checksum verification FAILED!"
        print_warning "One or more files have been modified or corrupted"
        exit 1
    fi
}

main() {
    print_header
    verify_checksums
    
    echo ""
    echo -e "${GREEN}╔════════════════════════════════════════╗${NC}"
    echo -e "${GREEN}║${NC}    ${YELLOW}✓ Verification Successful ✓${NC}     ${GREEN}║${NC}"
    echo -e "${GREEN}╚════════════════════════════════════════╝${NC}"
    echo ""
}

main "$@"
