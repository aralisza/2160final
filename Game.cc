#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "TestLevel.cc"

using namespace std;

class Game {
public:
    int curLev;
    vector<Level*> levels;
    bool winner;

    Game() {
        curLev = 0;

        TestLevel *l1 = new TestLevel;
        RSE *l2 = new RSE;
        TestLevel *l3 = new TestLevel;

        levels.push_back(l1);
        levels.push_back(l2);
        levels.push_back(l3);
    }

    void print() {
        printf("Current Level: %d\n", curLev + 1);
        levels[curLev]->printBoard();
    }

    // handle key inputs
    void onKey(char key) {
        // move player
        if (key == 'w' ||
            key == 'a' ||
            key == 's' ||
            key == 'd') {
            levels[curLev]->movePlayer(key);
        }
        // reset level, also resets win to 0
        else if (key == 'r') {
            levels[curLev]->reset();
        }
        // previous level
        else if (key == '[') {
            curLev = max(curLev - 1, 0);
        }
        // next level
        else if (key == ']') {
            curLev = min(curLev + 1, (int)levels.size() - 1);
        }
    }

    bool winAll() {
        bool r = true;
        for (Level* l : levels) {
            r = r && l->win;
        }

        return r;
    }
};

int main() {
    Game g;
    char input;
    bool control = true;

    printf("======================================================\n\n        ######\n        #     #   ####    ####   #    #   ####\n        #     #  #    #  #    #  #   #   #\n        ######   #    #  #       ####     ####\n        #   #    #    #  #       #  #         #\n        #    #   #    #  #    #  #   #   #    #\n        #     #   ####    ####   #    #   ####\n\n======================================================\n\n~~~~~~~~~~~~~~~~~~~  How to Play  ~~~~~~~~~~~~~~~~~~~~\n\nYou are represented with the letter 'p'\n\nPush the rocks so that you clear a path to the exit.\nRocks are represented with the letter 'O'\n\nYou can only move rocks if there is a free space to\npush them to.\n\nExits are marked with the letter 'e'\n\nWalls are represented with the letter 'X'.\nWalls are immovable.\n\nYou beat the level when you move your player to the\nexit.\n\nControls:\nw - up\na - left\ns - down\nd - right\nr - reset\n[ - previous level\n] - next level\n\nHave fun!\n\n");

    while (control) {
        g.print();

        cin >> input;
        g.onKey(input);

        if (g.winAll()) {
            g.print();
            printf("You Win!\n");
            control = false;
        }
    }
}
