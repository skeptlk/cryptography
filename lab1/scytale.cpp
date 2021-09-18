#include <iostream>
#include "simple_ciphers.h"

// compile: 
// g++ scytale.cpp simple_ciphers.cpp -o scytale

// run: 
// $ ./scytale e 5      -> encrypt with key = 5
// $ ./scytale d 5      -> decrypt with key = 5

enum Mode { ENCRYPT, DECRYPT };

int main (int argc, char ** argv) 
{
    Mode mode = ENCRYPT;
    int k; // key

    if (argc > 2) {
        if (argv[1][0] == 'e')
            mode = ENCRYPT;
        else if (argv[1][0] == 'd')
            mode = DECRYPT;
        else {
            std::cerr << "[Error:] Incorrect mode argument\n";
            return 1;
        }
        k = std::atoi(argv[2]);
        if (k <= 0) {
            std::cerr << "[Error:] Invalid key\n";
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
        std::cout << encrypt_scytale(input, k);
    else 
        std::cout << decrypt_scytale(input, k);
}