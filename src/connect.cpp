#include "socket.hpp"
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const char *socket_path = "wc_connect_sock";


int main() {
    sockInit();
    std::printf("Warp Chess Connector v1.0\nby Ray Redondo\n");
    int opt = 1;
    SOCKET sock = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    std::strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    if(listen(sock, 1) == -1) printf("Listening error: %d\n", errno);
    SOCKET cl = accept(sock, NULL, NULL);
    char *buf = (char*)std::malloc(sizeof(char));
    while(1) {
        recv(cl, buf, 1, 0);
        std::printf("%c", buf[0]);
    }
    // sockQuit();
}
