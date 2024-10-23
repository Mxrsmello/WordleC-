#include <igloo/igloo.h>
#include <vector>
#include "helpers.h"

using namespace igloo;

Context(WordleKeyboard){
    Spec(TestKeyColor){
        int state = 0;
        Assert::That(getKeyColor(state) == "white");

        state = 1;
        Assert::That(getKeyColor(state) == "green");

        state = 2;
        Assert::That(getKeyColor(state) == "grey");

        state = 3;
        Assert::That(getKeyColor(state) == "yellow");

        state = 10;
        Assert::That(getKeyColor(state) == "unknown");
    }

    Spec(TestKeyState){
        int state = 0;
        Assert::That(getKeyState(state) == "not pressed");

        state = 1;
        Assert::That(getKeyState(state) == "pressed correct");

        state = 2;
        Assert::That(getKeyState(state) == "pressed not in word");

        state = 3;
        Assert::That(getKeyState(state) == "pressed in wrong spot");

        state = 5;
        Assert::That(getKeyState(state) == "unknown");
    }
};

int main(int argc, const char *argv[])
{
    return TestRunner::RunAllTests(argc, argv);
}