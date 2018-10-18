/**
 * @file led_seq.c Contains the PWM values for the one or more color LED(s)
 *                 for the different sequences 
 *
 * Automagically created on: 18-10-2018 at 15:36 */

#include "led_seq.h"
#include "boards.h"

#define LED_STRUCT1(name, count)       const struct {            \
                                        uint16_t red[count];    \
                                      } __attribute__((packed)) name

#define LED_STRUCT2(name, count)       const struct {            \
                                        uint16_t red[count];    \
                                        uint16_t green[count];   \
                                      } __attribute__((packed)) name

LED_STRUCT2(ramp_offset_seq, 5) = {
    {0, 0, 1000, 1000, 0},
    {0, 1000, 1000, 0, 0}
};
const uint16_t ramp_offset_duration[] = { 0, 2000, 2000, 2000, 2000, 8000 };

LED_STRUCT1(red_pulse_seq, 6) = {
    {0, 1000, 1000, 0, 200, 0}
};
const uint16_t red_pulse_duration[] = { 0, 2000, 2000, 2000, 500, 500, 7000 };

LED_STRUCT2(green_seq_seq, 5) = {
    {0, 0, 0, 0, 0},
    {0, 1000, 200, 0, 0}
};
const uint16_t green_seq_duration[] = { 0, 1000, 1000, 2000, 1000, 5000 };

LED_STRUCT2(dual_freq_seq, 5) = {
    {0, 1000, 0, 1000, 0},
    {0, 500, 1000, 500, 0}
};
const uint16_t dual_freq_duration[] = { 0, 2000, 2000, 2000, 2000, 8000 };

LED_STRUCT1(pir_pulse_seq, 4) = {
    {0, 1000, 1000, 0}
};
const uint16_t pir_pulse_duration[] = { 0, 25, 250, 25, 300 };

LED_STRUCT2(orange_seq_seq, 3) = {
    {0, 1000, 0},
    {0, 1000, 0}
};
const uint16_t orange_seq_duration[] = { 0, 2500, 2500, 5000 };

const uint32_t led_num_len[] = {2, 1, 2, 2, 1, 2};
const uint32_t led_seq_len[] = {5, 6, 5, 5, 4, 3};
const uint16_t * const led_seq_ptr[] = {(uint16_t *) &ramp_offset_seq, (uint16_t *) &red_pulse_seq, (uint16_t *) &green_seq_seq, (uint16_t *) &dual_freq_seq, (uint16_t *) &pir_pulse_seq, (uint16_t *) &orange_seq_seq };
const uint16_t * const led_seq_duration_ptr[] = { ramp_offset_duration, red_pulse_duration, green_seq_duration, dual_freq_duration, pir_pulse_duration, orange_seq_duration };

const uint32_t led_pin_num[LED_COLOR_MAX] = {LED_RED, LED_GREEN};

const uint32_t * const led_seq_get_pin_ptr(void)
{
    return led_pin_num;
}

uint32_t led_seq_get_pin_num(led_sequences seq)
{
    return led_num_len[seq];
}

uint32_t led_seq_get_seg_len(led_sequences seq)
{
    return led_seq_len[seq];
}

uint16_t * led_seq_get_seq_color_ptr(led_sequences seq, led_seq_color color)
{
    return ((uint16_t *)(led_seq_ptr[seq] + color*led_seq_len[seq]));
}

uint16_t * led_seq_get_seq_duration_ptr(led_sequences seq)
{
    return (uint16_t *) led_seq_duration_ptr[seq];
}

