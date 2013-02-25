#ifndef BINARY_FILE_READER_H__
#define BINARY_FILE_READER_H__

#include <fstream>

class BinaryFileReader {
public:
    BinaryFileReader(const char* filename);
    ~BinaryFileReader();

    bool IsEnded(); // Readable until reaches end
    char GetChar(); // Extracts a character and returns it

private:
    std::ifstream file_stream_;
};

#endif