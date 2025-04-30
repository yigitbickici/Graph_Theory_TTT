#include <iostream>
#include <vector>
#include <limits>
#include <random>
#include <ctime>
#include "GameTreeVisualizer.h"
using namespace std;

class TicTacToe {
private:
    vector<vector<char>> board;
    char player;
    char computer;
    int difficulty; 
    GameTreeVisualizer visualizer;
    vector<vector<vector<char>>> gameHistory;
    int currentNodeId;

    bool isMovesLeft() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == ' ')
                    return true;
        return false;
    }

    int evaluate() {
        for (int row = 0; row < 3; row++) {
            if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
                if (board[row][0] == computer) return +10;
                else if (board[row][0] == player) return -10;
            }
        }

        for (int col = 0; col < 3; col++) {
            if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
                if (board[0][col] == computer) return +10;
                else if (board[0][col] == player) return -10;
            }
        }

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == computer) return +10;
            else if (board[0][0] == player) return -10;
        }

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == computer) return +10;
            else if (board[0][2] == player) return -10;
        }

        return 0;
    }

    int minimax(int depth, bool isMax, int alpha, int beta, int parentNodeId) {
        int score = evaluate();

        if (score == 10) return score - depth;
        if (score == -10) return score + depth;
        if (!isMovesLeft()) return 0;

        if (isMax) {
            int best = -1000;
            bool pruned = false;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = computer;
                        int nodeId = visualizer.addNode(board, parentNodeId, pruned);
                        int moveVal = minimax(depth + 1, !isMax, alpha, beta, nodeId);
                        board[i][j] = ' ';
                        best = max(best, moveVal);
                        alpha = max(alpha, best);
                        if (beta <= alpha) {
                            pruned = true;
                            break;
                        }
                    }
                }
                if (pruned) break;
            }
            return best;
        } else {
            int best = 1000;
            bool pruned = false;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = player;
                        int nodeId = visualizer.addNode(board, parentNodeId, pruned);
                        int moveVal = minimax(depth + 1, !isMax, alpha, beta, nodeId);
                        board[i][j] = ' ';
                        best = min(best, moveVal);
                        beta = min(beta, best);
                        if (beta <= alpha) {
                            pruned = true;
                            break;
                        }
                    }
                }
                if (pruned) break;
            }
            return best;
        }
    }

    pair<int, int> findBestMove() {
        int bestVal = -1000;
        pair<int, int> bestMove = {-1, -1};
        vector<pair<int, int>> possibleMoves;
        vector<pair<int, int>> allMoves; 

        int rootNodeId = visualizer.addNode(board);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    allMoves.push_back({i, j}); 
                    board[i][j] = computer;
                    int nodeId = visualizer.addNode(board, rootNodeId);
                    int moveVal = minimax(0, false, -1000, 1000, nodeId);
                    board[i][j] = ' ';

                    if (moveVal > bestVal) {
                        bestVal = moveVal;
                        bestMove = {i, j};
                        possibleMoves.clear();
                        possibleMoves.push_back({i, j});
                    } else if (moveVal == bestVal) {
                        possibleMoves.push_back({i, j});
                    }
                }
            }
        }

        if (difficulty == 1) {
            if (rand() % 2 == 0) {
                return bestMove;
            } else {
                int randomIndex = rand() % allMoves.size();
                return allMoves[randomIndex];
            }
        }
        else if (difficulty == 2) {
            if (rand() % 4 != 0) {
                return bestMove;
            } else {
                int randomIndex = rand() % allMoves.size();
                return allMoves[randomIndex];
            }
        }
        else {
            return bestMove;
        }
    }

public:
    TicTacToe(int diff) : difficulty(diff) {
        board = vector<vector<char>>(3, vector<char>(3, ' '));
        player = 'X';
        computer = 'O';
        visualizer.startVisualization("game_history.dot");
        gameHistory.push_back(board);
        currentNodeId = visualizer.addNode(board);
    }

    void printBoard() {
        cout << "\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << board[i][j];
                if (j < 2) cout << " | ";
            }
            cout << "\n";
            if (i < 2) cout << "---------\n";
        }
        cout << "\n";
    }

    bool makeMove(int row, int col) {
        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            return false;
        }
        board[row][col] = player;
        gameHistory.push_back(board);
        currentNodeId = visualizer.addNode(board, currentNodeId);
        return true;
    }

    void computerMove() {
        pair<int, int> move = findBestMove();
        board[move.first][move.second] = computer;
        gameHistory.push_back(board);
        currentNodeId = visualizer.addNode(board, currentNodeId);
    }

    bool isGameOver() {
        int score = evaluate();
        if (score == 10) {
            printBoard();
            cout << "Computer wins!\n";
            visualizer.endVisualization();
            cout << "Game tree saved to 'game_history.dot'.\n";
            cout << "To visualize: dot -Tpng game_history.dot -o game_history.png\n";
            return true;
        }
        if (score == -10) {
            printBoard();
            cout << "Congratulations! You win!\n";
            visualizer.endVisualization();
            cout << "Game tree saved to 'game_history.dot'.\n";
            cout << "To visualize: dot -Tpng game_history.dot -o game_history.png\n";
            return true;
        }
        if (!isMovesLeft()) {
            printBoard();
            cout << "Draw!\n";
            visualizer.endVisualization();
            cout << "Game tree saved to 'game_history.dot'.\n";
            cout << "To visualize: dot -Tpng game_history.dot -o game_history.png\n";
            return true;
        }
        return false;
    }
};

int main() {
    srand(time(0));
    int difficulty;
    do {
        cout << "Select difficulty level (1: Easy, 2: Medium, 3: Hard): ";
        cin >> difficulty;
        cout << "difficulty: " << difficulty << endl;
    } while (difficulty < 1 || difficulty > 3);

    TicTacToe game(difficulty);
    int row, col;

    while (true) {
        game.printBoard();
        cout << "Enter your move (row column, 0-2): ";
        cin >> row >> col;

        if (!game.makeMove(row, col)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        if (game.isGameOver()) break;

        cout << "Computer is thinking...\n";
        game.computerMove();

        if (game.isGameOver()) break;
    }

    return 0;
} 