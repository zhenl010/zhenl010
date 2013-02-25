#include <iostream>
#include <fstream>
#include <string>
#include "binary_file_reader.h"
#include "binary_file_writer.h"

int main(int argc, char** argv) {
    using namespace std;

    string str;
    BinaryFileReader file_reader(argv[1]);
    while (!file_reader.IsEnded()) {
        char c = file_reader.GetChar();
        cout << c;
        str += c;
    }

    BinaryFileWriter file_writer(argv[2]);
    file_writer.Write("Hello world!", 12);

    return 0;
}