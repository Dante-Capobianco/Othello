#ifndef SKELETON_H
#define SKELETON_H

#include <stdbool.h>

void printBoard(char board[][26], int n);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, int row, 
                           int col, char colour, int deltaRow, int deltaCol);

int makeMove(const char board[][26], int n, char turn, int *row, int *col);

#endif
