# C++ Chess

This is a chess app written in C++. It's primary purpose is for me to learn C++.

Most of the code is in Vecboard.cpp. This file defines several functions that assist in the parsing of a chess game written in PGN ([portable game notation](https://en.wikipedia.org/wiki/Portable_Game_Notation)) format. PGN format is the most common way of writing chess moves. It provides enough information to recreate a game of chess from start to finish, eliminating any ambiguity that may arise. The main problem that this file solves is taking the current board state and a move as a SAN ([standard algebraic notation](https://en.wikipedia.org/wiki/Algebraic_notation_(chess))) string and determining the starting and destination squares.

Most modern chess engines take a fundamentally different approach to game-state representation and move generation than is found in this project. This project uses a 2D Vector to represent the board (board-centric). This is in contrast to the bitboard representation that is used in most modern engines (piece-centric). The bitboard representation is more efficient and allows for faster move generation. However, the board-centric representation is easier to understand and is more intuitive. Which is why I chose to use it. 

The main functions in Vecboard.cpp are:

- `void move(string san)`: Moves a piece from one square to another given the SAN string. Handles move logic and validation and relies on many of the other functions below.
- `vector<pair<int, int>> getValidMoves(int x, int y)`: Returns a vector of pairs of indices that represent the valid moves for a piece at a given square.
- `pair<pair<int, int>, pair<int, int>> sanToIndices(const string& san)` : Converts a SAN move to a pair of pairs of indices for the origin and destination squares.

Other useful functions include:

- `void start()`: Sets pieces to their starting positions.
- `void load(string fen)`: Loads a board state from a FEN string.
- `void forceMove(int fromX, int fromY, int toX, int toY)`: Moves a piece from one square to another.
- `void print()`: Prints the current board state to the console.

## TODO

- Checkmate detection

- board.prev(), board.next(), board.start: Search through the moves 

- board.eval(): Evaluate the current players position with an integer

- board.play(): Play moves against a basic engine

- Refactor the move validation for pins.