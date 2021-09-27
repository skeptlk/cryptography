#include "lfsr.hpp"
#include <bitset>
#include <iostream>

LFSR::LFSR(uint32_t start_state, std::function<uint32_t(uint32_t)> lambda)
{
    state = start_state;
    pol = lambda;
}

uint32_t LFSR::tick() {
    uint32_t bit = pol(state);
    state &= 0b00000000000001111111111111111111;
    state = (state >> 1) | (bit << (WIDTH - 1));
    return bit;
}

uint32_t LFSR::generate() {
    uint32_t result = 0;
    for (int i = 0; i < (sizeof(uint32_t) * 8); ++i) {
        uint32_t bit = pol(state);
        state = (state >> 1) | (bit << (WIDTH - 1));
        result |= bit << i;
    } 
    return result;
}

void LFSR::print_state() {
    std::bitset<WIDTH> set(state);
    std::cout << set << std::endl;
    std::cout << std::dec << "\n";
}
