#include <iostream>

namespace // unnamed namespace
{
    static const int BUFFER_SIZE = 4096;
    static char buffer[BUFFER_SIZE];

    // for example: char* read4096()
    char* readfixed() // suppose given as api
    {
        // fake here:
        for (int i=0; i<BUFFER_SIZE; ++i)
        {
            buffer[i] = rand() % 256;
        }
        return &buffer[0];
    }
}

// void * memcpy ( void * destination, const void * source, size_t num );
// char str[]="Sample string"; char dest[40];
// memcpy (dest, str, strlen(str)+1);
// char * strcat ( char * destination, const char * source );
// strcat (str," and more ");
// void * memmove ( void * destination, const void * source, size_t num );
// char str[] = "memmove can be very useful......";
// memmove (str+20,str+15,11);

char* readline() // use given api
{
    char* cstr = readfixed();

    int leng = strlen(cstr);

    return nullptr;
}

int main(int argc, char** argv)
{
    char* str = readline();

    return 0;
}