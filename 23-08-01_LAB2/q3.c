/*
3. WAP to extract each byte as a character from the representation of multi-byte data types and store the extracted bytes in the following structure:
struct Packet {
	char a1;
	char a2[2];
	char a3;
}
and display the contents of the structure
*/

#include <stdio.h>

struct Packet {
    char a1;
    char a2[2];
    char a3;
};

int main(){
    struct Packet ch;

    int c = 0x0F0F0F0F;
    
    ch.a1 = (c >> 24) & 0xFF;
    ch.a2[0] = ( c >> 16 ) & 0xFF;
    ch.a2[1] = ( c >> 8 ) & 0xFF;
    ch.a3 = c & 0xFF;

    printf("Bytes are: %d %d %d %d\n", ch.a1, ch.a2[0], ch.a2[1], ch.a3);
}