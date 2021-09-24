#include "alphabet.h"
#include <iostream>
#include <fstream>
#include <codecvt>
#include <sstream>
#include <map>
#include <numeric>

/**
 *  Count character distribution in given language
 */

std::map<CHAR, double> collect_stats(std::wifstream & file) 
{
    std::map<CHAR, int> map;
    CHAR c;

    while (file >> std::noskipws >> c) {
        map[c]++;
    }

    std::map<CHAR, int> filtered;
    // exclude non-cyrillic symbols
    for (const CHAR c: cyrillic_alphabet_ext) {
        filtered[c] = map[c];
    }

    // count map sum
    // this thing is heavily overcomplicated
    // but stl algorithms is kinda fun :)
    int sum = std::accumulate(
        filtered.begin(), 
        filtered.end(), 
        0, 
        [](double acc, const std::map<CHAR, int>::value_type& p) {
            return acc + p.second;
        }
    );

    // make a map of probabilities
    std::map<CHAR, double> dist;

    for (auto i = filtered.begin(); i != filtered.end(); ++i) {
        dist[i->first] = (double) i->second / sum;
    }

    return std::move(dist);
}

void print_stats(std::map<CHAR, double> stat) 
{
    for (CHAR ch: cyrillic_alphabet_ext) {
        if (ch) {
            std::wcout << "\"" << ch << "\" " << stat[ch] << "\n";
        }
    }
}


int main(int argc, char ** argv) {
    std::locale::global(std::locale(""));
    
    if (argc < 2) {
        std::cerr << "[Error:] Provide input file name!\n";
        return 1;
    }

    std::wifstream inp(argv[1]);

    if (!inp.is_open()) {
        std::cerr << "[Error:] Failed to open file!\n";
        return 1;
    }

    auto map = collect_stats(inp);

    print_stats(map);
}
