cmake_minimum_required(VERSION 3.10)
project(metetch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -flto -Wall -Wextra")

find_package(CURL REQUIRED)
find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    # Core
    src/main.cpp
    src/utils.cpp
    src/collect.cpp
    src/render.cpp
    src/update_handler.cpp
    src/uninstall.cpp
    
    # Modular Namespaced Functions (Pure C++, Zero Piping)
    src/modules/system.cpp
    src/modules/hardware.cpp
    src/modules/network.cpp
    
    # Advanced Hardware Modules
    src/modules/hardware/gpu.cpp
    
    # CPU Advanced Modules
    src/modules/hardware/cpu_advanced/frequency_current.cpp
    src/modules/hardware/cpu_advanced/frequency_max.cpp
    src/modules/hardware/cpu_advanced/frequency_base.cpp
    src/modules/hardware/cpu_advanced/cores.cpp
    src/modules/hardware/cpu_advanced/threads.cpp
    src/modules/hardware/cpu_advanced/tdp.cpp
    src/modules/hardware/cpu_advanced/power_draw.cpp
    src/modules/hardware/cpu_advanced/helper.cpp
    src/modules/hardware/cpu_advanced/aggregator.cpp
    
    # Disk Advanced Modules
    src/modules/hardware/disk_advanced/disk_info.cpp
    src/modules/hardware/disk_advanced/disks_info.cpp
    src/modules/hardware/disk_advanced/all_disks_stats.cpp
    src/modules/hardware/disk_advanced/total_space.cpp
    src/modules/hardware/disk_advanced/used_space.cpp
    src/modules/hardware/disk_advanced/free_space.cpp
    src/modules/hardware/disk_advanced/usage_percent.cpp
    src/modules/hardware/disk_advanced/helper.cpp
    
    # Advanced Network Modules
    src/modules/network/advanced/ipv4.cpp
    src/modules/network/advanced/ipv6.cpp
    src/modules/network/advanced/gateway.cpp
    src/modules/network/advanced/dns.cpp
    src/modules/network/advanced/mac.cpp
    src/modules/network/advanced/bytes_received.cpp
    src/modules/network/advanced/bytes_sent.cpp
    src/modules/network/advanced/packet_loss.cpp
    src/modules/network/advanced/latency.cpp
    src/modules/network/advanced/helper.cpp
    src/modules/network/advanced/aggregator.cpp
    
    # System Modules
    src/modules/system/security.cpp
    src/modules/system/resources.cpp
    
    # Flag Config Modules
    src/flags/config/path.cpp
    src/flags/config/loader.cpp
    src/flags/config/saver.cpp
    src/flags/config/menu.cpp
    src/flags/config/features_registry.cpp
    src/flags/config/display_title.cpp
    
    # Flag Config Features (Modular)
    src/flags/config/features/gpu_monitoring_toggle.cpp
    src/flags/config/features/disk_monitoring_toggle.cpp
    src/flags/config/features/network_monitoring_toggle.cpp
    src/flags/config/features/battery_display_toggle.cpp
    src/flags/config/features/advanced_cpu_toggle.cpp
    src/flags/config/features/security_info_toggle.cpp
    src/flags/config/features/package_count_toggle.cpp
    src/flags/config/features/uptime_display_toggle.cpp
    src/flags/config/features/memory_display_toggle.cpp
    src/flags/config/features/load_display_toggle.cpp
    src/flags/config/features/processes_display_toggle.cpp
    src/flags/config/features/audio_display_toggle.cpp
    src/flags/config/features/display_info_toggle.cpp
    
    # Flag Help Modules
    src/flags/help/basic.cpp
    src/flags/help/extended.cpp
    
    # Flag Install Modules
    src/flags/install/starting.cpp
    src/flags/install/progress.cpp
    src/flags/install/success.cpp
    src/flags/install/failed.cpp
    src/flags/install/post_instructions.cpp
    
    # Flag Update Modules
    src/flags/update/checker.cpp
    src/flags/update/display.cpp
    src/flags/update/check_message.cpp
    src/flags/update/handler.cpp
    src/flags/update/install_executor.cpp
    
    # Flag Minimal Modules
    src/flags/minimal/display.cpp
)

add_executable(metetch ${SOURCES})

target_link_libraries(metetch PRIVATE
    ${CURL_LIBRARIES}
    ${CURSES_LIBRARIES}
    tinfo
    pthread
)

install(TARGETS metetch DESTINATION /usr/local/bin)
