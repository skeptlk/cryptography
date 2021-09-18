#include "shrinking_generator.hpp"

ShrinkingGenerator::ShrinkingGenerator(uint64_t key)
{
    A = new LFSR(key, [](uint16_t lfsr) {
        return ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1u;
    });

    S = new LFSR(key, [](uint16_t lfsr) {
        return ((lfsr >> 4) ^ (lfsr >> 5) ^ (lfsr >> 6) ^ (lfsr >> 12)) & 1u;
    });
}

uint64_t ShrinkingGenerator::gamma() 
{
    uint64_t result = 0;
    for (int i = 0; i < sizeof(uint64_t) * 8; ++i) {
        result |= (A->tick() & S->tick()) << i;
    }
    return result;
}