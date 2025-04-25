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
    int difficulty; // 1: Kolay, 2: Orta, 3: Zor
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
        // Satır kontrolü
        for (int row = 0; row < 3; row++) {
            if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
                if (board[row][0] == computer) return +10;
                else if (board[row][0] == player) return -10;
            }
        }

        // Sütun kontrolü
        for (int col = 0; col < 3; col++) {
            if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
                if (board[0][col] == computer) return +10;
                else if (board[0][col] == player) return -10;
            }
        }

        // Çapraz kontrol
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

    int minimax(int depth, bool isMax, int alpha, int beta) {
        int score = evaluate();

        if (score == 10) return score - depth;
        if (score == -10) return score + depth;
        if (!isMovesLeft()) return 0;

        if (isMax) {
            int best = -1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = computer;
                        best = max(best, minimax(depth + 1, !isMax, alpha, beta));
                        board[i][j] = ' ';
                        alpha = max(alpha, best);
                        if (beta <= alpha) break;
                    }
                }
            }
            return best;
        } else {
            int best = 1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = player;
                        best = min(best, minimax(depth + 1, !isMax, alpha, beta));
                        board[i][j] = ' ';
                        beta = min(beta, best);
                        if (beta <= alpha) break;
                    }
                }
            }
            return best;
        }
    }

    pair<int, int> findBestMove() {
        int bestVal = -1000;
        pair<int, int> bestMove = {-1, -1};
        vector<pair<int, int>> possibleMoves;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = computer;
                    int moveVal = minimax(0, false, -1000, 1000);
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

        // Zorluk seviyesine göre rastgele hamle seçimi
        if (difficulty == 1) {
            // Kolay: %50 ihtimalle en iyi hamleyi, %50 ihtimalle rastgele hamle yapar
            if (rand() % 2 == 0) {
                return bestMove;
            } else {
                int randomIndex = rand() % possibleMoves.size();
                return possibleMoves[randomIndex];
            }
        } else if (difficulty == 2) {
            // Orta: %75 ihtimalle en iyi hamleyi, %25 ihtimalle rastgele hamle yapar
            if (rand() % 4 != 0) {
                return bestMove;
            } else {
                int randomIndex = rand() % possibleMoves.size();
                return possibleMoves[randomIndex];
            }
        } else {
            // Zor: Her zaman en iyi hamleyi yapar
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
            cout << "Bilgisayar kazandı!\n";
            visualizer.endVisualization();
            cout << "Oyun ağacı 'game_history.dot' dosyasına kaydedildi.\n";
            cout << "Görselleştirmek için: dot -Tpng game_history.dot -o game_history.png\n";
            return true;
        }
        if (score == -10) {
            printBoard();
            cout << "Tebrikler! Siz kazandınız!\n";
            visualizer.endVisualization();
            cout << "Oyun ağacı 'game_history.dot' dosyasına kaydedildi.\n";
            cout << "Görselleştirmek için: dot -Tpng game_history.dot -o game_history.png\n";
            return true;
        }
        if (!isMovesLeft()) {
            printBoard();
            cout << "Berabere!\n";
            visualizer.endVisualization();
            cout << "Oyun ağacı 'game_history.dot' dosyasına kaydedildi.\n";
            cout << "Görselleştirmek için: dot -Tpng game_history.dot -o game_history.png\n";
            return true;
        }
        return false;
    }
};

int main() {
    srand(time(0));
    int difficulty;
    cout << "Zorluk seviyesini seçin (1: Kolay, 2: Orta, 3: Zor): ";
    cin >> difficulty;

    TicTacToe game(difficulty);
    int row, col;

    while (true) {
        game.printBoard();
        cout << "Hamlenizi girin (satır sütun, 0-2 arası): ";
        cin >> row >> col;

        if (!game.makeMove(row, col)) {
            cout << "Geçersiz hamle! Tekrar deneyin.\n";
            continue;
        }

        if (game.isGameOver()) break;

        cout << "Bilgisayar düşünüyor...\n";
        game.computerMove();

        if (game.isGameOver()) break;
    }

    return 0;
} 