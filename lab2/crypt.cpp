#include "alphabet.h"
#include <fstream>

std::wstring encrypt_trithemius(
    const std::wstring & original, 
    const std::wstring & alphabet,
    size_t n // size of alphabet
) {
    auto alph_map = map_alphabet(alphabet);
    const int strlen = original.length();
    std::wstring result(strlen, L' ');

    for (int i = 0; i < strlen; ++i) {
        int m = alph_map[original[i]];
        int pos = (m + f(i)) % n;
        result[i] = alphabet[pos];
    }

    return result;
}

int main (int argc, char** argv) 
{
    std::setlocale(LC_ALL, "");

    std::wstring alphabet = cyrillic_alphabet;

    if (argc >= 3 && std::string(argv[1]) == "-a") {
        // set shuffled alphabet from file
        auto filename = argv[2];
        std::wifstream inp(filename, std::wifstream::in);

        if (!inp.is_open()) {
            std::cerr << "[Error:] Cannot open alphabet file " << filename << "\n"; 
            return 1;
        }
        inp >> alphabet;

        if (alphabet.length() != ALPH_N) {
            std::cerr << "[Error:] Alphabet size should be " << ALPH_N << "!\n"; 
            return 1;
        }
    } 

    std::wstring s;
    std::getline(std::wcin, s);

    std::wcout << encrypt_trithemius(s, alphabet, ALPH_N);

}
