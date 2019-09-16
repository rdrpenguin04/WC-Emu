#include "ram.hpp"

bool RAMComponent::respondToRead(uint32_t loc) {
  return loc & 0xFFFF < 0x4000;
}

uint8_t RAMComponent::read(uint32_t loc) {
  return RAM[loc&0xFFFF];
}

void RAMComponent::write(uint32_t loc, uint8_t val) {
  RAM[loc&0xFFFF] = val;
}
