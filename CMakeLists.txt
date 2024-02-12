cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/pico-sdk)
set(PICO_EXTRAS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/pico-extras)

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(${PICO_EXTRAS_PATH}/external/pico_extras_import.cmake)

project(rp2040-wm8960)
pico_sdk_init()
add_compile_options(-Wall)

add_subdirectory(libs)

add_subdirectory(apps)