#include "alphabet.h"
#include <fstream>

std::wstring decrypt_trithemius(
    const std::wstring & crypted, 
    const std::wstring & alphabet,
    size_t n // size of alphabet
) {
    auto alph_map = map_alphabet(alphabet);
    const int strlen = crypted.length();
    std::wstring result(strlen, L' ');

    for (int i = 0; i < strlen; ++i) {
        int L = alph_map[crypted[i]];
        int diff = L - f(i);
        while (diff < 0) 
            diff += ALPH_N;
        int pos = (diff) % ALPH_N;
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

    std::wcout << decrypt_trithemius(s, alphabet, ALPH_N);

}
