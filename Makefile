# ============================================================================
# Metetch Makefile
# Copyright (c) 2025 techoraye - All Rights Reserved
# Licensed under METETCH PROPRIETARY LICENSE
# This software and source code are proprietary and confidential
# See LICENSE file for details
# ============================================================================

.PHONY: all build install uninstall clean help

# Color output
GREEN  := \033[0;32m
YELLOW := \033[0;33m
RED    := \033[0;31m
NC     := \033[0m # No Color

INSTALL_PATH := /usr/local/bin
BUILD_DIR := build
BINARY_NAME := metetch
VERSION := 0.3.0

all: build

build:
	@echo "$(YELLOW)Building metetch v$(VERSION)...$(NC)"
	@TMP_BUILD=/tmp/metetch_build_$$$$; \
	mkdir -p $$TMP_BUILD/build; \
	cp -r src include CMakeLists.txt $$TMP_BUILD/ 2>/dev/null || true; \
	cd $$TMP_BUILD/build && \
	cmake .. > /dev/null 2>&1 && \
	make -j$(shell nproc) > /dev/null 2>&1 && \
	mkdir -p $(PWD)/$(BUILD_DIR) && \
	cp $$TMP_BUILD/build/$(BINARY_NAME) $(PWD)/$(BUILD_DIR)/ && \
	rm -rf $$TMP_BUILD && \
	echo "$(GREEN)✓ Build successful!$(NC)" && \
	echo "$(GREEN)Binary location: $(PWD)/$(BUILD_DIR)/$(BINARY_NAME)$(NC)" || \
	(echo "$(RED)✗ Build failed!$(NC)" && exit 1)

install: build
	@echo "$(YELLOW)Installing metetch to $(INSTALL_PATH)...$(NC)"
	@sudo cp $(BUILD_DIR)/$(BINARY_NAME) $(INSTALL_PATH)/
	@sudo chmod +x $(INSTALL_PATH)/$(BINARY_NAME)
	@echo "$(GREEN)✓ Installation successful!$(NC)"
	@echo "$(GREEN)Run 'metetch' from anywhere to start the system monitor.$(NC)"

uninstall:
	@echo "$(YELLOW)Removing metetch from $(INSTALL_PATH)...$(NC)"
	@sudo rm -f $(INSTALL_PATH)/$(BINARY_NAME)
	@echo "$(GREEN)✓ Uninstallation successful!$(NC)"

clean:
	@echo "$(YELLOW)Cleaning build directory...$(NC)"
	@rm -rf $(BUILD_DIR)
	@echo "$(GREEN)✓ Clean successful!$(NC)"

help:
	@echo "$(GREEN)metetch - System Information Fetcher$(NC)"
	@echo ""
	@echo "$(YELLOW)Available targets:$(NC)"
	@echo "  make build       - Build the project (default)"
	@echo "  make install     - Build and install to $(INSTALL_PATH)"
	@echo "  make uninstall   - Remove from system"
	@echo "  make clean       - Remove build directory"
	@echo "  make help        - Show this help message"
	@echo ""
	@echo "$(YELLOW)Examples:$(NC)"
	@echo "  make              # Build the project"
	@echo "  make install      # Build and install system-wide"
	@echo "  make uninstall    # Remove from system"
