#include "lfsr.hpp"



LFSR::LFSR(uint16_t start_state, std::function<uint16_t(uint16_t)> lambda)
{
    state = start_state;
    pol = lambda;
}

uint16_t LFSR::tick() {
    uint16_t bit = pol(state);
    state = (state >> 1) | (bit << 15);
    return bit;
}

uint16_t LFSR::generate() {
    uint16_t result = 0;
    for (int i = 0; i < sizeof(uint16_t) * 8; ++i) {
        uint16_t bit = pol(state);
        state = (state >> 1) | (bit << 15);
        result |= bit << i;
    } 
    return result;
}
