#include <string>
#include <map>

#define ALPH_N 40
typedef wchar_t CHAR;
const CHAR cyrillic_alphabet[] = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
const CHAR cyrillic_alphabet_ext[] = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя ,.-:!?";

std::map<CHAR, int> map_alphabet(const std::wstring & alph) {
    std::map<CHAR, int> map;
    for (int i = 0; i < alph.length(); ++i) {
        map[alph[i]] = i;
    }
    return std::move(map);
}
