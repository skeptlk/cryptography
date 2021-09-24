#include <iostream>
#include <unistd.h>
#include "simple_ciphers.h"

// compile: 
// g++ scytale.cpp simple_ciphers.cpp -o scytale

// run: 
// $ ./scytale -e -k 5      -> encrypt with key = 5
// $ ./scytale -d -k 5      -> decrypt with key = 5

enum Mode { ENCRYPT, DECRYPT };

int main (int argc, char ** argv) 
{
    Mode mode = ENCRYPT;
    int k; // key

    int c;
    while ((c = getopt(argc, argv, "edk:")) != -1)
    {
        switch (c)
        {
        case 'e': mode = ENCRYPT; break;
        case 'd': mode = DECRYPT; break;
        case 'k': k = std::atoi(optarg); break;
        case '?':
            std::cout << "Invalid arguments!\n"
                      << "Please use -d to decrypt, -e to encrypt,\n" 
                      << "-k 321 to specify key\n";
            break;
        default:
            break;
        }
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