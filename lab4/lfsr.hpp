#include <stdint.h>
#include <functional>

#define WIDTH 19

// todo: make this class templated
class LFSR
{
private:
    uint64_t state;
    std::function<uint64_t(uint64_t)> pol;
public:
    LFSR(uint64_t start_state, std::function<uint64_t(uint64_t)>);
    uint64_t tick();
    uint64_t generate();
    void print_state();
};

