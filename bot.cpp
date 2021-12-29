/*
Increase Lumber production. Editted and added functions to bot.cpp too increase the number of lumber the dwarves collect.
*/

#include <cstdlib>
#include <cmath>
#include <iostream>
#include "bot.h"

using namespace std;

bool isTree(Dwarf & dwarf, int r, int c);
bool isNextToATree(Dwarf & dwarf, int r, int c);
void moveToClosestTree(Dwarf & dwarf, int r, int c, ostream &log);

const int MAX_ROWS = 40;
const int MAX_COLS = 40;
const int MAX_NUM = 10;

int ROWS; // global variables
int COLS;
int NUM;

void onStart(int rows, int cols, int num, std::ostream &log) {
    log << "Start!" << endl; // Print a greeting message
    ROWS = rows; // Save values in global variables
    COLS = cols;
    NUM = num;
}
void onAction(Dwarf & dwarf, int day, int hours, int minutes, ostream &log) {
    // Get current position of the dwarf
    int r = dwarf.row();
    int c = dwarf.col();
    if (dwarf.look(r, c+1) == PINE_TREE) { // Right
        // If there is a pine tree, chop it
        log << "Found a tree -- chop East" << endl;
        dwarf.start_chop(EAST);
        return;
    } 
    else if (dwarf.look(r, c-1) == PINE_TREE) { // Left
        // If there is a pine tree, chop it
        log << "Found a tree -- chop West" << endl;
        dwarf.start_chop(WEST);
        return;
    }
    else if (dwarf.look(r+1, c) == PINE_TREE) { // Down
        // If there is a pine tree, chop it
        log << "Found a tree -- chop South" << endl;
        dwarf.start_chop(SOUTH);
        return;
    }
    else if (dwarf.look(r-1, c) == PINE_TREE) { // Up
        // If there is a pine tree, chop it
        log << "Found a tree -- chop North" << endl;
        dwarf.start_chop(NORTH);
        return;
    }
    else {
        // Otherwise, move to the closest tree
        moveToClosestTree(dwarf, r, c, log);
        return;
    }
}

bool isTree(Dwarf & dwarf, int r, int c) {
    return (dwarf.look(r, c) == PINE_TREE ||
    dwarf.look(r, c) == APPLE_TREE);
}

bool isNextToATree(Dwarf & dwarf, int r, int c) {
    return (dwarf.look(r, c+1) == PINE_TREE ||
    dwarf.look(r, c-1) == PINE_TREE ||
    dwarf.look(r+1, c) == PINE_TREE ||
    dwarf.look(r-1, c) == PINE_TREE);
}

void moveToClosestTree(Dwarf & dwarf, int r, int c, ostream &log) {
    // Implement radial search
    int rows = ROWS;
    if (rows > 0) {
        int cols = COLS;
        for (int row = max(0, r-MAX_ROWS); row <= min(r+MAX_ROWS, rows-2); row++) {
              for (int col = max(0, c-MAX_COLS); col <= min(c+MAX_COLS, cols-2); col++) {
                if (isNextToATree(dwarf, row, col) && !isTree(dwarf, row, col)) {
                    log << "Walk to " << row << " " << col << endl;
                    dwarf.start_walk(row, col);
                    return;
                }
            }
        }
    }
}
