#include <fstream>
#include <iostream>
#include <cstdio>

#include "rom.hpp"

bool ROMComponent::respondToRead(uint32_t loc) {
  return (loc & 0xFFFF) >= 0x8000;
}

uint8_t ROMComponent::read(uint32_t loc) {
  return ROM[loc&0x7FFF];
}

void ROMComponent::write(uint32_t loc, uint8_t val) {
  // Do nothing; writing to ROM makes no sense.
}

void ROMComponent::reloadROM() {
  std::ifstream romFile{"rom/wc.bin", std::ios::in|std::ios::binary};
  size_t fileSize = 0;

  if(romFile.is_open()) {
    romFile.seekg(0, std::ios::end);
    fileSize = romFile.tellg();
    romFile.seekg(0, std::ios::beg);

    ROM.reset(new uint8_t[fileSize]);
    romFile.read((char*)ROM.get(), fileSize);
  } else {
    printf("ERROR: Couldn't load ROM file!");
  }
}
