#include "chip.h"
#include "util.h"

#include <iostream>
#include <fstream>
#include <fmt/core.h>

void Chip8::load(std::string path)
{
    std::ifstream file(path.c_str(), std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // TODO: error handling
    file.read(reinterpret_cast<char*>(&this->mem[0]), size);
}

struct Dispatch {
    uint16_t instruction;
    uint16_t mask;
    void(*dispatch)(uint16_t ins);
    std::string(*disassemble)(uint16_t ins);
};

Dispatch dispatch_table[] = {
    {0x0000, 0xF000, [](uint16_t ins) {}, [](uint16_t ins)
     { return fmt::format("Call {}", ins); }}};

void Chip8::dispatch(uint16_t ins) {
    for (auto &entry: dispatch_table) {
        if ((ins & entry.mask) == entry.instruction) {
            entry.dispatch(ins);
        }
    }
}

std::string Chip8::disassemble(uint16_t ins) {
    for (auto &entry: dispatch_table) {
        if ((ins & entry.mask) == entry.instruction) {
            return entry.disassemble(ins);
        }
    }
    // TODO exception
    return "BAD";
}