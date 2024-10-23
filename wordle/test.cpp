#include <igloo/igloo.h>
#include <vector>
#include "wordle.h"

using namespace igloo;

vector<string> allowedWords = {"bend", "bell", "bird", "come", "calm"};
vector<string> words = {"test"};

Context(WordleGame){
    Spec(CorrectInitialization){
        Wordle wordle(4, words, allowedWords);

        // ready game state
        Assert::That(wordle.getGameState() == GameState::READY);

        // reset transactions
        wordle.startNewGame();
        wordle.resetStatistics();

        // length set correctly
        Assert::That(wordle.getWordLength(), Equals(4));

        // playing game state
        Assert::That(wordle.getGameState() == GameState::PLAYING);

        Assert::That(wordle.getCurrentStreak() == 0);
        Assert::That(wordle.getLongestStreak() == 0);
        Assert::That(wordle.getTimesPlayed() == 0);
    }

    Spec(CorrectCheckingOfUserWord){
        Wordle wordle(4, words, allowedWords);

        wordle.startNewGame();
        wordle.resetStatistics();

        // playing game state
        Assert::That(wordle.getGameState() == GameState::PLAYING);

        wordle.checkWord("info");

        Assert::That(wordle.getUserWord() == "info");
        Assert::That(wordle.isWinGame() == false);
        Assert::That(wordle.isGameOver() == false);

        wordle.checkWord(wordle.getCorrectWord());

        // won game state
        Assert::That(wordle.getGameState() == GameState::WIN);

        Assert::That(wordle.isWinGame() == true);
        Assert::That(wordle.isGameOver() == true);
    }

    Spec(CorrectStats){
        Wordle wordle(4, words, allowedWords);

        wordle.startNewGame();
        wordle.resetStatistics();

        Assert::That(wordle.getAverageAttempts() == 0);
        Assert::That(wordle.getWinPercentage() == 0);

        wordle.checkWord(wordle.getCorrectWord());

        Assert::That(wordle.getAverageAttempts() == 1);
        Assert::That(wordle.getWinPercentage() == 100);
    }

    Spec(LimitNumberOfGuesses){
        Wordle wordle(4, words, allowedWords);

        wordle.startNewGame();
        wordle.resetStatistics();

        wordle.checkWord("info");
        wordle.checkWord("info");
        wordle.checkWord("info");
        wordle.checkWord("info");
        wordle.checkWord("info");
        wordle.checkWord("info");

        // lost game state
        Assert::That(wordle.getGameState() == GameState::LOSE);

        Assert::That(wordle.isWinGame() == false);
        Assert::That(wordle.isGameOver() == true);
    }


};

int main(int argc, const char *argv[])
{
    return TestRunner::RunAllTests(argc, argv);
}