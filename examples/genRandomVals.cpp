#include <iostream>

#include "Random.h"

int main(int argc, char* argv[])
{
  sivelab::Random rgen( 12 );
  for (auto i=0; i<10; i++) {
    std::cout << rgen.uniform() << std::endl;
  }

  std::cout << "==========" << std::endl;
  
  for (auto i=0; i<10; i++) {
    std::cout << rgen.normal() << std::endl;
  }
}
