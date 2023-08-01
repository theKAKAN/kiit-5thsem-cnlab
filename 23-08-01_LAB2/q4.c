/*
4. WAP to modify the program no. 3 to regenerate original numbers
from the structure member and also display the total number
*/

#include <stdio.h>

struct Packet {
    char a1;
    char a2[2];
    char a3;
};

int main(){
    struct Packet ch;

    int c = 0x0A0B0C0D;
    
    ch.a1 = (c >> 24) & 0xFF;
    ch.a2[0] = ( c >> 16 ) & 0xFF;
    ch.a2[1] = ( c >> 8 ) & 0xFF;
    ch.a3 = c & 0xFF;

    int regain = ( (ch.a1 << 24) | (ch.a2[0] << 16) | (ch.a2[1] << 8) | ch.a3 );

    printf("Bytes are: %d %d %d %d\n", ch.a1, ch.a2[0], ch.a2[1], ch.a3);
    printf("Original: %d; Remade: %d\n", c, regain);
}