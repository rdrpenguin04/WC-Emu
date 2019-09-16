#pragma once

#include "component.hpp"

class ROMComponent: public Component {
private:
  uint8_t *ROM;
protected:
  ~ROMComponent() = default;
public:
  ROMComponent() {
    ROM = new uint8_t[0x8000];
    reloadROM();
  }
  bool respondToRead(uint32_t loc);
  uint8_t read(uint32_t loc);
  void write(uint32_t loc, uint8_t val);

  void reloadROM();
};
