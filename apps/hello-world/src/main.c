#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include <math.h>

#include <stdbool.h>
#include <stdint.h>

#include "wm8960-i2c.h"
#include "mtb_wm8960.h"

#include "pico/audio_i2s.h"

#define SINE_WAVE_TABLE_LEN 2048
#define SAMPLES_PER_BUFFER 256

static int16_t sine_wave_table[SINE_WAVE_TABLE_LEN];

struct audio_buffer_pool *init_audio() {

    static audio_format_t audio_format = {
            .format = AUDIO_BUFFER_FORMAT_PCM_S16,
            .sample_freq = 24000,
            .channel_count = 1,
    };

    static struct audio_buffer_format producer_format = {
            .format = &audio_format,
            .sample_stride = 2
    };

    struct audio_buffer_pool *producer_pool = audio_new_producer_pool(&producer_format, 3,
                                                                      SAMPLES_PER_BUFFER); // todo correct size
    bool __unused ok;
    const struct audio_format *output_format;

    struct audio_i2s_config config = {
            .data_pin = PICO_AUDIO_I2S_DATA_PIN,
            .clock_pin_base = PICO_AUDIO_I2S_CLOCK_PIN_BASE,
            .dma_channel = 0,
            .pio_sm = 0,
    };

    output_format = audio_i2s_setup(&audio_format, &config);
    if (!output_format) {
        panic("PicoAudio: Unable to open audio device.\n");
    }

    ok = audio_i2s_connect(producer_pool);
    assert(ok);
    audio_i2s_set_enabled(true);
    return producer_pool;
}

int main(void) {
    bool status = false; 

    stdio_init_all();

    sleep_ms(3000);

    wm8960_i2c_init();

    sleep_ms(100);

    printf("PicoAudio: Initializing audio codec [%d %d].\n", PICO_AUDIO_I2S_CLOCK_PIN_BASE, PICO_AUDIO_I2S_DATA_PIN);
    
    status = mtb_wm8960_init(WM8960_FEATURE_HEADPHONE);
    if (!status) {
        panic("PicoAudio: Unable to initialize audio codec.\n");
    }

    mtb_wm8960_activate();
    if (!status) {
        panic("PicoAudio: Unable to activate audio codec.\n");
    }

    status = mtb_wm8960_configure_clocking(
        512 * 24000,
        true,
        WM8960_ADC_DAC_SAMPLE_RATE_24_KHZ,
        WM8960_AUDIO_INTF0_WL_16BITS,
        WM8960_AUDIO_INTF0_MS_SLAVE);

    if (!status) {
        panic("PicoAudio: Unable to configure audio clocking.\n");
    }

    status = mtb_wm8960_set_output_volume(0x7F);
    if (!status) {
        panic("PicoAudio: Unable to set output volume.\n");
    }

    for (int i = 0; i < SINE_WAVE_TABLE_LEN; i++) {
        sine_wave_table[i] = 32767 * cosf(i * 2 * (float) (M_PI / SINE_WAVE_TABLE_LEN));
    }

    struct audio_buffer_pool *ap = init_audio();
    uint32_t step = 0x200000;
    uint32_t pos = 0;
    uint32_t pos_max = 0x10000 * SINE_WAVE_TABLE_LEN;
    uint vol = 128;

    while(1) {
        struct audio_buffer *buffer = take_audio_buffer(ap, true);

        int16_t *samples = (int16_t *) buffer->buffer->bytes;
        for (uint i = 0; i < buffer->max_sample_count; i++) {
            samples[i] = (vol * sine_wave_table[pos >> 16u]) >> 8u;
            pos += step;
            if (pos >= pos_max) pos -= pos_max;
        }

        buffer->sample_count = buffer->max_sample_count;
        give_audio_buffer(ap, buffer);
    }

    puts("\n");
    return 0;
}