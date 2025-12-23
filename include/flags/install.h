#pragma once

/**
 * Install Flag Display - Installation and setup information displays
 * Handles install messages and prompts
 */

/**
 * Display installation starting message
 */
void showInstallStarting();

/**
 * Display installation progress
 */
void showInstallProgress(const char* step);

/**
 * Display installation success message
 */
void showInstallSuccess();

/**
 * Display installation failed message
 */
void showInstallFailed(const char* reason);

/**
 * Display post-installation instructions
 */
void showPostInstallInstructions();
