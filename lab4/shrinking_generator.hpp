#include "lfsr.hpp"


class ShrinkingGenerator 
{
private: 
    LFSR *A; // generates sequence 
    LFSR *S; // decides discard bit or not
public:
    ShrinkingGenerator(uint64_t key);
    uint64_t gamma();
};


