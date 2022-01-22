
#include "Vector3D.h"
#include "Random.h"

int main(int argc, char* argv[])
{
    sivelab::Vector3D C(0.0f, 0.0f, -5.0f), P;
    float r = 1.0f;
    
	sivelab::Random randGen;

    // generate some random unit vectors and add them to C
    for (int i=0; i<5; i++) {
        P[0] = (randGen.uniform() * 2.0) - 1.0;
        P[1] = (randGen.uniform() * 2.0) - 1.0;
        P[2] = (randGen.uniform() * 2.0) - 1.0;
        // P.normalize();
        std::cout << "C+P = " << C+P << ", length = " << P.length() << std::endl;
    }
    
}
