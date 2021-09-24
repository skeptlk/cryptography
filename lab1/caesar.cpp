#include <iostream>
#include <unistd.h>
#include "simple_ciphers.h"

// compile: 
// g++ caesar.cpp simple_ciphers.cpp -o caesar

// run: 
// $ ./caesar -e -a 3 -k 5   -> encrypt with keys a = 3 and k = 5
// $ ./caesar -d -a 3 -k 5   -> decrypt with keys a = 3 and k = 5

enum Mode { ENCRYPT, DECRYPT };


int main (int argc, char ** argv) 
{
    Mode mode = ENCRYPT;
    int a, k; // keys

    opterr = 0;
    
    int c;
    while ((c = getopt(argc, argv, "eda:k:")) != -1)
    {
        switch (c)
        {
        case 'e': mode = ENCRYPT; break;
        case 'd': mode = DECRYPT; break;
        case 'a': a = std::atoi(optarg); break;
        case 'k': k = std::atoi(optarg); break;
        case '?':
            std::cout << "Invalid arguments!\n"
                      << "Please use -d to decrypt, -e to encrypt,\n" 
                      << "-a 123 and -k 321 to specify key parts\n";
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
        std::cout << encrypt_caesar(input, a, k);
    else 
        std::cout << decrypt_caesar(input, a, k);

}
