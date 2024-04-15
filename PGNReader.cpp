#include "PGNReader.h"

using namespace std;

PGNReader::PGNReader(const string& filename) : file(filename) {
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }
}

GameBoard PGNReader::parseGame() {
    string line;
    Game game;
    GameBoard board;

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
            int ct = 0;
            while (iss_moves >> move) {
                ct++;
                if (ct > 350) {
                    cout << "WARNING: Game has more than 350 moves.";
                }
                size_t pos = move.find('.');
                if (pos != string::npos) {
                    // Get the moves and and to out list
                    string white_move = move.substr(0, pos);
                    string black_move = move.substr(pos + 1);
                    if (!white_move.empty()) game.moves.push_back(white_move);
                    if (!black_move.empty()) game.moves.push_back(black_move);
                } else if (move == "1-0" || move == "0-1" || move == "1/2-1/2" || move == "*") {
                    board = printGame(game);
                    return board;
                } else {
                    game.moves.push_back(move);
                }

            }
        }
    }
    board = printGame(game);
    return board;
}

GameBoard PGNReader::printGame(const Game& game) {
    cout << game.event << endl;
    cout << game.site << endl;
    cout << game.date << endl;
    cout << game.round << endl;
    cout << game.white << endl;
    cout << game.black << endl;
    cout << game.result << endl;
    cout << game.whiteElo << endl;
    cout << game.blackElo << endl;
    GameBoard board;
    int move_number = 1;
    for (const auto& move : game.moves) {
        if (std::all_of(move.begin(), move.end(), ::isdigit)) {
            continue;
        }
        if (move == "1-0" || move == "0-1" || move == "1/2-1/2" || move == "*") {
            return board;
        }
        board.move(move);
        if (move_number % 2 == 0) {
            cout << move_number / 2 << "... " << move << endl;
        } else {
            cout << move_number / 2 + 1 << ". " << move << " " << endl;
        }
        board.print();
        move_number++;
    }
    return board;
}