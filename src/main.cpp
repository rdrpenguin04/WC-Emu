#include <cstdio>
#include "bus.hpp"
#include "w65c816s.hpp"

int main() {
    printf("Warp Chess Emulator v%d.%d\nby Lightning Creations\n\nWarp Chess by (fill in later)\n", 1, 0);

    Bus bus;
    w65c816s cpu(bus);

    return 0;
}
