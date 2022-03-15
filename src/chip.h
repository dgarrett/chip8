#pragma once

#include <stdint.h>
#include <string>

class Chip8
{
public:
    Chip8()
    {
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            for (int x = 0; x < SCREEN_WIDTH; x++)
            {
                screen_pixels[y][x] = 0xabcdefff;
            }
        }
    }
    constexpr static uint32_t SCREEN_WIDTH = 64;
    constexpr static uint32_t SCREEN_HEIGHT = 32;
    uint32_t screen_texture = 0;
    uint32_t screen_pixels[SCREEN_HEIGHT][SCREEN_WIDTH]{};

    std::string disassemble(uint16_t);
    void dispatch(uint16_t);

    uint16_t V[0x10]{};
    uint16_t I = 0;
    uint16_t stack[128]{};
    uint8_t mem[4096]{};
};
