#pragma once

#include "component.hpp"
#include <memory>

class CharPortComponent: public Component {
private:
  FILE *output;
protected:
public:
  CharPortComponent() { output = stderr; }
  ~CharPortComponent()=default;

  bool respondToRead(uint32_t loc);
  uint8_t read(uint32_t loc);
  void write(uint32_t loc, uint8_t val);

  void setOutput(FILE *output);
};
