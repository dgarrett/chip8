#pragma once

inline uint16_t swap(uint16_t x) {
    return ((x & 0xff) << 8) | ((x & 0xff00) >> 8);
}

inline uint16_t NNN(uint16_t ins) {
    return ins & 0xfff;
}

inline uint8_t NN(uint16_t ins) {
    return ins & 0xff;
}

inline uint8_t X(uint16_t ins) {
    return (ins & 0xf00) >> 8;
}