#pragma once

#include "component.hpp"
#include <memory>

class RAMComponent: public Component {
private:
  std::unique_ptr<uint8_t[]> RAM;
protected:
  
public:
  RAMComponent() : RAM{new uint8_t[4096]} {}
  ~RAMComponent()=default;

  bool respondToRead(uint32_t loc);
  uint8_t read(uint32_t loc);
  void write(uint32_t loc, uint8_t val);
};
