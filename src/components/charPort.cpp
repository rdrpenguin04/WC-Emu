#include <cstdio>

#include "charPort.hpp"

bool CharPortComponent::respondToRead(uint32_t loc) {
  return 0; // WIP
}

uint8_t CharPortComponent::read(uint32_t loc) {
  return 0; // WIP
}

void CharPortComponent::write(uint32_t loc, uint8_t val) {
  if(loc == 0x4800) fprintf(stderr, "%c", val);
}

