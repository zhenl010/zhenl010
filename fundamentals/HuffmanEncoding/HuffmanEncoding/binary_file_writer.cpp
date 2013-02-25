#include "binary_file_writer.h"
#include <iostream>
#include <fstream>

BinaryFileWriter::BinaryFileWriter(const char* filename)
    :file_stream_(filename, std::ios::out|std::ios::binary) {
}

BinaryFileWriter::~BinaryFileWriter() {
    file_stream_.close();
}

// Readable until reaches end
bool BinaryFileWriter::IsEnded() {
    return !file_stream_.good();
}

// Write single character to file
void BinaryFileWriter::PutChar(char c) {
    file_stream_.put(c);
}

// Write block of data
void BinaryFileWriter::Write(const char* str, unsigned int num) {
    file_stream_.write(str, num);
}