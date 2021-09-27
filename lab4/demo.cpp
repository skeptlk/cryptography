
#include "shrinking_generator.hpp"
#include <bitset>

int main ()
{
    ShrinkingGenerator gen(115502235080362L);

    auto g = gen.gamma();

    std::cout << "Gamma: " 
            << std::dec << g << " " 
            << std::hex << g << "\n";

    std::bitset<sizeof(g) * 8> bin(g);

    std::cout << "binary: " << bin << "\n";

}

