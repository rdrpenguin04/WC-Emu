#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include "components/ram.hpp"
#include "components/rom.hpp"
#include "bus.hpp"
#include "w65c816s.hpp"

constexpr int ver_maj{1};
constexpr int ver_min{0};

int main() {
    printf("Warp Chess Emulator v%d.%d\n"\
           "by Lightning Creations\n\n"\
           "Warp Chess by (fill in later)\n", ver_maj, ver_min);
    RAMComponent ram{};
    ROMComponent rom{};
    ExtBus bus({
        &ram,
        &rom
    });
    w65c816s cpu(bus);


    while(1) {
        printf("> ");
        char* line = NULL;
        size_t size;

        if(getline(&line, &size, stdin) != -1) {
            char * freeLine = line;
            // Minimal parser
            line[strlen(line)-1] = 0; // Remove trailing newline
            while(line[0] == ' ' || line[0] == '\t' || line[0] == '\r') line++;
            if(std::strcmp("q", line) == 0) break;
            else if(std::strcmp("info registers", line) == 0) {
                printf("C (AB)\t0x    %04X\t%d\n", cpu.getC(), cpu.getC());
                printf("X\t0x(%02X)%04X\t%d\n", cpu.getDBR(), cpu.getX(), cpu.getX());
                printf("Y\t0x(%02X)%04X\t%d\n", cpu.getDBR(), cpu.getY(), cpu.getY());
                printf("D\t0x(00)%04X\t%d\n", cpu.getD(), cpu.getD());
                printf("S\t0x(00)%04X\t%d\n", cpu.getS(), cpu.getS());
                printf("PC\t0x(%02X)%04X\t%d\n", cpu.getPBR(), cpu.getPC(), cpu.getPC());
                printf("P\t0x      %02X\t%d\n", cpu.getP(), cpu.getP());
                printf("Emulation mode: %s\n", cpu.getE() ? "true" : "false");
            } else if(std::strcmp("s", line) == 0) {
                printf("Tick took %d cycles.\n", cpu.tick());
            } else if(std::strstr(line,"read ")==line){
                line+=5;
                unsigned addr = std::strtol(line,NULL,16);
                printf("u8 at $(%X): %hhx\n",addr,bus.read(addr));
            } else if(std::strcmp("irq",line)==0){
                cpu.markIRQ();
            } else if(std::strstr(line,"connect char ")==line){
            	std::string uri{line+std::strlen("connect char ")};
            	puts("Connect Not Implemented yet");
            } else if(std::strstr(line,"connect cmd ")==line){
            	std::string uri{line+std::strlen("connect cmd ")};
            	puts("Connect Not Implemented yet");
            } else {
                printf("Undefined command: \"%s\". Try... uh, we have no help command.\n", line);
            }
            line = freeLine;
        } // else continue;
        std::free(line);
    }

    return 0;
}
