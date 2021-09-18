#include "alphabet.h"
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>
#include <numeric> /* accumulate */
#include <iomanip>
#include <locale> /* imbue and std::numpunct */

#define PATH_TO_LANG_STAT_FILE ("./stat.dat")

enum errors {
    TOO_BIG_DEVIATION,
    UNEXPECTED_CHARACTER,
    CRITICAL_FAIL,
};


struct CrackResult
{
    int error_flag = 0;
    int key = -1;
    std::wstring orig;
    double deviation;
};


std::wstring ceasar_decrypt(const std::wstring & crypted, int k, int &err) {
    const int len = crypted.length();
    std::wstring result(len, ' ');
    auto map = map_alphabet((CHAR *)cyrillic_alphabet_ext);

    for (int i = 0; i < len; i++) {
        if (!map.count(crypted[i])) {
            err = UNEXPECTED_CHARACTER;
            return L"";
        }
        int pos = map[crypted[i]] - k;
        while (pos < 0) pos += ALPH_N;
        result[i] = cyrillic_alphabet_ext[pos % ALPH_N];
    }

    return result;
} 

/**
 * Used to set different decimal separator
 */
template <class charT, charT sep>
class punct_facet: public std::numpunct<charT> {
    protected:
        charT do_decimal_point() const { return sep; }
};

std::map<CHAR, double> read_lang_stat() {
    std::map<CHAR, double> stat;
    std::wifstream langstat(PATH_TO_LANG_STAT_FILE);
    
    if (!langstat.is_open()) {
        throw "[Error:] Failed to read statistic file!";
    }

    std::wstring line;
    while (std::getline(langstat, line))
    {
        std::wstringstream ss;
        ss.imbue(std::locale(ss.getloc(), new punct_facet<CHAR, '.'>));
        ss << line;

        CHAR ch, q /* for quote */;
        double freq;
        ss >> q >> ch >> q >> freq;
        stat[ch] = freq;
    }
    
    return std::move(stat);
} 

double deviation(std::map<CHAR, double> & a, std::map<CHAR, double> & b, int &err) {
    double dev = 0.0;
    for (CHAR c: cyrillic_alphabet_ext) {
        dev += (a[c] - b[c]) * (a[c] - b[c]);
    }
    return dev;
}

std::map<CHAR, double> count_distribution(const std::wstring & input, int &err) {
    std::map<CHAR, int> counter;
    for (CHAR c: input) {
        counter[c] += 1;
    }

    // count map sum
    // this thing is heavily overcomplicated
    // but stl algorithms is kinda fun :)
    int sum = std::accumulate(
        counter.begin(), 
        counter.end(), 
        0, 
        [](double acc, const std::map<CHAR, int>::value_type& p) {
            return acc + p.second;
        }
    );

    // make a map of probabilities
    std::map<CHAR, double> dist;

    for (const CHAR ch: cyrillic_alphabet_ext) {
        dist[ch] = (double) counter[ch] / sum;
    }

    return std::move(dist);
}

CrackResult crack_cipher(const std::wstring & input, std::map<CHAR, double> langstat) {
    double min_dev = 10e10;
    int probable_key = -1;
    std::wstring s;

    CrackResult res;
    res.key = probable_key;
    res.deviation = min_dev;
    res.error_flag = 0;
    res.orig = s;

    for (int i = 0; i < ALPH_N; i++) {
        std::wstring decr = ceasar_decrypt(input, i, res.error_flag);
        auto dist = count_distribution(decr, res.error_flag);
        auto dev = deviation(dist, langstat, res.error_flag);
        if (res.error_flag)
            return res;
        if (min_dev > dev) {
            min_dev = dev;
            probable_key = i;
            s = decr;
        }
    }

    if (min_dev > 0.1) {
        res.error_flag = TOO_BIG_DEVIATION;
    }

    return res;
}


int main() {
    std::locale::global(std::locale("ru_RU.UTF8"));


    auto stat = read_lang_stat();

    // get all input from cin
    std::wstring input, line;
    while (std::getline(std::wcin, line))
        input += line;

    auto result = crack_cipher(input, stat);

    std::wcout << result.orig << " " << result.deviation << "\n";


}

