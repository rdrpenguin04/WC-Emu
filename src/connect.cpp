#include "socket.hpp"
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Ready for more platform compatibility heck? Here we go!
#ifdef _WIN32
#include <conio.h>
#define changemode(x)
#else
// Code from https://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
#include <termios.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

void changemode(int dir) {
    static struct termios oldt, newt;

    if(dir == 1) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

int kbhit() {
    struct timeval tv;
    fd_set rdfs;

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    FD_ZERO(&rdfs);
    FD_SET(STDIN_FILENO, &rdfs);

    select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &rdfs);
}
#endif

const char *socket_path = "wc_connect_sock";

int main() {
    sockInit();
    std::printf("Warp Chess Connector v1.0\nby Ray Redondo\n");
    int opt = 1;
    SOCKET sock = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0);
    struct sockaddr_un addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    std::strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    if(listen(sock, 1) == -1) printf("Listening error: %d\n", errno);
    SOCKET cl = accept(sock, NULL, NULL);
    char *buf = (char*)std::malloc(sizeof(char));
    while(1) {
        changemode(1);
        while(!kbhit()) {
            int8_t received = recv(cl, buf, 1, 0);
            if(received && buf[0]) std::printf("%c", buf[0]);
        }
        changemode(0);
        printf("Meep.\n");
        char c = getchar();
        sendc(sock, c);
    }
    // sockQuit();
}
