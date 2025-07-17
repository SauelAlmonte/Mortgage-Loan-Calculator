// Banner.cpp
#include "Banner.h"
#include <iostream>
#include <iomanip>

using namespace std;

/*
    Function: displayBanner

    Programmer's Note:
        - Outputs a welcome banner formatted with consistent spacing using iomanip.
        - Displays the program name prominently and welcomes the user.

    Simpler Terms:
        Shows a welcome message with the program name, formatted neatly.
 */
void displayBanner(const string& programName) {
    cout << setfill('=') << setw(45) << "=" << endl;
    cout << setfill(' ') << setw(30) << "Welcome to the " << endl;
    cout << setw(34) << programName << endl;
    cout << setfill('=') << setw(45) << "=" << endl;
    cout << setfill(' ');
}
