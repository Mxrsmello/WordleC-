#include <iostream>
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <cctype>
#include <iomanip>
#include <unistd.h>
#include "helpers.h"

using namespace std;

// Wordle keyboard

int main()
{
    bool gameStarted = false;
    // Read input form status.txt
    while (true)
    {
        string line;
        vector<string> lines;

        // open the file
        ifstream file("status.txt");
        // if cannot open then continue
        if (!file.is_open())
        {
            continue;
        }

        while (getline(file, line))
        {
            lines.push_back(line);
        }

        // if no lines then continue
        if (lines.size() == 0)
        {
            continue;
        }

        // close the file
        file.close();

        // if first line is "exit" then exit
        if (lines[0] == "exit")
        {
            break;
        }

        // if not started then wait
        if (string(lines[0]) == "main menu")
        {
            clearTerminal();
            cout << "Waiting for Wordle Game round to start" << endl;
            sleep(1);
            continue;
        }

        if (string(lines[0]) == "waiting")
        {
            // sleep for 0.5 second
            sleep(1);
            continue;
        }

        gameStarted = true;

        // keyboard
        string keyboard = getKeyboard(lines);

        // clear the terminal
        clearTerminal();

        // print the keyboard
        cout << keyboard << endl;

        // sleep for 0.5 second
        sleep(1);
        writeStatus("waiting");
    }
}
