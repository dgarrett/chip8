#include "chip.h"
#include "util.h"

#include <iostream>
#include <fstream>
#include <fmt/core.h>

void Chip8::load(std::string path) {
    std::ifstream file(path.c_str(), std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // TODO: error handling
    file.read(reinterpret_cast<char *>(&this->mem[0]), size);
}

struct Dispatch {
    uint16_t instruction;
    uint16_t mask;
    void (*dispatch)(Chip8 *chip, uint16_t ins);
    std::string (*disassemble)(uint16_t ins);
};

Dispatch dispatch_table[] = {
    {0x00E0, 0xFFFF, [](Chip8 *chip, uint16_t ins) {}, [](uint16_t ins) { return fmt::format("disp_clear"); }},
    {0x00EE, 0xFFFF, [](Chip8 *chip, uint16_t ins) {
        chip->SP--;
        chip->PC = chip->SP; }, [](uint16_t ins) { return fmt::format("ret"); }},
    {0x0000, 0xF000, [](Chip8 *chip, uint16_t ins) {}, [](uint16_t ins) { return fmt::format("callm {:03X}", NNN(ins)); }},
    {0x1000, 0xF000, [](Chip8 *chip, uint16_t ins) { chip->PC = NNN(ins); }, [](uint16_t ins) { return fmt::format("jmp {:03X}", NNN(ins)); }},
    {0x2000, 0xF000, [](Chip8 *chip, uint16_t ins) {
        chip->SP = chip->PC;
        chip->SP++;
        chip->PC = NNN(ins); }, [](uint16_t ins) { return fmt::format("call {:03X}", NNN(ins)); }},
    {0x3000, 0xF000, [](Chip8 *chip, uint16_t ins) {
        if (chip->V[X(ins)] == NN(ins)) chip->PC++; }, [](uint16_t ins) { return fmt::format("sei v{:01X} {}", X(ins), NN(ins)); }},
    {0x4000, 0xF000, [](Chip8 *chip, uint16_t ins) {
        if (chip->V[X(ins)] != NN(ins)) chip->PC++; }, [](uint16_t ins) { return fmt::format("snei v{:01X} {}", X(ins), NN(ins)); }},
    {0x5000, 0xF00F, [](Chip8 *chip, uint16_t ins) {
        if (chip->V[X(ins)] == chip->V[Y(ins)]) chip->PC++; }, [](uint16_t ins) { return fmt::format("ser v{:01X} v{:01X}", X(ins), Y(ins)); }},
    {0x6000, 0xF000, [](Chip8 *chip, uint16_t inst) {}, [](uint16_t ins) { return fmt::format("movi v{:01X} {}", X(ins), NN(ins)); }},
    {0x7000, 0xF000, [](Chip8 *chip, uint16_t inst) {}, [](uint16_t ins) { return fmt::format("addi v{:01X} {}", X(ins), NN(ins)); }},
    {0x8000, 0xF00F, [](Chip8 *chip, uint16_t inst) {}, [](uint16_t ins) { return fmt::format("movr v{:01X} v{:01X}", X(ins), Y(ins)); }},
    {0x8001, 0xF00F, [](Chip8 *chip, uint16_t inst) {}, [](uint16_t ins) { return fmt::format("or v{:01X} v{:01X}", X(ins), Y(ins)); }},
    {0x8002, 0xF00F, [](Chip8 *chip, uint16_t inst) {}, [](uint16_t ins) { return fmt::format("and v{:01X} v{:01X}", X(ins), Y(ins)); }},
    {0x8003, 0xF00F, [](Chip8 *chip, uint16_t inst) {}, [](uint16_t ins) { return fmt::format("xor v{:01X} v{:01X}", X(ins), Y(ins)); }},
    {0x8004, 0xF00F, [](Chip8 *chip, uint16_t inst) {}, [](uint16_t ins) { return fmt::format("addr v{:01X} v{:01X}", X(ins), Y(ins)); }},
    {0x8005, 0xF00F, [](Chip8 *chip, uint16_t inst) {}, [](uint16_t ins) { return fmt::format("subr v{:01X} v{:01X}", X(ins), Y(ins)); }},
    {0x8006, 0xF00F, [](Chip8 *chip, uint16_t inst) {}, [](uint16_t ins) { return fmt::format("shr v{:01X} v{:01X}", X(ins), Y(ins)); }},
    {0x8007, 0xF00F, [](Chip8 *chip, uint16_t inst) {}, [](uint16_t ins) { return fmt::format("nsubr v{:01X} v{:01X}", X(ins), Y(ins)); }},
    {0x800E, 0xF00F, [](Chip8 *chip, uint16_t inst) {}, [](uint16_t ins) { return fmt::format("shl v{:01X} v{:01X}", X(ins), Y(ins)); }},
    {0x9000, 0xF00F, [](Chip8 *chip, uint16_t inst) {}, [](uint16_t ins) { return fmt::format("sner v{:01X} v{:01X}", X(ins), Y(ins)); }},
    {0xA000, 0xF000, [](Chip8 *chip, uint16_t inst) {}, [](uint16_t ins) { return fmt::format("imovi 0x{:03X}", NNN(ins)); }},
    {0xB000, 0xF000, [](Chip8 *chip, uint16_t inst) {}, [](uint16_t ins) { return fmt::format("jumpoff 0x{:03X}", NNN(ins)); }},
    {0xC000, 0xF000, [](Chip8 *chip, uint16_t inst) {}, [](uint16_t ins) { return fmt::format("rnd v{:01X} 0x{:02X}", X(ins), NN(ins)); }},

};

void Chip8::dispatch(uint16_t ins) {
    for (auto &entry : dispatch_table) {
        if ((ins & entry.mask) == entry.instruction) {
            entry.dispatch(ins);
        }
    }
}

std::string Chip8::disassemble(uint16_t ins) {
    for (auto &entry : dispatch_table) {
        if ((ins & entry.mask) == entry.instruction) {
            return entry.disassemble(ins);
        }
    }
    // TODO exception
    return "BAD";
}