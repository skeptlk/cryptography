#include <stdint.h>
#include <functional>

#define WIDTH 19

class LFSR
{
private:
    uint32_t state;
    std::function<uint32_t(uint32_t)> pol;
public:
    LFSR(uint32_t start_state, std::function<uint32_t(uint32_t)>);
    uint32_t tick();
    uint32_t generate();
    void print_state();
};

