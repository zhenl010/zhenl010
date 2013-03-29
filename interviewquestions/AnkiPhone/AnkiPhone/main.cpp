#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#define UINT_XMAX 0xFFFFFFFF

// bit vise reverse
// 0110111000101001 => 1001010001110110
unsigned int UintReverse(unsigned int x) {
    unsigned int y = 0;
    for (char i=0; i<32; ++i) {
        y = (y<<1) | (x&1);
        x >>= 1;
    }
    return y;
}

// leetcode version using swap
unsigned int SwapBits(unsigned int x, unsigned char i, unsigned char j) {
    unsigned int y = (x>>i) & 1;
    unsigned int z = (x>>j) & 1;
    if (y ^ z) { // do swap only of they differ!
        x ^= ((1<<i) | (1<<j));
    }
    return x;
}

typedef unsigned int uint;
uint reverseMask(uint x) {
    assert(sizeof(x) == 4); // special case: only works for 4 bytes (32 bits).
    x = ((x & 0x55555555) << 1) | ((x & 0xAAAAAAAA) >> 1);
    x = ((x & 0x33333333) << 2) | ((x & 0xCCCCCCCC) >> 2);
    x = ((x & 0x0F0F0F0F) << 4) | ((x & 0xF0F0F0F0) >> 4);
    x = ((x & 0x00FF00FF) << 8) | ((x & 0xFF00FF00) >> 8);
    x = ((x & 0x0000FFFF) << 16) | ((x & 0xFFFF0000) >> 16);
    return x;
}

void PrintUint(unsigned int x) {
    for (char i=0; i<32; ++i) {
        if (x & 1) { putchar('1'); } else { putchar('0'); }
        x >>= 1;
    }
}

// Implement memcpy function which accepts num of bits as argument as oppose to number of bytes. 
// Notice the signature defers from <cstdlib>
// void * memcpy ( void * destination, const void * source, size_t num );
// To avoid overflows, the size of the arrays pointed by both the destination and source parameters,
// shall be at least num bits, and should not overlap
void MemCopy (const void* src, void* dst, int num) { // num as number of bits
    int bit_num = num % 8;
    num = num / 8;
    memcpy(dst, src, num);
    if (0 < bit_num) {
        unsigned char mask = (1<<bit_num) - 1;
        ((char*)dst)[num] = (((char*)dst)[num] & (~mask)) | (((char*)src)[num] & mask);
    }
}

unsigned int lowbit(unsigned int x) {
    return x & (~x + 1);
}

int NumberOfOnes(unsigned int x) {
    int cnt = 0;
    while (x>0) {
        ++cnt;
        x -= lowbit(x);
    }
    return cnt;
}

int number_of_ones(unsigned int x) {
    int total_ones = 0;
    while (x != 0) {
        x = x & (x-1);
        total_ones++;
    }
    return total_ones;
}

int main() {
    unsigned int x = 1750;
    printf("x: ");
    PrintUint(x);
    printf("\n");
    x = UintReverse(x);
    printf("x: ");
    PrintUint(x);
    printf("\n\n");

    // char src[] = "cstring can be very useful......";
    char src[] = "AbC";
    // memmove(src+20,src+15,11);
    puts(src);
    // char str[] = "................................";
    char str[] = "xYz";
    puts(str);
    printf("\n\n");
    for(int i=1; i<=8*(sizeof(src)-1); ++i) {
        // memcpy(str, src, i);
        MemCopy(src, str, i);
        puts(src);
        puts(str);
    }

    printf("\n\n");
    for (unsigned int x=0; x<100; ++x) {
        if(number_of_ones(x) != NumberOfOnes(x)) {
            printf("%d %d\n", NumberOfOnes(x), number_of_ones(x));
        }
    }

    return 0;
}