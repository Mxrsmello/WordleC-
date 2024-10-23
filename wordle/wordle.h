#ifndef WORDLE_H
#define WORDLE_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <cctype>
#include <iomanip>
#include "helpers.h"

using namespace std;

enum class GameState
{
    READY,
    PLAYING,
    WIN,
    LOSE
};

class Wordle
{
private:
    int wordLength;
    vector<string> words;
    vector<string> allowedWords;

    // statistics
    int timesPlayed;
    int currentStreak;
    int longestStreak;

    string userWord;
    string correctWord;

    // map of attempted words and their total attempts
    map<string, int> attemptedWordsAttempts;
    // map of attempted words and result: win/lose
    map<string, bool> attemptedWordsResult;
    // map of attempted words and their user words
    map<string, vector<string>> attemptedWordsUserWords;

    vector<int> keyboardState;

    // variables used in a single round
    int attempts = 0;

    // game state
    GameState gameState;

public:
    // constructor
    Wordle(int wordLength, vector<string> words, vector<string> allowedWords);

    // getters
    int getWordLength();
    vector<string> getWords();
    vector<string> getAllowedWords();
    int getTimesPlayed();
    int getCurrentStreak();
    int getLongestStreak();
    string getUserWord();
    string getCorrectWord();
    map<string, int> getAttemptedWordsAttempts();
    map<string, bool> getAttemptedWordsResult();
    map<string, vector<string>> getAttemptedWordsUserWords();
    vector<string> getAttemptedWordsUserWords(string word)
    {
        return this->attemptedWordsUserWords[word];
    }
    bool isWordAllowed(string word) {
        bool isAllowed = false;
        for (int i = 0; i < this->allowedWords.size(); i++) {
            if (this->allowedWords[i] == word) {
                isAllowed = true;
                break;
            }
        }

        return isAllowed;
    }
    vector<int> getKeyboardState();
    // reset statistics
    void resetStatistics();

    // start new game
    void startNewGame();

    // check if the user word is valid
    void checkWord(string userWord);

    // is game over?
    bool isGameOver();

    // is win?
    bool isWinGame();

    // get game state
    GameState getGameState();

    int getAverageAttempts();
    double getWinPercentage();
    void saveStatistics()
    {
        ofstream statsFile;
        statsFile.open(to_string(wordLength) + "-stats.txt");
        statsFile << this->getTimesPlayed() << endl;
        statsFile << this->getCurrentStreak() << endl;
        statsFile << this->getLongestStreak() << endl;

        int sizeOfAttemptedWords = this->attemptedWordsAttempts.size();
        statsFile << sizeOfAttemptedWords << endl;
        // loop and write to file
        for (auto const &pair : this->attemptedWordsAttempts)
        {
            statsFile << pair.first;
            statsFile << " " << pair.second;
            statsFile << " " << this->attemptedWordsResult[pair.first];
            int sizeOfUserWords = this->attemptedWordsUserWords[pair.first].size();
            statsFile << " " << sizeOfUserWords;
            for (int i = 0; i < sizeOfUserWords; i++)
            {
                statsFile << " " << this->attemptedWordsUserWords[pair.first][i];
            }
            statsFile << endl;
        }

        statsFile.close();
    }

    void loadStatsFromFile()
    {
        ifstream statsFile;
        statsFile.open(to_string(wordLength) + "-stats.txt");
        if (statsFile.is_open())
        {
            string line;
            getline(statsFile, line);
            this->timesPlayed = stoi(line);
            getline(statsFile, line);
            this->currentStreak = stoi(line);
            getline(statsFile, line);
            this->longestStreak = stoi(line);

            getline(statsFile, line);
            int sizeOfAttemptedWords = stoi(line);
            for (int i = 0; i < sizeOfAttemptedWords; i++)
            {
                getline(statsFile, line);
                stringstream ss(line);
                string word;
                int attempts;
                bool result;
                int sizeOfUserWords;
                ss >> word >> attempts >> result >> sizeOfUserWords;
                this->attemptedWordsAttempts[word] = attempts;
                this->attemptedWordsResult[word] = result;
                for (int j = 0; j < sizeOfUserWords; j++)
                {
                    string userWord;
                    ss >> userWord;
                    this->attemptedWordsUserWords[word].push_back(userWord);
                }
            }
        }
        statsFile.close();
    }

    void updateKeyboardState()
    {
        // update keyboard state
        for (int i = 0; i < this->userWord.length(); i++)
        {
            int charPos = this->userWord[i] - 'a';

            // check correct word and user word
            if (this->correctWord[i] == this->userWord[i])
            {
                // position of char in alphabet
                int charPos = this->userWord[i] - 'a';
                this->keyboardState[charPos] = 1;
            }
            else
            {
                // check if the letter is in the correct word
                bool inCorrectWord = false;
                for (int j = 0; j < this->correctWord.length(); j++)
                {
                    if (this->correctWord[j] == this->userWord[i])
                    {
                        inCorrectWord = true;
                        break;
                    }
                }

                int charPos = this->userWord[i] - 'a';
                if (inCorrectWord)
                {
                    this->keyboardState[charPos] = 3;
                }
                else
                {
                    this->keyboardState[charPos] = 2;
                }
            }
        }

        ofstream statusFile("../keyboard/status.txt");
        for (int i = 0; i < 26; i++)
        {
            statusFile << this->keyboardState[i] << endl;
        }
        statusFile.close();
    }
};

Wordle::Wordle(int wordLength, vector<string> words, vector<string> allowedWords)
{
    this->wordLength = wordLength;
    this->words = words;
    this->allowedWords = allowedWords;

    this->timesPlayed = 0;
    this->currentStreak = 0;
    this->longestStreak = 0;

    // initialize keyboard state
    for (int i = 0; i < 26; i++)
    {
        keyboardState.push_back(0);
    }

    this->gameState = GameState::READY;

    // load statistics from file
    this->loadStatsFromFile();
}

void Wordle::checkWord(string userWord)
{
    this->userWord = userWord;
    this->attempts++;
    this->attemptedWordsAttempts[correctWord]++;
    this->attemptedWordsUserWords[correctWord].push_back(userWord);

    // update keyboard state
    this->updateKeyboardState();

    if (toLower(this->correctWord) == toLower(this->userWord))
    {
        this->gameState = GameState::WIN;
        this->attemptedWordsResult[correctWord] = true;

        currentStreak++;
        if (currentStreak > longestStreak)
        {
            longestStreak = currentStreak;
        }
    }
    else
    {
        if (this->attempts == 6)
        {
            this->gameState = GameState::LOSE;
            this->attemptedWordsResult[correctWord] = false;
            currentStreak = 0;
        }
    }

    saveStatistics();
}

void Wordle::resetStatistics()
{
    this->timesPlayed = 0;
    this->currentStreak = 0;
    this->longestStreak = 0;
    this->attemptedWordsAttempts.clear();
    this->attemptedWordsResult.clear();
    this->attemptedWordsUserWords.clear();
}

void Wordle::startNewGame()
{
    this->timesPlayed++;
    this->correctWord = allowedWords[rand() % allowedWords.size()];
    this->userWord = "";
    this->attempts = 0;
    this->gameState = GameState::PLAYING;
    attemptedWordsAttempts[correctWord] = 0;

    // reset keyboard state
    for (int i = 0; i < 26; i++)
    {
        keyboardState[i] = 0;
    }
}

// is game over?
bool Wordle::isGameOver()
{
    return this->gameState == GameState::WIN || this->gameState == GameState::LOSE;
}

// is win
bool Wordle::isWinGame()
{
    return this->gameState == GameState::WIN;
}

int Wordle::getWordLength()
{
    return this->wordLength;
}

vector<string> Wordle::getWords()
{
    return this->words;
}

vector<string> Wordle::getAllowedWords()
{
    return this->allowedWords;
}

int Wordle::getTimesPlayed()
{
    return this->timesPlayed;
}

int Wordle::getCurrentStreak()
{
    return this->currentStreak;
}

int Wordle::getLongestStreak()
{
    return this->longestStreak;
}

string Wordle::getUserWord()
{
    return this->userWord;
}

string Wordle::getCorrectWord()
{
    return this->correctWord;
}

map<string, int> Wordle::getAttemptedWordsAttempts()
{
    return this->attemptedWordsAttempts;
}

map<string, bool> Wordle::getAttemptedWordsResult()
{
    return this->attemptedWordsResult;
}

map<string, vector<string>> Wordle::getAttemptedWordsUserWords()
{
    return this->attemptedWordsUserWords;
}

vector<int> Wordle::getKeyboardState()
{
    return this->keyboardState;
}

GameState Wordle::getGameState()
{
    return this->gameState;
}

int Wordle::getAverageAttempts()
{
    int totalAttempts = 0;
    for (auto const &attempt : this->getAttemptedWordsAttempts())
    {
        totalAttempts += attempt.second;
    }

    int timesPlayed = this->getTimesPlayed();
    if (timesPlayed == 0)
    {
        timesPlayed = 1;
    }
    int averageAttempts = totalAttempts / timesPlayed;
    return averageAttempts;
}

double Wordle::getWinPercentage()
{
    int totalWins = 0;
    for (auto const &result : this->getAttemptedWordsResult())
    {
        if (result.second)
        {
            totalWins++;
        }
    }

    int timesPlayed = this->getTimesPlayed();
    if (timesPlayed == 0)
    {
        timesPlayed = 1;
    }
    int winPercentage = (totalWins / timesPlayed) * 100;
    return winPercentage;
}

#endif // WORDLE_H