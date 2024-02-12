#include <stdio.h>
#include "pico/stdlib.h"

#include <stdbool.h>
#include <stdint.h>
#include <hardware/i2c.h>

#include "wm8960-i2c.h"

#define PIN_SDA 2
#define PIN_SCL 3

#define I2C_PORT i2c1

void wm8960_i2c_init(void)
{
    i2c_init(I2C_PORT, 10 * 1000);

    // Initialize I2C pins
    gpio_set_function(PIN_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PIN_SCL, GPIO_FUNC_I2C);
    
    gpio_pull_up(PIN_SDA);
    gpio_pull_up(PIN_SCL);

    printf("I2C initialized\n");
}

bool i2c_write(uint8_t address, uint8_t *data)
{
    int wbytes = i2c_write_blocking(I2C_PORT, address, data, 2, true);

    if (wbytes == PICO_ERROR_GENERIC) {
        return false;
    }

    return true;
}
