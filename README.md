# RP2040 audio with WM8960

Here a set of examples of i2s audio thanks to the WM8960 and the RP2040.

## Build

Just use the CMAKE

```sh
mkdir build && cd build
cmake ..
make
```

## Dependecies

This project uses as dependecy:

 * pico-extras
   * To support the Audio I2S
 * arduino-wm8960
   * To support the configuration for the WM8960

In the `libs` folder there is also a `rp2040-i2c-wm8960` that configure the i2c
device from the RP2040 that is used to configure the WM8960.

## Hardware configuration

Currently i am using the WM8960 Audio Hat from Waveshare and also the the board
RP2040-PiZero always from the Waveshare

![audio-shield](https://www.waveshare.com/w/A6Y79bcq/Kdy80nYY.php?f=WM8960-Audio-HAT-1.jpg&width=600)

![rp2040-pizero](https://www.waveshare.com/w/upload/1/18/RP2040-PiZero.jpg)