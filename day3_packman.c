#include <stdio.h>
#include <stdint.h>

#define MASK_RED 0xF800  // 1111 1000 0000 0000
#define MASK_GREEN 0x07E0  // 0000 0111 1110 0000
#define MASK_BLUE 0x001F   // 0000 0000 0001 1111

void parse_rgb565(uint16_t pixel) 
{
    uint8_t r_raw = (pixel & MASK_RED) >> 11;   // Extract red component
    uint8_t g_raw = (pixel & MASK_GREEN) >> 5; // Extract green component
    uint8_t b_raw = (pixel & MASK_BLUE);          // Extract blue component

    uint8_t r8 = (r_raw <<3);
    uint8_t g8 = (g_raw <<3);
    uint8_t b8 = (b_raw <<3);


    printf("Input : 0x%04X\n", pixel);
    printf("[Raw Value] R : %2d (0x%02X), G : %2d (0X%02X), B : %2d (0x%02X)\n",
    r_raw, r_raw, g_raw, g_raw, b_raw, b_raw);

    printf("Pixel: 0x%04X -> R: %d, G: %d, B: %d\n", pixel, r8, g8, b8);
}

int main(int argc, char *argv[]) 
{   
    printf("===Day 3 : Packed Data Parsing (RGB565) ===\n");

    parse_rgb565(0xFFFF);
    parse_rgb565(0xF000);
    parse_rgb565(0x07E0);
    parse_rgb565(0x1234);

    return 0;
}