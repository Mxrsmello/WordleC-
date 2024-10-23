#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <cctype>
#include <iomanip>

using namespace std;

string getTextInColor(string text, string color)
{
    stringstream ss;
    if (color == "green")
    {
        ss << "\033[32m" << text << "\033[0m";
    }
    else if (color == "yellow")
    {
        ss << "\033[33m" << text << "\033[0m";
    }
    else if (color == "white")
    {
        ss << "\033[37m" << text << "\033[0m";
    }
    else if (color == "grey")
    {
        ss << "\033[90m" << text << "\033[0m";
    }
    return ss.str();
}

// function to clear the screen
void clearTerminal()
{
    cout << "\033[2J\033[1;1H";
}

string toLower(string str)
{
    string lowerStr = "";
    for (int i = 0; i < str.length(); i++)
    {
        lowerStr += tolower(str[i]);
    }
    return lowerStr;
}

string toUpper(string str)
{
    string upperStr = "";
    for (int i = 0; i < str.length(); i++)
    {
        upperStr += toupper(str[i]);
    }
    return upperStr;
}

string getKeyState(int st)
{
    if (st == 0)
    {
        return "not pressed";
    }
    else if (st == 1)
    {
        return "pressed correct";
    }
    else if (st == 2)
    {
        return "pressed not in word";
    }
    else if (st == 3)
    {
        return "pressed in wrong spot";
    }

    return "unknown";
}

string getKeyColor(int st)
{
    if (st == 0)
    {
        return "white";
    }
    else if (st == 1)
    {
        return "green";
    }
    else if (st == 2)
    {
        return "grey";
    }
    else if (st == 3)
    {
        return "yellow";
    }

    return "unknown";
}

void printCell(int state, char letter, stringstream &ss)
{
    if (state == 0)
    {
        ss << getTextInColor("| " + string(1, letter) + " |", getKeyColor(state));
    }
    else if (state == 1)
    {
        ss << getTextInColor("| " + string(1, letter) + " |", getKeyColor(state));
    }
    else if (state == 2)
    {
        ss << getTextInColor("| " + string(1, letter) + " |", getKeyColor(state));
    }
    else if (state == 3)
    {
        ss << getTextInColor("| " + string(1, letter) + " |", getKeyColor(state));
    }
}

void printLines(int state, stringstream &ss)
{
    string kstate = getKeyState(state);
    if (kstate == "not pressed")
    {
        ss << getTextInColor(" --- ", getKeyColor(state));
    }
    else if (kstate == "pressed correct")
    {
        ss << getTextInColor(" --- ", getKeyColor(state));
    }
    else if (kstate == "pressed not in word")
    {
        ss << getTextInColor(" --- ", getKeyColor(state));
    }
    else if (kstate == "pressed in wrong spot")
    {
        ss << getTextInColor(" --- ", getKeyColor(state));
    }
}

char getLetterFromIndex(int idx)
{
    return 'A' + idx;
}

map<char, int> getLetterToState(vector<string> lines) {
    map<char, int> letterToState;
    for (int i = 0; i < 26; i++) {
        int state = stoi(lines[i]);
        char letter = getLetterFromIndex(i);
        letterToState[letter] = state;
    }
    return letterToState;
}

vector<char> getQwertyKeys()
{
    vector<char> keys = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
                         'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
                         'Z', 'X', 'C', 'V', 'B', 'N', 'M'};
    return keys;
}

string getKeyboard(vector<string> lines) 
{
    stringstream ss;
    vector<char> keys = getQwertyKeys();
    map<char, int> letterStates = getLetterToState(lines);

    // for the first 10
    for (int i = 0; i < 10; i++)
    {
        int state = letterStates[keys[i]];
        printLines(state, ss);
    }
    ss << endl;
    for (int i = 0; i < 10; i++)
    {
        int state = letterStates[keys[i]];
        char letter = keys[i];
        printCell(state, letter, ss);
    }
    ss << endl;
    for (int i = 0; i < 10; i++)
    {
        int state = letterStates[keys[i]];
        printLines(state, ss);
    }
    ss << endl;

    ss << "   ";
    // for the next 9
    for (int i = 10; i < 19; i++)
    {
        int state = letterStates[keys[i]];
        printLines(state, ss);
    }
    ss << endl;
    ss << "   ";
    for (int i = 10; i < 19; i++)
    {
        int state = letterStates[keys[i]];
        char letter = keys[i];
        printCell(state, letter, ss);
    }
    ss << endl;
    ss << "   ";
    for (int i = 10; i < 19; i++)
    {
        int state = letterStates[keys[i]];
        printLines(state, ss);
    }
    ss << endl;

    // for the next 7
    ss << "      ";
    for (int i = 19; i < 26; i++)
    {
        int state = letterStates[keys[i]];
        printLines(state, ss);
    }
    ss << endl;
    ss << "      ";
    for (int i = 19; i < 26; i++)
    {
        int state = letterStates[keys[i]];
        char letter = keys[i];
        printCell(state, letter, ss);
    }
    ss << endl;
    ss << "      ";
    for (int i = 19; i < 26; i++)
    {
        int state = letterStates[keys[i]];
        printLines(state, ss);
    }
    ss << endl;

    return ss.str();
}

// write to status.txt, takes string message to write
void writeStatus(string message)
{
    ofstream statusFile;
    statusFile.open("status.txt");
    statusFile << message;
    statusFile.close();
}

#endif // HELPERS_H