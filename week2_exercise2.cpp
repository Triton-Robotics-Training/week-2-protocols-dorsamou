//STARTER 
//THIS EXERCISE IS TO BE DONE IN A GENERIC C++ COMPILER
//https://www.programiz.com/cpp-programming/online-compiler/
//IF YOU HAVE ISSUES WITH THE COMPILER, CONTACT EMBEDDED LEAD
const int BUFFER_SIZE = 98;
const int offset = 1;
#include <iostream>

//defines an array of 98 characters using hexidecimal unsigned bytes 
static unsigned char inputString[] = 
{0x84,0x1d,0x3d,0x74,0x1e,0x3d,0x74,0x1e,
0x3c,0x1e,0xbd,0xb4,0x7c,0x1d,0x1e,0xbd,
0xfd,0x54,0xbc,0x1e,0x7c,0xfd,0xbd,0x14,
0x9d,0xbc,0x15,0x1e,0x7c,0x3d,0x14,0x1d,
0xbc,0x54,0x9f,0x1e,0x3d,0x74,0xdd,0x94,
0x1e,0x3d,0x94,0xdf,0x1e,0xad,0xb4,0x7c,
0x1d,0x1e,0xbd,0xfd,0x54,0xbc,0x1e,0xdc,
0xb4,0xdd,0x1e,0x94,0xfd,0x1e,0x9c,0xbc,
0x7c,0xfd,0x9c,0xbc,0x3e,0x1e,0x1d,0x94,
0x94,0x14,0x74,0x57,0xff,0xff,0x14,0x7d,
0xdd,0xbc,0x74,0x74,0xdd,0xbc,0x74,0x74,
0xdf,0xfc,0x3d,0x94,0x1d,0xb4,0x5c,0xdf,
0x3d,0xfd}; //this test string should output something readable

//puts a character into the output buffer
//remember that nothing will show until you print a newline.
void putc(char c){
    printf("%c", c);
}

//puts a character into the output buffer as hexadecimal
//remember that nothing will show until you print a newline.
void putc_hex(char c){
    printf("0x%2x", (unsigned char)c);
}

//puts a character into the output buffer as binary
//remember that nothing will show until you print a newline.
void putc_bin(char c){
    for(int i = 0; i < 8; i ++){
        printf("%c", (c>>(7-i) & 1) ? '1' : '0');
    }
    
}

void decode(unsigned char *input, unsigned char *output)
{
    unsigned char temp[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; i++) {
        temp[i] = input[i];
        output[i] = 0;
        
        /* Shift the 7th, 6th, and 5th bits from temp[i] into positions 0, 1, and 2 of output[i]
           1) Shifts temp by 5 bits to the right in order to get bits 5, 6, and 7 
           2) ANDs the result with 0x07(00000111) to isolate the last 3 bits and make all the other bits 0
           3) ORs the result with output[i] to set the 0, 1, 2 bits of output[i]

           Example: temp[i] = 0b11010101
                1) temp[i] >> 5 = 0b00000110
                2) 0b00000110 & 0b00000111 = 0b00000110
                3) output[i] |= 0b00000110 *assumes output[i] = 0b00000000
                4) output[i] = 0b00000110

        */
        output[i] |= ((temp[i] >> 5) & 0x07);
        
        /*set the 3rd bit of output[i] based on the 0th bit of temp[i]
        1) ANDs temp[i] with 0x01(00000001) to isolate the last bit
        2) Shifts the result by 3 bits to the left to set the 3rd bit of output[i]
        3) ORs the result with output[i] to set the 3rd bit of output[i]
        */
        output[i] |= ((temp[i] & 0x01) << 3); 

        
        // Set the 4th bit of output[i] equal to the inverted 3rd bit of temp[i]
        output[i] |= (((temp[i] >> 3) & 0x01) ^ 0x01) << 4; 
        
        // Set the 5th bit of output[i] equal to the 4th bit of temp[i]
        output[i] |= ((temp[i] >> 4) & 0x01) << 5;  
        
        // Set the 6th and 7th bits of output[i] equal to the inverted 1st and 2nd bits of temp[i]
        output[i] |= (((temp[i] >> 1) & 0x01) ^ 0x01) << 6; 
        output[i] |= (((temp[i] >> 2) & 0x01) ^ 0x01) << 7; 
    }    
}

int main(void)
{
    unsigned char outputString[BUFFER_SIZE];
    decode(inputString, outputString);
    for(int i = 0; i < BUFFER_SIZE; i++){
        printf("inputString[%d] = ", i);
        putc_bin(inputString[i]);
        putc('\n');
        printf("outputString[%d] = ", i);
        putc_bin(outputString[i]);
        putc('\n');
        putc('\n');
    }

    for(int i = 0; i < BUFFER_SIZE; i++){
        putc(outputString[i]);
    }

    putc('\n');
    return 0;
}