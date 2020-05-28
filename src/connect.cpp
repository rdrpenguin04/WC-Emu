#include "socket.hpp"
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Ready for more platform compatibility heck? Here we go!
#ifdef _WIN32
#include <conio.h>
#else
// Code from https://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
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
        while(!kbhit()) {
            int8_t received = recv(cl, buf, 1, 0);
            if(received) std::printf("%c", buf[0]);
        }
        char c = getchar();
        putc(c, stdout);
        sendc(sock, c);
    }
    // sockQuit();
}
