#include "alphabet.h"

/**
 * inv[k] is a such number that (inv[K] * K) % n = 1 
 */
int inv(int k, int n) {
    int i = 1;
    while (i < 100) {
        if ((i * k) % n == 1)
            return i;
        i++;
    }
    throw "Cannot find inv";
}

/**
 *      Аффинная система подстановок Цезаря
 */

std::string encrypt_caesar(const std::string& source, int a, int k) {
    std::string result(source.length(), ' ');

    for (int i = 0; i < source.length(); ++i) {
        CHAR ch = source[i];
        const int pos = alphabet_map[ch];
        const int shift = (a * pos + k) % ALPH_N;
        CHAR ch2 = alphabet_arr[shift];
        result[i] = ch2;
    }

    return result;
}

std::string decrypt_caesar(const std::string& source, int a, int k) {
    std::string result(source.length(), ' ');

    for (int i = 0; i < source.length(); ++i) {
        CHAR ch = source[i];
        const int pos = alphabet_map[ch];
        const int shift = (inv(a, ALPH_N) * (pos + ALPH_N - k)) % ALPH_N;
        CHAR ch2 = alphabet_arr[shift];
        result[i] = ch2;
    }

    return result;
}

/**
 *      Шифр "скитала"
 */

std::string encrypt_scytale(const std::string& source, int key) {
    const int len = source.length();
    // key = number of rows
    // count number of pivots
    const int n = ((len - 1) / key) + 1;
    std::string result(n * key, ' ');

    for (int i = 0; i < len; ++i) {
        // calculate shift
        int j = (i / n) + key * (i % n);
        result[j] = source[i];
    }

    return result;
}

std::string decrypt_scytale(std::string source, int key) {
    const int len = source.length();
    // key = number of rows
    // count number of pivots
    const int n = ((len - 1) / key) + 1;
    std::string result(n * key, ' ');

    for (int i = 0; i < len; ++i) {
        // calculate shift
        int j = (i / key) + n * (i % key);
        result[j] = source[i];
    }

    return result;
}
