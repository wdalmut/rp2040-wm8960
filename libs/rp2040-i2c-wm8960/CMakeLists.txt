cmake_minimum_required(VERSION 3.16)

# set the project name
project(rp2040-i2c-wm8960)

# define libraries
add_library(rp2040-i2c-wm8960 src/wm8960-i2c.c)

target_link_libraries(rp2040-i2c-wm8960
    pico_stdlib
    hardware_i2c
)

# define location for header files
target_include_directories(rp2040-i2c-wm8960 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)
