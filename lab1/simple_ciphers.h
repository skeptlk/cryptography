#ifndef SIMPLE_CIPHERS
#define SIMPLE_CIPHERS

#include <string>
#include "alphabet.h"

std::string encrypt_caesar(const std::string& source, int a, int k);
std::string decrypt_caesar(const std::string& source, int a, int k);

std::string encrypt_scytale(const std::string& source, int key);
std::string decrypt_scytale(std::string source, int key);

#endif // SIMPLE_CIPHERS
