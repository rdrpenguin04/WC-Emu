#include <cstdio>
#include <cstring>
#include "bus.hpp"
#include "w65c816s.hpp"

int main() {
    printf("Warp Chess Emulator v%d.%d\nby Lightning Creations\n\nWarp Chess by (fill in later)\n", 1, 0);

    ExtBus bus;
    w65c816s cpu(bus);

    while(1) {
        printf("> ");
        char *line = NULL;
        size_t size;
        if(getline(&line, &size, stdin) != -1) {
            // Minimal parser
            line[strlen(line)-1] = 0; // Remove trailing newline
            if(strcmp("q", line) == 0) break;
        } // else continue;
    }

    return 0;
}
