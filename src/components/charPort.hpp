#pragma once

#include "component.hpp"
#include "../socket.hpp"
#include <memory>

class CharPortComponent: public Component {
private:
  SOCKET sock;
protected:
public:
  CharPortComponent() {}
  ~CharPortComponent()=default;

  bool respondToRead(uint32_t loc);
  uint8_t read(uint32_t loc);
  void write(uint32_t loc, uint8_t val);

  void conn();
};
