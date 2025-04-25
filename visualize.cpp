#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class GameTreeVisualizer {
private:
    ofstream dotFile;
    int nodeCount = 0;

    string getNodeLabel(const vector<vector<char>>& board) {
        string label = "";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                label += board[i][j] == ' ' ? '_' : board[i][j];
                if (j < 2) label += "|";
            }
            if (i < 2) label += "\\n";
        }
        return label;
    }

public:
    void startVisualization(const string& filename) {
        dotFile.open(filename);
        dotFile << "digraph GameTree {\n";
        dotFile << "node [shape=box, style=filled, fillcolor=lightblue];\n";
    }

    int addNode(const vector<vector<char>>& board, int parentId = -1) {
        int currentId = nodeCount++;
        string label = getNodeLabel(board);
        
        dotFile << "node" << currentId << " [label=\"" << label << "\"];\n";
        if (parentId != -1) {
            dotFile << "node" << parentId << " -> node" << currentId << ";\n";
        }
        
        return currentId;
    }

    void endVisualization() {
        dotFile << "}\n";
        dotFile.close();
    }
};

// Örnek kullanım için test fonksiyonu
void testVisualization() {
    GameTreeVisualizer visualizer;
    visualizer.startVisualization("game_tree.dot");
    
    // Başlangıç durumu
    vector<vector<char>> initialBoard = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    int rootId = visualizer.addNode(initialBoard);
    
    // İlk hamle (X)
    vector<vector<char>> firstMove = {
        {'X', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    int firstMoveId = visualizer.addNode(firstMove, rootId);
    
    // Bilgisayar hamlesi (O)
    vector<vector<char>> computerMove = {
        {'X', ' ', ' '},
        {' ', 'O', ' '},
        {' ', ' ', ' '}
    };
    int computerMoveId = visualizer.addNode(computerMove, firstMoveId);
    
    visualizer.endVisualization();
    
    cout << "Görselleştirme dosyası oluşturuldu: game_tree.dot\n";
    cout << "Bu dosyayı Graphviz ile görselleştirmek için şu komutu kullanın:\n";
    cout << "dot -Tpng game_tree.dot -o game_tree.png\n";
}

int main() {
    testVisualization();
    return 0;
} 