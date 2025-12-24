/**
 * Features Registry Initialization
 * Dynamically registers all available features at runtime
 */

#include "flags/config/features_registry.h"
#include "data_types.h"

FeaturesRegistry features_registry;

// Feature declarations
extern void toggleGPUMonitoring();
extern void toggleDiskMonitoring();
extern void toggleNetworkMonitoring();
extern void toggleBatteryDisplay();
extern void toggleAdvancedCPU();
extern void toggleSecurityInfo();
extern void togglePackageCount();
extern void toggleUptimeDisplay();
extern void toggleMemoryDisplay();
extern void toggleLoadDisplay();
extern void toggleProcessesDisplay();
extern void toggleAudioDisplay();
extern void toggleDisplayInfo();

void initializeFeaturesRegistry() {
    // Register all features dynamically
    features_registry.registerFeature({
        "gpu_monitoring",
        "GPU Monitoring",
        "Display GPU device, usage, temperature, and memory",
        &cfg.show_gpu,
        toggleGPUMonitoring
    });
    
    features_registry.registerFeature({
        "disk_monitoring",
        "Disk Monitoring",
        "Display disk usage and storage information",
        &cfg.show_disk,
        toggleDiskMonitoring
    });
    
    features_registry.registerFeature({
        "network_monitoring",
        "Network Monitoring",
        "Display network interface and advanced network stats",
        &cfg.show_network,
        toggleNetworkMonitoring
    });
    
    features_registry.registerFeature({
        "battery_display",
        "Battery Display",
        "Show battery status and power information",
        &cfg.show_battery,
        toggleBatteryDisplay
    });
    
    features_registry.registerFeature({
        "cpu_advanced",
        "Advanced CPU Info",
        "Display detailed CPU metrics (frequency, cores, TDP)",
        &cfg.show_cpu_advanced,
        toggleAdvancedCPU
    });
    
    features_registry.registerFeature({
        "security_info",
        "Security Info",
        "Show security features and firewall status",
        &cfg.show_security,
        toggleSecurityInfo
    });
    
    features_registry.registerFeature({
        "package_count",
        "Package Count",
        "Display installed package statistics",
        &cfg.show_packages,
        togglePackageCount
    });
    
    features_registry.registerFeature({
        "uptime_display",
        "Uptime Display",
        "Show system uptime information",
        &cfg.show_uptime,
        toggleUptimeDisplay
    });
    
    features_registry.registerFeature({
        "memory_display",
        "Memory Display",
        "Show RAM and swap memory usage",
        &cfg.show_memory,
        toggleMemoryDisplay
    });
    
    features_registry.registerFeature({
        "load_display",
        "CPU Load Display",
        "Show CPU load and temperature metrics",
        &cfg.show_load,
        toggleLoadDisplay
    });
    
    features_registry.registerFeature({
        "processes_display",
        "Processes Display",
        "Show process and thread statistics",
        &cfg.show_processes,
        toggleProcessesDisplay
    });
    
    features_registry.registerFeature({
        "audio_display",
        "Audio System Display",
        "Show audio device and configuration",
        &cfg.show_audio,
        toggleAudioDisplay
    });
    
    features_registry.registerFeature({
        "display_info",
        "Display Information",
        "Show monitor resolution and details",
        &cfg.show_display,
        toggleDisplayInfo
    });
}
