#include <iostream>
#include <string>
#include <sstream>

class Time
{
public:
    std::string whatTime(int seconds);

};

std::string Time::whatTime(int seconds)
{
    using namespace std;

    int hours = seconds/3600;
    int mins = (seconds%3600)/60;
    int secs = (seconds%3600)%60;

    stringstream strStream;
    strStream << hours << ":" << mins << ":" << secs;

    string timeStr = strStream.str();

    return timeStr;
}

int main()
{
    Time timeTest;
    timeTest.whatTime(3661);

    return 0;
}