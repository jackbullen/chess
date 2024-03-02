#include "PGNReader.h"

using namespace std;

PGNReader::PGNReader(const string& filename) : file(filename) {
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }
}

PGNReader::Game PGNReader::parseGame() {
    string line;
    Game game;

    while (getline(file, line)) {
        if (line.empty()) continue;
        if (line[0] == '[') {
            // Parse game metadata
            if (line.find("[Event ") == 0)
                game.event = line.substr(8, line.size() - 10);
            else if (line.find("[Site ") == 0)
                game.site = line.substr(7, line.size() - 9);
            else if (line.find("[Date ") == 0)
                game.date = line.substr(7, line.size() - 9);
            else if (line.find("[Round ") == 0)
                game.round = line.substr(8, line.size() - 10);
            else if (line.find("[White ") == 0)
                game.white = line.substr(8, line.size() - 10);
            else if (line.find("[Black ") == 0)
                game.black = line.substr(8, line.size() - 10);
            else if (line.find("[Result ") == 0)
                game.result = line.substr(9, line.size() - 11);
            else if (line.find("[WhiteElo ") == 0)
                game.whiteElo = line.substr(11, line.size() - 13);
            else if (line.find("[BlackElo ") == 0)
                game.blackElo = line.substr(11, line.size() - 13);
            else if (line.find("[ECO ") == 0)
                game.eco = line.substr(6, line.size() - 8);
        } else {
            // Parse game moves
            istringstream iss_moves(line);
            string move;
            while (iss_moves >> move) {
                size_t pos = move.find('.');
                if (pos != string::npos) {
                    // Split the string into white and black moves
                    string white_move = move.substr(0, pos);
                    string black_move = move.substr(pos + 1);

                    // Add the moves to the list
                    if (!white_move.empty()) game.moves.push_back(white_move);
                    if (!black_move.empty()) game.moves.push_back(black_move);
                } else {
                    game.moves.push_back(move);
                }
            }
        }
    }
    return game;
}

VecBoard PGNReader::createBoard(const Game& game) {
    VecBoard board;
    board.start();

    for (const auto& move : game.moves) {
        if (std::all_of(move.begin(), move.end(), ::isdigit)) {
            cout << move << ".";
            continue;
        }

        pair<pair<int, int>, pair<int, int> > indices = board.sanToIndices(move);
        cout << "san = " << move << " " << indices.first.first << " " << indices.first.second << " " << indices.second.first << " " << indices.second.second << endl;
        board.print();
    }

    return board;
}