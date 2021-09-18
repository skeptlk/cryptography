#include <stdint.h>
#include <functional>


class LFSR
{
private:
    uint16_t state;
    std::function<uint16_t(uint16_t)> pol;
public:
    LFSR(uint16_t start_state, std::function<uint16_t(uint16_t)>);
    uint16_t tick();
    uint16_t generate();
};

