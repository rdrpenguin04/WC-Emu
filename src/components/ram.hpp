#pragma once

#include "component.hpp"

class RAMComponent: public Component {
private:
  uint8_t *RAM;
protected:
  ~RAMComponent()=default;
public:
  RAMComponent() {
    RAM = new uint8_t[0x4000];
  }
  bool respondToRead(uint32_t loc);
  uint8_t read(uint32_t loc);
  void write(uint32_t loc, uint8_t val);
};
