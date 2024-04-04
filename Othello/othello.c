
#include "othello.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void printBoard(char board[][26], int n);

char letter(int num, int n);

void winner(char board[][26], int n);

bool noMove(char board[][26], int n, char colour);

bool positionInBounds(int n, int row, int col);

int makeMove(const char board[][26], int n, char turn, int* row, int* col);

void copied(char copy[8][26], const char board[][26]);

char* changeDirection(char boarddd[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);

void updateBoard(char board[][26], int n, int row, int col, char colour);

int probability(char board[][26], int n, char turn);

int currentScore(char board[][26], int n, char turn);

void availMoves(const char board[][26], int rowMove[60], int colMove[60], int* totalMoves, char turn);

bool valid(const char board[][26], int n, int row, int col, char colour);

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);

int max(int x, int y);

int min(int x, int y);

int minimaxSumMAX(char board[8][26], char origTurn, char current, int ply, int alpha, int beta);

int minimaxSumMIN(char board[8][26], char origTurn, char current, int ply, int alpha, int beta);

int weights(int i);

int heuristic(char board[][26], int n, char turn);

int cornerWeight(char board[][26], int n, char turn);

int main(void) {
  int n;
  int counter = 2;
  char compColour, opponent;
  bool validd = true;
  int row, col;
  int available;
  char rowChar;
  char colChar;
  printf("Enter the board dimension (choose 8): ");
  scanf("%d", &n);
  char board[n][26];
  for (int roww = 0; roww < n; roww++) {
    for (int coll = 0; coll < n; coll++) {
      if (roww == coll && (roww == n/2 - 1 || roww == n/2)) {
        board[roww][coll] = 'W';
      } else if ((roww == coll - 1 && roww == n/2 - 1) || (roww == coll + 1 && roww == n/2)) {
        board[roww][coll] = 'B';
      } else {
        board[roww][coll] = 'U';
      }
    }
  }

  printf("Computer plays (B/W): ");
  scanf(" %c", &compColour);
  if (compColour == 'B') {
    opponent = 'W';
  } else {
    opponent = 'B';
  }
  printBoard(board, n);

  while ((!noMove(board, n, 'W') || !noMove(board, n, 'B')) && validd) {
    if (counter % 2 == 0 && noMove(board, n, 'B')) {
      printf("B player has no valid move.\n");
    } else if (counter % 2 != 0 && noMove(board, n, 'W')) {
      printf("W player has no valid move.\n");
    } else if (counter % 2 == 0 && compColour == 'B') {
      makeMove(board, n, 'B', &row, &col);
      board[row][col] = 'B';
      printf("Computer places B at %c%c.\n", row + 'a', col + 'a');
      updateBoard(board, n, row, col, 'B');
      printBoard(board, n);
    } else if (counter % 2 == 0) {
      printf("Enter move (RowCol): ");
      scanf(" %c %c", &rowChar, &colChar);
      row = rowChar - 'a';
      col = colChar - 'a';
      if (valid(board, n, row, col, 'B')) {
        updateBoard(board, n, row, col, 'B');
        printBoard(board, n);
      } else {
        printf("Invalid move!\n");
        validd = false;
      }
    } else if (counter % 2 != 0 && compColour == 'W') {
      makeMove(board, n, 'W', &row, &col);
      board[row][col] = 'W';
      printf("Computer places W at %c%c.\n", row + 'a', col + 'a');
      updateBoard(board, n, row, col, 'W');
      printBoard(board, n);
    } else {
      printf("Enter move (RowCol): ");
      scanf(" %c %c", &rowChar, &colChar);
      row = rowChar - 'a';
      col = colChar - 'a';
      if (valid(board, n, row, col, 'W')) {
        updateBoard(board, n, row, col, 'W');
        printBoard(board, n);
      } else {
        printf("Invalid move!\n");
        validd = false;
      }
    }

    counter++;
  }

  if (validd) {
    winner(board, n);
  } else {
    printf("%c player wins.\n", compColour);
  }
  return 0;
}

void printBoard(char board[][26], int n) {
  char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  printf("  ");
  for (int i = 0; i < n; i++) {
    printf("%.1s", alphabet + i);
  }
  printf("\n");
  for (int row = 0; row < n; row++) {
    printf("%.1s ", alphabet + row);
    for (int col = 0; col < n; col++) {
      printf("%c", board[row][col]);
    }
    printf("\n");
  }
}

char letter(int num, int n) {
  char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  for (int i = 0; i < n; i++) {
    if (num == i) {
      return alphabet[i];
    }
  } 
}

void winner(char board[][26], int n) {
  int white = 0;
  int black = 0;

  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) { 
      if (board[row][col] == 'W') {
        white++;
      } else if (board[row][col] == 'B') {
        black++;
      }
    }
  }

  if (white > black) {
    printf("W player wins.\n");
  } else if (black > white) {
    printf("B player wins.\n");
  } else {
    printf("Draw!\n");
  }

  printf("W = %d AND B = %d\n", white, black);
}

int max(int x, int y) {
  if (x >= y) {
    return x;
  } else {
    return y;
  }
}

int min(int x, int y) {
  if (x <= y) {
    return x;
  } else {
    return y;
  }
}

int heuristic(char board[][26], int n, char turn) {
  return (2 * cornerWeight(board, n, turn) + 3 * probability(board, n, turn));
}

int cornerWeight(char board[][26], int n, char turn) {
  char opp = 'B';
  if (turn == 'B') {
    opp = 'W';
  }
  int total = 0, i = 0;
  while (i < 64) {
    if (board[i/8][i%8] == turn) {
      total += weights(i);
    } else if (board[i/8][i%8] == opp) {
      total -= weights(i);
    }
    i++;
  }
  return total;
}

int weights(int i) {
  int weights[64] = {20, -3, 2, 2, 2, 2, -3, 20, 
  -3, -4, -1, -1, -1, -1, -4, -3, 
  2, -1, 1, 0, 0, 1, -1, 2,
  2, -1, 0, 1, 1, 0, -1, 2,
  2, -1, 0, 1, 1, 0, -1, 2,
  2, -1, 1, 0, 0, 1, -1, 2,
  -3, -4, -1, -1, -1, -1, -4, -3,
  20, -3, 2, 2, 2, 2, -3, 20};
  return weights[i];
}

int currentScore(char board[][26], int n, char turn) {
  int sum = 0;
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (board[row][col] = turn) {
        sum++;
      }
    }
  }
  return sum;
}

int probability(char board[][26], int n, char turn) {
  char opp = 'B';
  if (turn == 'B') {
    opp = 'W';
  }
  int turnScore = currentScore(board, n, turn);
  int oppScore = currentScore(board, n, opp);
  return (turnScore - oppScore);
}

bool noMove(char board[][26], int n, char colour) {
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) { 
      if (valid(board, n, row, col, colour)) {
        return false;
      }
    }
  }
  return true;
}

bool positionInBounds(int n, int row, int col) {
  if (row < n && row >= 0 && col < n && col >= 0) {
    return true;
  } else {
    return false;
  }
}

int makeMove(const char board[][26], int n, char turn, int* row, int* col) {
  int rowMove[60];
  int colMove[60];
  int totalMoves = 0;
  char opp= 'B';
  if (turn == 'B') {
    opp = 'W';
  }

  availMoves(board, rowMove, colMove, &totalMoves, turn);

  int bestSum = -1000000000;
  *row = rowMove[0];
  *col = colMove[0];

  for (int i = 0; i < totalMoves; i++) {
    char copy[8][26];
    copied(copy, board);
    updateBoard(copy, 8, rowMove[i], colMove[i], turn);
    int sum = minimaxSumMIN(copy, turn, opp, 1, -1000000000, 1000000000);
    if (sum > bestSum) {
      bestSum = sum;
      *row = rowMove[i];
      *col = colMove[i];
    }
  }
  return 0;
}

int minimaxSumMAX(char board[8][26], char origTurn, char current, int ply, int alpha, int beta) {
  if (ply == 5 || (noMove(board, 8, 'W') && noMove(board, 8, 'B'))) {
    return heuristic(board, 8, current);
  }
  int bestSum = -1000000000;
  int rowMove[60];
  int colMove[60];
  int totalMoves = 0;
  char opp = 'B';
  if (current == 'B') {
    opp = 'W';
  }

  availMoves(board, rowMove, colMove, &totalMoves, current);

  for (int i = 0; i < totalMoves; i++) {
    char copy[8][26];
    copied(copy, board);
    updateBoard(copy, 8, rowMove[i], colMove[i], current);
    int sum = minimaxSumMIN(copy, origTurn, opp, ply + 1, alpha, beta);
    if (sum > bestSum) {
      bestSum = sum;
    }
    if (bestSum >= beta) {
      return bestSum;
    }
    alpha = max(alpha, bestSum);
  }
  return bestSum;
}

int minimaxSumMIN(char board[8][26], char origTurn, char current, int ply, int alpha, int beta) {
  if (ply == 5 || (noMove(board, 8, 'W') && noMove(board, 8, 'B'))) {
    return heuristic(board, 8, current);
  }
  int bestSum = 1000000000;
  int rowMove[60];
  int colMove[60];
  int totalMoves = 0;

  availMoves(board, rowMove, colMove, &totalMoves, current);

  for (int i = 0; i < totalMoves; i++) {
    char copy[8][26];
    copied(copy, board);
    updateBoard(copy, 8, rowMove[i], colMove[i], current);
    int sum = minimaxSumMAX(copy, origTurn, origTurn, ply + 1, alpha, beta);
    if (sum < bestSum) {
      bestSum = sum;
    }
    if (bestSum <= alpha) {
      return bestSum;
    }
    beta = min(beta, bestSum);
  }
  return bestSum;
}

void availMoves(const char board[][26], int rowMove[60], int colMove[60], int* totalMoves, char turn) {
  int i = 0;
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) { 
      if (valid(board, 8, row, col, turn)) {
        rowMove[i] = row;
        colMove[i] = col;
        i++;
        (*totalMoves)++;
      }
    }
  }
}

bool valid(const char board[][26], int n, int row, int col, char colour) {
  if (board[row][col] == 'U') {
    for (int i = -1; i < 2; i++) {
      if (checkLegalInDirection(board, n, row, col, colour, -1, i)) {
        return true;
      }
    }

    for (int i = -1; i < 2; i++) {
      if (checkLegalInDirection(board, n, row, col, colour, 1, i)) {
        return true;
      }
    }

    if (checkLegalInDirection(board, n, row, col, colour, 0, 1)) {
      return true;
    }

    if (checkLegalInDirection(board, n, row, col, colour, 0, -1)) {
      return true;
    }
  } else {
    return false;
  }
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
  char oppColour;
  if (colour == 'W') {
    oppColour = 'B';
  } else {
    oppColour = 'W';
  }

  row += deltaRow;
  col += deltaCol;

  if (board[row][col] != oppColour) {
    return false;
  }

  row += deltaRow;
  col += deltaCol;

  while (positionInBounds(n, row, col)) {
    if (board[row][col] == 'U') {
      return false;
    } else if (board[row][col] == colour) {
      return true;
    }
    row += deltaRow;
    col += deltaCol;
  } 
  return false;
}

void copied(char copy[8][26], const char board[][26]) {
  memcpy(copy, board, sizeof(char) * 64);
}

char* changeDirection(char boarddd[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
  char oppColour;
  int roww = row;
  int coll = col;
  if (colour == 'W') {
    oppColour = 'B';
  } else {
    oppColour = 'W';
  }

  row += deltaRow;
  col += deltaCol;
  if (boarddd[row][col] != oppColour) {
    return boarddd;
  }
  row += deltaRow;
  col += deltaCol;
  while (positionInBounds(n, row, col)) {
    if (boarddd[row][col] == 'U') {
      return boarddd;
    } else if (boarddd[row][col] == colour) {
      break;
    }
    row += deltaRow;
    col += deltaCol;
  } 
  if (!positionInBounds(n, row, col)) {
    return boarddd;
  }

  roww += deltaRow;
  coll += deltaCol;
  while (boarddd[roww][coll] != colour) {
    boarddd[roww][coll] = colour;
    roww += deltaRow;
    coll += deltaCol;
  }
  return boarddd;
}

void updateBoard(char boardd[][26], int n, int row, int col, char colour) {
  for (int i = -1; i < 2; i++) {
    changeDirection(boardd, n, row, col, colour, -1, i);
  }
  for (int i = -1; i < 2; i++) {
    changeDirection(boardd, n, row, col, colour, 1, i);
  }
  changeDirection(boardd, n, row, col, colour, 0, 1);
  changeDirection(boardd, n, row, col, colour, 0, -1);
  boardd[row][col] = colour;
}