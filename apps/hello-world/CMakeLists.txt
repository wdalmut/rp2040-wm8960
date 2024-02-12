add_executable(hello-world
    src/main.c
)

target_include_directories(hello-world PRIVATE
    src/include
)

target_compile_definitions(hello-world PRIVATE
    PICO_AUDIO_I2S_MONO_INPUT=1
    USE_AUDIO_I2S=1
    PICO_AUDIO_I2S_DATA_PIN=21
    PICO_AUDIO_I2S_CLOCK_PIN_BASE=18
)

target_link_libraries(hello-world
    pico_stdlib
    pico_util
    hardware_i2c
    arduino-wm8960
    rp2040-i2c-wm8960
    pico_audio_i2s
)

pico_enable_stdio_usb(hello-world 1) # enable usb output
pico_enable_stdio_uart(hello-world 0) # disable uart output

# create map/bin/hex file etc.
pico_add_extra_outputs(hello-world)