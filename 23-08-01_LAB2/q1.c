// WAP to extract the first byte and last byte of an unsigned integer
// using command line arguments
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    unsigned int num = atoi(argv[1]);
    unsigned int lsb = num & 0xFF;

    unsigned int msb = (num >> 24) & 0xFF;

    printf("Original number: %u\n", num);
    printf("First byte: %d\n", msb);
    printf("Last byte: %d\n", lsb);

    return 0;
}
