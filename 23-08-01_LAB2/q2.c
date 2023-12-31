// WAP to extract each byte of a given number and store them in a variable and 
// display it
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    unsigned int num = atoi(argv[1]);

    unsigned int fourthByte = num & 0xFF,
                thirdByte = (num>>8) & 0xFF,
                secondByte = (num>>16) & 0xFF,
                firstByte = (num>>24) & 0xFF;

    printf("Original number: %u\n", num);
    printf("The bytes are: %u %u %u %u", firstByte, secondByte, thirdByte, fourthByte);

    return 0;
}
