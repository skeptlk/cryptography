#include "alphabet.h"
#include <random>

std::wstring generate_key(int n) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, ALPH_N - 1); // define the range

    std::wstring result(n, ' ');

    for(int i = 0; i < n; ++i) {
        result[i] = cyrillic_alphabet[distr(gen)];
    }

    return result;
}

int main (int argc, char** argv) {
    std::setlocale(LC_ALL, "");

    if (argc < 2) {
        std::cerr << "[Error:] Provide key length!\n"; 
        return 1;
    }

    int n = std::stoi(argv[1]);

    if (n <= 1) {
        std::cerr << "[Error:] Key length should be greater than 1!\n"; 
        return 1;
    }

    std::wcout << generate_key(n);


}
