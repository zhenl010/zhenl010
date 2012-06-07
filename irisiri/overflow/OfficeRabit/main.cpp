#include <iostream>
#include <windows.h>
#include <ctime>
#include <vector>
#include "keyinput.h"

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace augment_window_functions;

//* HWND = "Window Handle" */
HWND GameWindow = FindWindow(0, "WinWord");

struct TimedKey {
    SimpleKey key_;
    time_t lasttime_;
    double timer_; // in seconds
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
    SetForegroundWindow(GameWindow);
    
    const int sleeptime = 500; // milliseconds
    time_t lasttime = time(NULL);
    TimedKey tkeys[] = {
        {{'2', false}, lasttime, 15.0},
        {{'3', false}, lasttime, 300.0},
        {{'4', false}, lasttime, 120.0}
    };
    int keynum = sizeof(tkeys) / sizeof(TimedKey);

    while (true) {
        for (int i=0; i<keynum; ++i) {
            time_t currtime = time(NULL);
            double timediff = difftime(currtime, tkeys[i].lasttime_);
            if (timediff > tkeys[i].timer_) {
                GenerateSimpleKey(tkeys[i].key_);
                tkeys[i].lasttime_ = currtime;
            }
        }

        // hiberate in between
        Sleep(sleeptime);
    }

    return 0;
}