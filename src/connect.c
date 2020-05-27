#include <stdio.h>
#include <unistd.h> // Linux only for the moment

int main() {
    printf("Warp Chess Connector v1.0\nby Ray Redondo\nTo use with the emulator, type:\n    connect char %i\nand then run the program!\n", getpid());
    for(;;); // Yeah, I'll make a useful loop later
}
