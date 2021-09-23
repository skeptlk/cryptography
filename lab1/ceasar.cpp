#include <iostream>
#include "simple_ciphers.h"

// compile: 
// g++ ceasar.cpp simple_ciphers.cpp -o ceasar

// run: 
// $ ./ceasar e 3 5      -> encrypt with keys a = 3 and k = 5
// $ ./ceasar d 3 5      -> decrypt with keys a = 3 and k = 5

enum Mode { ENCRYPT, DECRYPT };

int main (int argc, char ** argv) 
{
    Mode mode = ENCRYPT;
    int a, k; // keys

    if (argc > 3) {
        if (argv[1][0] == 'e')
            mode = ENCRYPT;
        else if (argv[1][0] == 'd')
            mode = DECRYPT;
        else {
            std::cerr << "[Error]: Incorrect mode argument\n";
            return 1;
        }
        a = std::atoi(argv[2]);
        if (a <= 0) {
            std::cerr << "[Error:] Invalid a key\n";
            return 1;
        }
        k = std::atoi(argv[3]);
        if (k <= 0) {
            std::cerr << "[Error:] Invalid k key\n";
            return 1;
        }
    } else {
        std::cerr << "[Error:] Provide arguments\n";
        return 1;
    }

    // get all input from cin
    std::string input, line;
    while (std::getline(std::cin, line))
        input += line;

    if (mode == ENCRYPT)
        std::cout << encrypt_ceasar(input, a, k);
    else 
        std::cout << decrypt_ceasar(input, a, k);

}
