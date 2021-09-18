#include <iostream>
#include <map>

typedef wchar_t CHAR;

#define ALPH_N 33

const CHAR cyrillic_alphabet[] = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

/**
 * Used to calculate alphabet shift for each letter
 */
int f(int x) {
    return 5 * (x * x) + 4 * x + 3;
}

std::map<CHAR, size_t> map_alphabet(const std::wstring & alph) {
    std::map<CHAR, size_t> map;
    for (int i = 0; i < alph.length(); ++i) {
        map[alph[i]] = i;
    }
    return std::move(map);
}
