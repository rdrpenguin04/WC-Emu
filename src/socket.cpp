#include <cerrno>
#include <cstdlib>
#include <cstdio>
#include "socket.hpp"

int sockInit() {
  #ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1,1), &wsa_data);
  #else
    return 0;
  #endif
}

int sockQuit() {
  #ifdef _WIN32
    return WSACleanup();
  #else
    return 0;
  #endif
}

int sockClose(SOCKET sock) {
  int status = 0;

  #ifdef _WIN32
    status = shutdown(sock, SD_BOTH);
    if (status == 0) { status = closesocket(sock); }
  #else
    status = shutdown(sock, SHUT_RDWR);
    if (status == 0) { status = close(sock); }
  #endif

  return status;
}

int sendc(SOCKET sock, char ch) {
  char *buf = (char*) std::malloc(sizeof(char));
  buf[0] = ch;
  int result;
  while((result = send(sock, buf, 1, 0)) == 0);
  if(result == -1) std::printf("ERROR AAAA: %d\n", errno);
  std::free(buf);
  return result;
}
