#ifndef GAMETREEVISUALIZER_H
#define GAMETREEVISUALIZER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class GameTreeVisualizer {
private:
    std::ofstream dotFile;
    int nodeCount = 0;

    std::string getNodeLabel(const std::vector<std::vector<char>>& board) {
        std::string label = "";
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
    void startVisualization(const std::string& filename) {
        dotFile.open(filename);
        dotFile << "digraph GameTree {\n";
        dotFile << "node [shape=box, style=filled, fillcolor=lightblue];\n";
    }

    int addNode(const std::vector<std::vector<char>>& board, int parentId = -1) {
        int currentId = nodeCount++;
        std::string label = getNodeLabel(board);
        
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

#endif // GAMETREEVISUALIZER_H 