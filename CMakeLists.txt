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
    src/config.cpp
    src/render.cpp
    src/update.cpp
    src/update_handler.cpp
    src/uninstall.cpp
    
    # Modular Namespaced Functions (Pure C++, Zero Piping)
    src/modules/system.cpp
    src/modules/hardware.cpp
    src/modules/network.cpp
    
    # Advanced Hardware Modules
    src/modules/hardware/gpu.cpp
    src/modules/hardware/cpu_advanced.cpp
    src/modules/hardware/disk_advanced.cpp
    
    # Advanced Network Modules
    src/modules/network/advanced.cpp
    
    # System Modules
    src/modules/system/security.cpp
    src/modules/system/resources.cpp
)

add_executable(metetch ${SOURCES})

target_link_libraries(metetch PRIVATE
    ${CURL_LIBRARIES}
    ${CURSES_LIBRARIES}
    tinfo
    pthread
)

install(TARGETS metetch DESTINATION /usr/local/bin)
