#include <iostream>
#include <fstream>
#include "shrinking_generator.hpp"

const int key = 1337;

/**
 * g++ gamma.cpp lfsr.cpp shrinking_generator.cpp -o cypher
 * 
 * ./cypher e out < test    ## encode
 * od -t x1 out             ## print in hex
 * ./cypher d out           ## decode
 * rm out
 */

void encrypt(const char * output_filename, ShrinkingGenerator *gen)
{
    std::ofstream file(output_filename, std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "[Error:] Failed to open file\n";
        exit(1);
    }

    // get all text from standard input
    std::string input, line;
    while (std::getline(std::cin, line)) {
        input += line;
    }

    const char *inp = input.c_str();
    char * out = (char *) malloc(input.length());
    uint64_t gamma;

    for (int i = 0; i < input.length(); ++i) {
        // gamma is of 64 bits size which is 8 byte
        if (i % 8 == 0) {
            gamma = gen->gamma();
        }
        // take relevant part (8 bits) of gamma 
        char chunk = (char) (gamma >> ((i % 8) * 8));
        out[i] = inp[i] ^ chunk;
    }

    file.write(out, input.length());
}

char * decrypt(const char * input_filename, ShrinkingGenerator *gen)
{
    std::ifstream file(input_filename, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "[Error:] Failed to open file\n";
        exit(1);
    }

    // get file size
    file.seekg(0, std::ios::end);
    int file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    char *out = (char*) calloc(1, file_size + 1);
    char c;
    int i = 0;
    uint64_t gamma;
    while(file.get(c)) {
        if (i % 8 == 0) {
            gamma = gen->gamma();
        }
        char chunk = (char) (gamma >> ((i % 8) * 8));
        out[i] = c ^ chunk;
        i++;
    }

    return out;
}


int main(int argc, char ** argv) {
    if (argc < 2) {
        std::cerr << "[Error:] Specify mode (e[ncrypt] or d[ecrypt]) as first argument\n";
        return 1;
    }

    if (argc < 3) {
        std::cerr << "[Error:] Specify file name as a second argument\n";
        return 1;
    }

    auto gen = new ShrinkingGenerator(key);

    if (argv[1][0] == 'e') {
        encrypt(argv[2], gen);
    } else if (argv[1][0] == 'd') {
        auto s = decrypt(argv[2], gen);
        std::cout << s << "\n";
    } else {
        std::cerr << "[Error:] Invalid mode\n";
        return 1;
    }

}
