#include <string>

std::string encrypt_caesar(const std::string& source, int a, int k);
std::string decrypt_caesar(const std::string& source, int a, int k);

std::string encrypt_scytale(const std::string& source, int key);
std::string decrypt_scytale(std::string source, int key);