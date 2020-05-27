#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "charPort.hpp"

bool CharPortComponent::respondToRead(uint32_t loc) {
  return 0; // WIP
}

uint8_t CharPortComponent::read(uint32_t loc) {
  return 0; // WIP
}

void CharPortComponent::write(uint32_t loc, uint8_t val) {
  if(loc == 0x4800) sendc(sock, val);
}

void CharPortComponent::conn() {
  sock = socket(AF_UNIX, SOCK_STREAM, 0);
  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, "wc_connect_sock", sizeof(addr.sun_path)-1);
  if(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1) std::fprintf(stderr, "Error: Could not connect to the socket.\nCode: %d\n", errno);
}
