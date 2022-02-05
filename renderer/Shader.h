#pragma once
#include <string>

namespace renderer {

class Shader
{
public:
  virtual ~Shader();

  virtual std::string getName() = 0;

protected:
  std::string name;
};
}// namespace renderer