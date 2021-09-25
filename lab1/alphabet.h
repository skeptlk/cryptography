#ifndef ALPHABET_1
#define ALPHABET_1

#include <iostream>
#include <map>


typedef char CHAR;

#define ALPH_N (sizeof(alphabet_arr)/sizeof(CHAR) - 1)

std::map<CHAR, int> alphabet_map {
    {'A', 0},  {'B', 1},  {'C', 2},
    {'D', 3},  {'E', 4},  {'F', 5},
    {'G', 6},  {'H', 7},  {'I', 8},
    {'J', 9},  {'K', 10}, {'L', 11},
    {'M', 12}, {'N', 13}, {'O', 14},
    {'P', 15}, {'Q', 16}, {'R', 17},
    {'S', 18}, {'T', 19}, {'U', 20},
    {'V', 21}, {'W', 22}, {'X', 23},
    {'Y', 24}, {'Z', 25}, {' ', 26},
    {'.', 27}, {',', 28},
};

const CHAR alphabet_arr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ .,";

int gcd(int n1, int n2);


#endif // ALPHABET