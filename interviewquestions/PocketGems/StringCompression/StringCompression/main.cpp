#include <iostream>
#include <string>
#include <sstream>

namespace {

using namespace std;

string StringCompression(const string& str) {
    if (str.empty()) return string();

    char curr = str[0];
    int count = 1;
    stringstream strm;
    for (size_t i=1; i<str.size(); ++i) {
        if (curr != str[i]) {
            strm << count << curr;
            curr = str[i];
            count = 1;
        } else {
            ++count;
        }
    }
    strm << count << curr;

    return strm.str();
}

}

int main(int argc, char** argv) {
    return 0;
}