# Othello Game Introduction + Rules
Play against a **high-speed, advanced** computer AI in Othello, a modern spinoff of the traditional Reversi game from 1883! The following outlines the game rules:
* The 8x8 checkered board begins with a total of 4 tiles - 2 white and 2 black centered in the middle in an alternating pattern. All moves must be within the bounds from "a" to "h"
* A valid move consists of a tile placed such that in any 1 of 8 directions (N, NE, E, SE, S, SW, W, NW), there are 1+ opposite-coloured tiles placed right after it, and at the end of the opposite-coloured tiles, one of the player's tiles are found
* After placing a tile, all of the opposite-coloured tiles along the valid paths (for a maximum of 8 paths) are "flipped" over to the player's colour
* If one player has no moves, instead of the game ending (which is how Reversi is played), the other player continues to play until the original player has a move
* The game ends if the game board is filled up completely or both players have no moves
* The winner is the player with the most tiles, or the player who does not make an invalid move.

# How to Start the Match
1. Download the game folder
2. Choose the "Othello" folder to compile, then compile and run the game
3. Choose size 8 as the standard game board size
4. Choose which colour the computer should be
5. Play!

# Interesting Facts About the Computer AI
* The computer originally implemented the **Minimax search algorithm**, but after several iterations, it now implements **Alpha-Beta Pruning**
* It takes advantage of *heuristics* - it uses a **weighted board** to aid in its decision making, with each spot on the board being weighed from -4 to 4, with the corners being weighed at an astonishing 20 due to their great impact on the game outcome. **Play around with this board to see if you can improve the algorithm!**
* The computer goes **5 layers deep** in its algorithm - thinking **5 steps ahead** - to compute the best possible position to lay a tile! If you want to challenge yourself even more, **change the "ply" variable to a higher value in lines 306 and 337!**
