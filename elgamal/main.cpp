
#include <iostream>
#include <random>
#include "InfInt.h"


/**
 * Find the greatest common divisor (Euclid)
 */
template<typename T>
T gcd(T n1, T n2) 
{
    while(n1 != n2)
    {
        if(n1 > n2)
            n1 -= n2;
        else
            n2 -= n1;
    }
    return n1;
}

// todo: move inside class
std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_real_distribution<float> distr(0.0, 1.0);


InfInt power(InfInt base, InfInt n) 
{
    InfInt r = base;
    while (--n > 0) r *= base; 
    return r;
}

InfInt inverse(InfInt k, InfInt n)
{
    InfInt i = 1;
    while (i < n) {
        if ((i * k) % n == 1)
            return i;
        i++;
    }
    throw "Cannot find inv";
}

struct PublicKey {
    InfInt p;       // large prime
    InfInt alpha;   // primitive root
    InfInt beta;    // = alpha ** z mod p
};

struct PrivateKey
{
    InfInt z;       // secret integer
    InfInt p;       // large prime
    InfInt alpha;   // primitive root
};

struct SignedMessage {
    InfInt m; // message hash
    InfInt r; // = alpha**k mod p
    InfInt s; // = inv[k] * (m - z * r)
};


class ElGamal {
private:
    InfInt p, alpha, beta, z;
public: 
    ElGamal(PrivateKey key) {
        p = key.p;            // big prime
        alpha = key.alpha;    // primitive root
        z = key.z;            // secret key
        beta = power(alpha, z) % p;
    }
    SignedMessage sign(InfInt m) {
        SignedMessage res;

        InfInt key = keygen(); // key is not stored anywhere!
        InfInt r = power(alpha, key) % p;

        InfInt s = ((InfInt) m - r * z) * inverse(key, p - 1);
        while (s < 0) s += p - 1;
        s %= p - 1;

        res.s = s;
        res.m = m;
        res.r = r;

        std::cout << "s=" << s << " m=" << m << " r=" << r << "\n";

        return res;
    }

    InfInt keygen() {
        return 31;
        InfInt k;
        do {
            k = (p * int(10000 * distr(eng))) / int(10000 * distr(eng));
            k %= p;
        } while (k <= 0 || gcd(k, p - 1) != 1);
        return k;
    }

    static bool verify(SignedMessage sign, PublicKey pk) {
        InfInt v1 = pk.beta.powmod(sign.r, pk.p) * sign.r.powmod(sign.s, pk.p);
        v1 %= pk.p;
        InfInt v2 = pk.alpha.powmod(sign.m, pk.p);

        return v1 == v2;
    }

    PublicKey genPublicKey() {
        PublicKey pk;
        pk.p = p;
        pk.alpha = alpha;
        pk.beta = power(alpha, z) % p;

        return pk;
    }

};

int main() 
{
    PrivateKey k;
    k.p = 131071;
    k.alpha = 7;
    k.z = 16;

    ElGamal elg(k);

    PublicKey pk = elg.genPublicKey();

    SignedMessage sm = elg.sign(15);

    if (ElGamal::verify(sm, pk)) {
        std::cout << "Yes!!!!!\n";
    } else {
        std::cout << "Blyat :(\n";
    }
}
