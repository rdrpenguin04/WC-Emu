#pragma once

#include "component.hpp"
#include <memory>

class ROMComponent: public Component {
private:
  std::unique_ptr<uint8_t[]> ROM;
protected:
  
public:
  ROMComponent() : ROM{new uint8_t[0x8000]} {
    reloadROM();
  }
  ~ROMComponent() = default;
  bool respondToRead(uint32_t loc);
  uint8_t read(uint32_t loc);
  void write(uint32_t loc, uint8_t val);

  void reloadROM();
};
