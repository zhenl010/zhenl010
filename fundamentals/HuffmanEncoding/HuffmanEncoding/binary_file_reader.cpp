#include "binary_file_reader.h"
#include <iostream>
#include <fstream>

BinaryFileReader::BinaryFileReader(const char* filename)
    :file_stream_(filename, std::ios::in|std::ios::binary) {
}

BinaryFileReader::~BinaryFileReader() {
    file_stream_.close();
}

// Readable until reaches end
bool BinaryFileReader::IsEnded() {
    return !file_stream_.good();
}

// Extracts a character and returns it
char BinaryFileReader::GetChar() {
    return file_stream_.get();
}