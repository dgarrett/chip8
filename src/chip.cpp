#include "chip.h"
#include "util.h"

struct Dispatch {
    uint16_t instruction;
    uint16_t mask;
    void(*dispatch)(uint16_t ins);
    std::string(*disassemble)(uint16_t ins);
};

Dispatch dispatch_table[] = {
    {0x0000, 0xF000, [](uint16_t ins) {}, [](uint16_t ins)
     { return std::string("Call"); }}};

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