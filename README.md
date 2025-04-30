# 🎮 Tic-Tac-Toe Game with Graph Theory Implementation

A sophisticated implementation of the classic Tic-Tac-Toe game that demonstrates the application of Graph Theory concepts and AI algorithms.

![Game Preview](game_preview.png)

## 📋 Table of Contents
- [Features](#-features)
- [Installation](#-installation)
- [Usage](#-usage)
- [Game Rules](#-game-rules)
- [Graph Theory Concepts](#-graph-theory-concepts)
- [Technical Details](#-technical-details)
- [Contributing](#-contributing)
- [License](#-license)

## ✨ Features

### Difficulty Levels
- **Easy**: Computer plays optimally 50% of the time, randomly 50% of the time
- **Medium**: Computer plays optimally 75% of the time, randomly 25% of the time
- **Hard**: Computer always plays the optimal move

### Technical Features
- 🧠 Minimax algorithm implementation
- ⚡ Alpha-Beta pruning optimization
- 🎯 Optimal game strategy
- 🖥️ User-friendly command-line interface

## 💻 Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/Graph_Theory_TTT.git
cd Graph_Theory_TTT
```

2. Compile the game:
```bash
g++ main.cpp -o tictactoe
```

## 🎮 Usage

Run the game:
```bash
./tictactoe
```

## 📜 Game Rules

- Played on a 3×3 grid
- Players alternate placing their marks (X for human, O for computer)
- Input moves using row and column numbers (0-2)
- First player to get three marks in a row (horizontally, vertically, or diagonally) wins
- Game ends in a draw if all cells are filled without a winner

## 📊 Graph Theory Concepts

### Game Tree Representation
- Each node represents a game state
- Edges represent possible moves
- Terminal nodes represent game outcomes (win, lose, draw)

### Algorithm Implementation
- **Minimax Algorithm**
  - Maximizes the minimum possible gain
  - Minimizes the maximum possible loss
  - Implements optimal strategy for both players

- **Alpha-Beta Pruning**
  - Reduces search space
  - Improves algorithm efficiency
  - Eliminates unnecessary node evaluations

### Theoretical Foundations
- Zero-sum games
- Nash equilibrium
- Game tree complexity
- Optimal strategy determination

## 🔧 Technical Details

### Complexity Analysis
- Game tree size: 9! = 362,880 possible states
- Minimax time complexity: O(b^d)
- Alpha-Beta pruning optimization: O(b^(d/2))
- Space complexity: O(bd)

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
