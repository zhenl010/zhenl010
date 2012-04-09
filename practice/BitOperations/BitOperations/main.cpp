#include <iostream>
#include <string>

//////////////////////////////////////////////////////////////////////////
// Count '1' bits
//////////////////////////////////////////////////////////////////////////
int CountOneBits(int num)
{
    int count = 0;
    int clone = num;
    while (clone != 0)
    {
        ++count;
        clone = clone & (clone - 1);
    }
    return count;
}

//////////////////////////////////////////////////////////////////////////
// Operations needed to convert an interger to another
//////////////////////////////////////////////////////////////////////////
int OpsNumToConvert(int a, int b)
{
    return CountOneBits(a ^ b);
}

//////////////////////////////////////////////////////////////////////////
// Return the next integer with the same number of '1' bits
// Assume there's still some left before reaching the limit
//////////////////////////////////////////////////////////////////////////
int NextIntSameOneBits(const int& num, int maxdigits = 32) // 32bits as default
{
    int number = num;
    int first_one_pos = 0;
    while ( (first_one_pos<maxdigits) && ((number & 1) == 0) )
    {
        number = number >> 1;
        ++first_one_pos;
    }

    int first_zero_pos = first_one_pos;
    while ( (first_zero_pos<maxdigits) && ((number & 1) == 1) )
    {
        number = number >> 1;
        ++first_zero_pos;
    }
    // overflow if first_zero_pos >= maxdigits

    number = num;
    int result = ((number >> first_zero_pos) + 1) << first_zero_pos;
    result += ((1 << (first_zero_pos-first_one_pos-1)) - 1);

    return result;
}

//////////////////////////////////////////////////////////////////////////
// Insert small into large starting at bit j and end at bit i
// assume i and j are correct that allow small to fit
//////////////////////////////////////////////////////////////////////////
void InsertBits(int& large, const int& small, int i, int j)
{
    large = (large | ( ((1 << (j-i+1))-1) << j ) ) & ( (small << j) | ( ~( ((1 << (j-i+1))-1) << j ) ) );
}

//////////////////////////////////////////////////////////////////////////
// Return the binary representation of a number between 0 and 1
//////////////////////////////////////////////////////////////////////////
std::string BinaryRepresentation(double prob, int length)
{
    using namespace std;
    string result;

    if (prob<0.0 || 1.0<prob)
    {
        return result;
    }

    result.resize(length, '0');
    result[0] = '.';
    double num = prob * 2.0;
    for (int i=0; i<length; ++i)
    {
        if (num < 1.0)
        {
        }
        else
        {
            result[i] = '1';
            num -= 1.0;
        } 

        num *= 2.0;
    }

    return result;
}

bool GetBit(int num, int pos)
{
    return (num & (1 << pos)) != 0;
}

void CoutAsBits(int num)
{
    for (int i=0; i<32; ++i)
    {
        if (GetBit(num, i))
        {
            std::cout << "1";
        } 
        else
        {
            std::cout << "0";
        }
    }
};

//////////////////////////////////////////////////////////////////////////
// monochrome screen saved as single array of bytes
// pixel(x,y) would be screen[y*width/8+x/8]'s x%8 bit @@
// it gets tricky with the optimization trick to set the 8 pixels in a byte together
//////////////////////////////////////////////////////////////////////////
// HATE it!
//////////////////////////////////////////////////////////////////////////
void DrawHorizontalLine(unsigned char screen[], int width, int x1, int x2, int y)
{
    unsigned char flagmask = UCHAR_MAX;
    int widbytes = width >> 3;
    int lfp = std::min(x1, x2);
    int rtp = std::max(x1, x2);
    int start_idx = y * widbytes + lfp >> 3;
    int start_rtd = 8 - lfp % 8;
    int end_idx = y * widbytes + rtp >> 3;
    int end_lfd = rtp % 8;
//...
}

int main(int argc, char** argv)
{
    using namespace std;

    int largeint = 1 << 20;
    int smallint = (1 << 4) + 3;

    CoutAsBits(largeint);
    cout << endl;
    CoutAsBits(smallint);
    cout << endl;

    InsertBits(largeint, smallint, 2, 6);
    CoutAsBits(largeint);
    cout << endl;

    cout << endl;
    cout << endl;
    cout << BinaryRepresentation(0.25, 32) << endl;
    cout << BinaryRepresentation(0.5, 32) << endl;
    cout << BinaryRepresentation(0.75, 32) << endl;
    cout << BinaryRepresentation(0.26, 32) << endl;
    cout << endl;

    cout << endl;
    cout << NextIntSameOneBits(1) << endl;
    cout << NextIntSameOneBits(3) << endl;
    cout << NextIntSameOneBits(7) << endl;
    cout << NextIntSameOneBits(26) << endl;
    cout << endl;

    cout << endl;
    cout << OpsNumToConvert(14, 31) << endl;
    cout << endl;

    const int SCREEN_BYTE_NUM = 256*256/8;
    const int SCREEN_WIDTH = 256*8;
    unsigned char screen[SCREEN_BYTE_NUM];

    DrawHorizontalLine(screen, SCREEN_WIDTH, SCREEN_WIDTH/4, SCREEN_WIDTH*3/4, 128);

    return 0;
}