#pragma once

uint16_t NNN(uint16_t ins) {
    return ins & 0xfff;
}

uint8_t NN(uint16_t ins) {
    return ins & 0xff;
}