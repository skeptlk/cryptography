
#include <iostream>
#include <random>
#include "InfInt.h"
#include <boost/multiprecision/cpp_int.hpp>
#include "elgamal.h"

int main() 
{
    using namespace boost::multiprecision;
    PrivateKey<InfInt> k;
    k.p = InfInt("6976882500550939125137558107757723128680933316233015585964568847958873017936552628954620027285175224556261205212161354308239831857606510746429216348102244958413017171056147944588923149437327411495673361046573229976281195791981931299810486713074819291");
    k.alpha = InfInt("1236882500550939125137558107757723128680933316233015585964568847958873017936552628954620027285175224556261205212161354308239831857606510746429216348102244958413017171056147944588923149437327411495673361046573229976281195791981931299810486713074819291");
    k.z = InfInt("5853909043309393784456456828");

    ElGamal<InfInt> elg(k);

    std::cout << "after const: \n";
    PublicKey<InfInt> pk = elg.genPublicKey();
    std::cout << "pk generated: " << pk.p << " al = " << pk.alpha << "\n";

    auto hash = InfInt("21038455166264480802089952438197877812");
    SignedMessage<InfInt> sm = elg.sign(hash);
    std::cout << "message signed: sm.r = " << sm.r << "\n";

    if (ElGamal<InfInt>::verify(sm, pk)) {
        std::cout << "Yes!!!!!\n";
    } else {
        std::cout << "Error!";
    }
}
