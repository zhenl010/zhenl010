#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <future>
#include <chrono>
#include <filesystem> // C++ TR2 

namespace {
//////////////////////////////////////////////////////////////////////////

typedef std::vector<std::string> StringVector;

using namespace std::tr2::sys; // for <filesystem>

StringVector listDirectory(std::string && dir)
{
    StringVector listing;
    std::string dir_str("\n> ");
    dir_str += dir;
    dir_str += ":\n ";
    listing.push_back(dir_str);

    std::vector<std::future<StringVector>> futures;
    for (auto it=directory_iterator(dir); it!=directory_iterator(); ++it)
    {
        if ( is_directory(it->path()) )
        {

        }
        else
        {
            listing.push_back(it->path().leaf());
        }
    }

    return listing;
}

//////////////////////////////////////////////////////////////////////////
}

int main()
{
    return 0;
}