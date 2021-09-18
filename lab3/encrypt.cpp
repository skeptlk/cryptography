#include "alphabet.h"
#include <iostream>
#include <numeric> /* accumulate */
#include <locale> /* imbue and std::numpunct */

std::wstring encrypt_ceasar(const std::wstring & input, int k) {
    const int len = input.length();
    std::wstring result(len, ' ');
    auto map = map_alphabet((CHAR *)cyrillic_alphabet_ext);

    for (int i = 0; i < len; i++) {
        int pos = map[input[i]] + k;
        result[i] = cyrillic_alphabet_ext[pos % ALPH_N];
    }

    return result;
} 

int main() {
    std::locale::global(std::locale("ru_RU.UTF8"));

    const int key = 5;

    // get all input from cin
    std::wstring input, line;
    while (std::getline(std::wcin, line))
        input += line;

    std::wcout << encrypt_ceasar(input, key);

}


