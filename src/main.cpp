#include <cstdio>
#include <cstring>
#include "bus.hpp"
#include "w65c816s.hpp"

int main() {
    printf("Warp Chess Emulator v%d.%d\n"\
           "by Lightning Creations\n\n"\
           "Warp Chess by (fill in later)\n", 1, 0);

    ExtBus bus;
    w65c816s cpu{bus};

    while(1) {
        printf("> ");
        char *line = NULL;
        size_t size;
        if(getline(&line, &size, stdin) != -1) {
            // Minimal parser
            line[strlen(line)-1] = 0; // Remove trailing newline
            while(line[0] == ' ' || line[0] == '\t' || line[0] == '\r') line++;
            if(strcmp("q", line) == 0) break;
            else if(strcmp("info registers", line) == 0) {
                printf("C (AB)\t0x    %04X\t%d\n", cpu.getC(), cpu.getC());
                printf("X\t0x(%02X)%04X\t%d\n", cpu.getDBR(), cpu.getX(), cpu.getX());
                printf("Y\t0x(%02X)%04X\t%d\n", cpu.getDBR(), cpu.getY(), cpu.getY());
                printf("D\t0x(00)%04X\t%d\n", cpu.getD(), cpu.getD());
                printf("S\t0x(00)%04X\t%d\n", cpu.getS(), cpu.getS());
                printf("PC\t0x(%02X)%04X\t%d\n", cpu.getPBR(), cpu.getPC(), cpu.getPC());
            }
        } // else continue;
    }

    return 0;
}
