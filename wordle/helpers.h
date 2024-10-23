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

// Function to getTextIn the string in green color
string getTextInGreen(string text)
{
    stringstream ss;
    ss << "\033[32m" << text << "\033[0m";
    return ss.str();
}

// Function to getTextIn the string in yellow color
string getTextInYellow(string text)
{
    stringstream ss;
    ss << "\033[33m" << text << "\033[0m";
    return ss.str();
}

// Function to getTextIn the string in white color
string getTextInWhite(string text)
{
    stringstream ss;
    ss << "\033[37m" << text << "\033[0m";
    return ss.str();
}

// function to getTextIn the string in grey color
string getTextInGrey(string text)
{
    stringstream ss;
    ss << "\033[90m" << text << "\033[0m";
    return ss.str();
}

// function to clear the screen
void clearTerminal()
{
    cout << "\033[2J\033[1;1H";
}

string getRow(string correctWord, string userWord)
{
    stringstream ss;
    for (int i = 0; i < correctWord.length(); i++)
    {
        if (correctWord[i] == userWord[i])
        {
            ss << getTextInGreen(" --- ");
        }
        else if (correctWord.find(userWord[i]) != string::npos)
        {
            ss << getTextInYellow(" --- ");
        }
        else
        {
            ss << getTextInGrey(" --- ");
        }
    }
    ss << endl;

    for (int i = 0; i < correctWord.length(); i++)
    {
        if (correctWord[i] == userWord[i])
        {
            ss << getTextInGreen("| " + toUpper(string(1, userWord[i])) + " |");
        }
        else if (correctWord.find(userWord[i]) != string::npos)
        {
            ss << getTextInYellow("| " + toUpper(string(1, userWord[i])) + " |");
        }
        else
        {
            ss << getTextInGrey("| " + toUpper(string(1, userWord[i])) + " |");
        }
    }
    ss << endl;

    for (int i = 0; i < correctWord.length(); i++)
    {
        if (correctWord[i] == userWord[i])
        {
            ss << getTextInGreen(" --- ");
        }
        else if (correctWord.find(userWord[i]) != string::npos)
        {
            ss << getTextInYellow(" --- ");
        }
        else
        {
            ss << getTextInGrey(" --- ");
        }
    }
    return ss.str();
}

int showMenu()
{
    cout << "=========================" << endl;
    cout << "    WELCOME TO WORDLE    " << endl;
    cout << "=========================" << endl;
    cout << endl;
    cout << "1. Play Wordle" << endl;
    cout << "2. How to Play" << endl;
    cout << "3. Statistics Summary" << endl;
    cout << "4. Reset Statistics" << endl;
    cout << "5. Exit" << endl;
    cout << endl;
    cout << "Select option: ";
    int option;
    cin >> option;
    return option;
}

void showHowToPlay(int wordLength)
{
    cout << "=====================================" << endl;
    cout << "              HOW TO PLAY" << endl;
    cout << "=====================================" << endl;
    cout << "Guess the Wordle in 6 tries." << endl;
    cout << endl;
    cout << "HOW TO PLAY:" << endl;
    cout << "- Each guess must be a valid " << wordLength << " letter word." << endl;
    cout << "- The color of the tiles will change to show" << endl;
    cout << "  you how close your guess was to the word." << endl;
    cout << getRow("WDDDD", "WEARY") << endl;
    cout << "w is in the word and in correct position" << endl;
    cout << getRow("IKKKK", "PILLS") << endl;
    cout << "i is in the word but in the wrong spot" << endl;
    cout << getRow("AGUEL", "VAGUE") << endl;
    cout << "v is not in the word at any spot" << endl;
}


void pressEnterToContinue()
{
    cout << endl;
    cout << "Press [Enter] to continue...";
    cin.ignore();
    cin.get();
}

#endif // HELPERS_H