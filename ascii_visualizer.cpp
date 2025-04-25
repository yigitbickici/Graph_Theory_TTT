#include <iostream>
#include <vector>
#include <string>
using namespace std;

class ASCIIGameTree {
private:
    void printBoard(const vector<vector<char>>& board, int depth) {
        string indent(depth * 4, ' ');
        cout << indent << "┌───┬───┬───┐\n";
        for (int i = 0; i < 3; i++) {
            cout << indent << "│ ";
            for (int j = 0; j < 3; j++) {
                cout << (board[i][j] == ' ' ? ' ' : board[i][j]) << " │ ";
            }
            cout << "\n";
            if (i < 2) cout << indent << "├───┼───┼───┤\n";
        }
        cout << indent << "└───┴───┴───┘\n";
    }

    void printConnector(int depth) {
        string indent(depth * 4, ' ');
        cout << indent << "    │\n";
        cout << indent << "    ▼\n";
    }

public:
    void visualizeGame(const vector<vector<vector<char>>>& gameStates) {
        for (size_t i = 0; i < gameStates.size(); i++) {
            printBoard(gameStates[i], i);
            if (i < gameStates.size() - 1) {
                printConnector(i);
            }
        }
    }
};

// Örnek kullanım
void testASCIIVisualization() {
    ASCIIGameTree visualizer;
    
    vector<vector<vector<char>>> gameStates = {
        {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
        },
        {
            {'X', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
        },
        {
            {'X', ' ', ' '},
            {' ', 'O', ' '},
            {' ', ' ', ' '}
        }
    };
    
    visualizer.visualizeGame(gameStates);
} 