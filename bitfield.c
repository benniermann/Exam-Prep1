#include "bitfield.h"
#include <stddef.h>

uint32_t set_bit(uint32_t val, int pos)
{
    return val | (1U << pos);
}

uint32_t clear_bit(uint32_t val, int pos)
{
    return val & ~(1U << pos);
}

uint32_t toggle_bit(uint32_t val, int pos)
{
    return val ^ (1U << pos);
}

int get_bit(uint32_t val, int pos)
{
    return (val >> pos) & 1U;
}

int count_ones(uint32_t val)
{
    int count = 0;
    while (val > 0) {
        count += val & 1;
        val >>= 1;
    }
    return count;
}

uint32_t pack_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;
}

void unpack_rgb(uint32_t packed, uint8_t *r, uint8_t *g, uint8_t *b)
{
    if (r != NULL) {
        *r = (packed >> 16) & 0xFF;
    }
    if (g != NULL) {
        *g = (packed >> 8) & 0xFF;
    }
    if (b != NULL) {
        *b = packed & 0xFF;
    }
}