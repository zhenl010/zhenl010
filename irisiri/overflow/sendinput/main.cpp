#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;

//* HWND = "Window Handle" */
HWND GameWindow = FindWindow(0, "WinWord");

/* This is a function to simplify usage of sending keys */
void GenerateKey(int vk, BOOL bExtended) {

    KEYBDINPUT  kb = {0};

    INPUT       Input = {0};


    /* Generate a "key down" */

    if (bExtended) { kb.dwFlags  = KEYEVENTF_EXTENDEDKEY; }

    kb.wVk  = vk;

    Input.type  = INPUT_KEYBOARD;

    Input.ki  = kb;

    SendInput(1, &Input, sizeof(Input));


    /* Generate a "key up" */

    ZeroMemory(&kb, sizeof(KEYBDINPUT));

    ZeroMemory(&Input, sizeof(INPUT));

    kb.dwFlags  =  KEYEVENTF_KEYUP;

    if (bExtended) { kb.dwFlags |= KEYEVENTF_EXTENDEDKEY; }

    kb.wVk = vk;

    Input.type = INPUT_KEYBOARD;

    Input.ki = kb;

    SendInput(1, &Input, sizeof(Input));


    return;

}


int main() {


    /*

       SetForegroundWindow will give the window focus for the

       keyboard/mouse! In other words, you don't have to have

       the game opened upfront in order to emulate key/mouse

       presses, it's very helpful if it's a game that runs

       in fullscreen mode, like StarCraft: Brood War does

    */


    SetForegroundWindow(GameWindow);

    while (1)
    {
        GenerateKey('4', FALSE);
        GenerateKey('3', FALSE);
        GenerateKey('2', FALSE);
        Sleep(16000);
    }

    while (0)
    {
        GenerateKey(VK_CAPITAL, TRUE);
        GenerateKey(VK_CAPITAL, TRUE);

        GenerateKey('A', FALSE);
        GenerateKey('M', FALSE);
        GenerateKey(' ', FALSE);
        GenerateKey('C', FALSE);
        GenerateKey(0x3A, FALSE); /* period key */
        GenerateKey(0x0D, FALSE); /* enter key */
    }

    return 0;

}