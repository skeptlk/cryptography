#include "lfsr.hpp"
#include <bitset>
#include <iostream>

LFSR::LFSR(uint64_t start_state, std::function<uint64_t(uint64_t)> lambda)
{
    state = start_state;
    pol = lambda;
}

uint64_t LFSR::tick() {
    uint64_t bit = pol(state);
    state = (state >> 1) | (bit << (WIDTH - 1));
    return bit;
}

uint64_t LFSR::generate() {
    uint64_t result = 0;
    for (int i = 0; i < (sizeof(uint64_t) * 8); ++i) {
        uint64_t bit = pol(state);
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
