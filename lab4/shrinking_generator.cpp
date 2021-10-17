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
    uint64_t bitcount  = 0;
    while (bitcount < sizeof(uint64_t) * 8) 
    {
        #ifdef VERBOSE
            auto a_tick = A->tick();
            auto s_tick = S->tick();
            std::cout << "=====\n";
            std::cout << "A bit: " << a_tick << "\n";
            std::cout << "A state: \n";
            A->print_state();
            std::cout << "S bit: " << s_tick << "\n";
            std::cout << "S state: \n";
            S->print_state();

            if (a_tick) {
                result |= s_tick << bitcount;
            }
            bitcount++;

        #else
            if (A->tick()) {
                result |= S->tick() << bitcount;
                bitcount++;
            } else {
                S->tick();
            }
        #endif
    }

    return result;
}