#ifndef BINARY_FILE_WRITTER_H__
#define BINARY_FILE_WRITTER_H__

#include <fstream>

class BinaryFileWriter {
public:
    BinaryFileWriter(const char* filename);
    ~BinaryFileWriter();

    bool IsEnded(); // Readable until reaches end
    void PutChar(char); // Write single character to file
    void Write(const char*, unsigned int); // Write block of data

private:
    std::ofstream file_stream_;
};

#endif