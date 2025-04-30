Tic-Tac-Toe Game

This project is a Tic-Tac-Toe (XOX) game developed using the Minimax algorithm. It allows the user to play against the computer and includes three difficulty levels.

Features

Three difficulty levels:
Easy: The computer plays the best move with a 50% chance and a random move with a 50% chance
Medium: The computer plays the best move with a 75% chance and a random move with a 25% chance
Hard: The computer always plays the best move
Optimal game strategy with the Minimax algorithm
Optimization with Alpha-Beta Pruning
User-friendly interface
Compilation and Execution

g++ main.cpp -o tictactoe
./tictactoe
Game Rules

The game is played on a 3x3 board
The player uses the symbol 'X', and the computer uses 'O'
Moves are made by entering row and column numbers (between 0 and 2)
The first player to align three of their symbols horizontally, vertically, or diagonally wins
If all cells are filled and no one has won, the game ends in a draw
Relation to Graph Theory

This project can be related to the following topics from Graph Theory:

Game Tree:
The Tic-Tac-Toe game can be modeled as a game tree that includes all possible moves
Each node represents a game state, and each edge represents a move
The Minimax algorithm operates on this tree
Minimax Algorithm:
Used to find the best move in the game tree
Determines the optimal strategy by computing maximum and minimum values
Reduces unnecessary searches with Alpha-Beta Pruning
Game Theory:
Zero-sum games
Nash equilibrium
Determining optimal strategies
Complexity Analysis:
Size and depth of the game tree
Time complexity of the Minimax algorithm
Optimization gained through Alpha-Beta Pruning
