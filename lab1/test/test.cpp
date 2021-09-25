#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE Test1

#include <boost/test/included/unit_test.hpp>
#include <string>
#include <random>
#include "../simple_ciphers.h"

// compile: g++ test.cpp ../simple_ciphers.cpp -lboost_unit_test_framework 

BOOST_AUTO_TEST_SUITE(Ceasar);

BOOST_AUTO_TEST_CASE(SimpleString)
{
	std::string s = "THIS IS A LONG TEST PHRASE WITH, PUNCTUATION.";
	int a = 3, k = 5;
	std::string e = encrypt_caesar(s, a, k);
	std::string r = decrypt_caesar(e, a, k);

	BOOST_CHECK(s != e);
	BOOST_CHECK(s == r);
}

BOOST_AUTO_TEST_CASE(RandomString)
{
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, ALPH_N - 1);

	const int len = 1000;
	std::string str(len, ' ');

	// generate random string of length 1000
	for (int i = 0; i < len; ++i) {
		str[i] = alphabet_arr[distr(gen)];
	}

	int a = 3, k = 5;
	std::string e = encrypt_caesar(str, a, k);
	std::string r = decrypt_caesar(e, a, k);

	BOOST_CHECK(str != e);
	BOOST_CHECK(str == r);
}


BOOST_AUTO_TEST_SUITE_END();
