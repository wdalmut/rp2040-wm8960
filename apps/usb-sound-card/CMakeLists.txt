add_executable(usb-sound-card
    src/main.c
)

target_include_directories(usb-sound-card PRIVATE
    src
)

target_compile_definitions(usb-sound-card PRIVATE
    PICO_AUDIO_I2S_MONO_OUTPUT=0
    PICO_AUDIO_I2S_MONO_INPUT=0
    USE_AUDIO_I2S=1
    PICO_AUDIO_I2S_DATA_PIN=21
    PICO_AUDIO_I2S_CLOCK_PIN_BASE=18
    PICO_USBDEV_ISOCHRONOUS_BUFFER_STRIDE_TYPE=1
    PICO_USBDEV_ENABLE_DEBUG_TRACE
    # need large descriptor
    PICO_USBDEV_MAX_DESCRIPTOR_SIZE=256
    # ours are zero based, so say so
    PICO_USBDEV_USE_ZERO_BASED_INTERFACES=1
    AUDIO_FREQ_MAX=48000
)

target_link_libraries(usb-sound-card
    pico_stdlib
    pico_util
    pico_multicore
    hardware_i2c
    arduino-wm8960
    rp2040-i2c-wm8960
    usb_device 
    pico_audio_i2s
)

pico_enable_stdio_usb(usb-sound-card 0) # disable usb output
pico_enable_stdio_uart(usb-sound-card 1) # enable uart output

# create map/bin/hex file etc.
pico_add_extra_outputs(usb-sound-card)