#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <cctype>
#include <iomanip>
#include "helpers.h"
#include "wordle.h"

using namespace std;

// Wordle Game in C++

// write to status.txt, takes string message to write
void writeStatus(string message)
{
    ofstream statusFile;
    statusFile.open("../keyboard/status.txt");
    statusFile << message;
    statusFile.close();
}

// takes 3 command line arguments: 4 4-words.txt 4-allowed.txt
int main(int argc, char *argv[])
{
    // seed the random number generator
    srand(time(NULL));

    string wordsFileName;
    string allowedWordsFileName;
    int wordLength;
    vector<string> words;
    vector<string> allowedWords;

    // check if the number of arguments is 4
    if (argc != 4)
    {
        cout << "Usage: " << argv[0] << " <word length> <words file> <allowed words file>" << endl;
        return 0;
    }

    // check if the word length is a number
    try
    {
        wordLength = stoi(argv[1]);
    }
    catch (const std::exception &e)
    {
        cout << "Error: The word length must be a number." << endl;
        return 0;
    }

    // check if the word length is between 3 and 10
    if (wordLength < 4 || wordLength > 8)
    {
        cout << "Error: The word length must be between 4 and 8." << endl;
        return 0;
    }

    // check if the words file exists
    wordsFileName = argv[2];
    ifstream wordsFile(wordsFileName);
    if (!wordsFile.good())
    {
        cout << "Error: The words file '" << wordsFileName << "' does not exist." << endl;
        return 0;
    }

    // check if the allowed words file exists
    allowedWordsFileName = argv[3];
    ifstream allowedWordsFile(allowedWordsFileName);
    if (!allowedWordsFile.good())
    {
        cout << "Error: The allowed words file '" << allowedWordsFileName << "' does not exist." << endl;
        return 0;
    }

    // read the words file and store the words in a vector
    string word;
    while (wordsFile >> word)
    {
        if (word.length() == wordLength)
        {
            words.push_back(word);
        }
    }

    // read the allowed words file and store the words in a vector
    while (allowedWordsFile >> word)
    {
        if (word.length() == wordLength)
        {
            allowedWords.push_back(word);
        }
    }

    Wordle wordle(wordLength, words, allowedWords);

    bool running = true;
    while (running)
    {
        writeStatus("main menu");
        clearTerminal();
        int option = showMenu();
        switch (option)
        {
        case 1:
        {
            wordle.startNewGame();

            // play wordle
            clearTerminal();

            // play the game
            bool playing = true;
            while (playing)
            {
                // check if the user has reached the maximum number of guesses
                if (wordle.isGameOver())
                {
                    cout << "You have reached the maximum number of guesses." << endl;
                    cout << "The correct word was" << endl;
                    cout << (getRow(wordle.getCorrectWord(), wordle.getCorrectWord())) << endl;
                    playing = false;
                    continue;
                }
                // through attemptedWordsUserWords and print the history
                clearTerminal();
                for (string word : wordle.getAttemptedWordsUserWords(wordle.getCorrectWord()))
                {
                    cout << (getRow(wordle.getCorrectWord(), word)) << endl;
                }

                // cout << "Correct: " << wordle.getCorrectWord() << endl;
                string userWord;
                cout << "Enter guess: ";
                cin >> userWord;

                // check if the user has entered a valid word
                if(wordle.isWordAllowed(userWord) == false)
                {
                    cout << "Error: The word is not allowed." << endl;
                    pressEnterToContinue();
                    continue;
                }

                // check length
                if (userWord.length() != wordLength)
                {
                    cout << "Error: The word must be " << wordLength << " characters long." << endl;
                    pressEnterToContinue();
                    continue;
                }

                wordle.checkWord(userWord);

                // compare case insensitive
                if (wordle.isWinGame())
                {
                    clearTerminal();
                    for (string word : wordle.getAttemptedWordsUserWords(wordle.getCorrectWord()))
                    {
                        cout << getRow(wordle.getCorrectWord(), word) << endl;
                    }

                    cout << "Splendid!" << endl;
                    playing = false;
                }
            }

            // press enter to return to the menu
            pressEnterToContinue();

            break;
        }
        case 2:
        {
            // how to play
            clearTerminal();
            showHowToPlay(wordLength);
            pressEnterToContinue();
            break;
        }
        case 3:
        {
            // statistics summary
            clearTerminal();
            cout << "=====================================" << endl;
            cout << "          STATISTICS SUMMARY" << endl;
            cout << "=====================================" << endl;
            cout << endl;
            cout << setw(20) << left << "Times Played: ";
            cout << setw(15) << right << wordle.getTimesPlayed() << endl;
            cout << setw(20) << left << "Average Attempts: ";
            cout << setw(15) << right << wordle.getAverageAttempts() << endl;
            cout << setw(20) << left << "Win Percentage: ";
            cout << setw(15) << right << wordle.getWinPercentage() << "%" << endl;
            cout << setw(20) << left << "Current Streak: ";
            cout << setw(15) << right << wordle.getCurrentStreak() << endl;
            cout << setw(20) << left << "Longest Streak: ";
            cout << setw(15) << right << wordle.getCurrentStreak() << endl;
            cout << endl;

            cout << "-------------------------------------" << endl;
            cout << "WORD                  ATTEMPTS    WIN" << endl;
            cout << "-------------------------------------" << endl;
            for (auto const &attempt : wordle.getAttemptedWordsAttempts())
            {
                cout << setw(20) << left << toUpper(attempt.first);
                cout << setw(10) << right << attempt.second;
                if (wordle.getAttemptedWordsResult()[attempt.first])
                {
                    cout << setw(5) << right << "Yes" << endl;
                }
                else
                {
                    cout << setw(7) << right << "No" << endl;
                }
            }

            pressEnterToContinue();
            break;
        }
        case 4:
        {
            // reset statistics
            clearTerminal();
            cout << "=====================================" << endl;
            cout << "          RESET STATISTICS" << endl;
            cout << "=====================================" << endl;
            cout << endl;
            cout << "Are you sure you want to reset the statistics? (y/n): ";
            char reset;
            cin >> reset;
            if (reset == 'y')
            {
                wordle.resetStatistics();
                cout << "Statistics reset." << endl;
            }

            pressEnterToContinue();
            break;
        }

        case 5:
        {
            // quit
            clearTerminal();
            cout << "=====================================" << endl;
            cout << "               GOODBYE" << endl;
            cout << "=====================================" << endl;
            cout << endl;
            cout << "Thanks for playing!" << endl;
            cout << endl;
            running = false;
            writeStatus("exit");
            wordle.saveStatistics();
            break;
        }
        default:
        {
            // invalid option
            clearTerminal();
            cout << "=====================================" << endl;
            cout << "              ERROR" << endl;
            cout << "=====================================" << endl;
            cout << endl;
            cout << "Invalid option. Please try again." << endl;

            pressEnterToContinue();
            break;
        }
        }
    }

    return 0;
}
