# TODO

- Refactor the move validation for pins.
    - Move code into a seperate file from VecBoard
    - Write helper functions to reduce repeated code (currently repeated code chunk in KNIGHT and ROOK, this should be a function, and need to make same check for bishop, queen, and pawn moves)

- Evaluation function.

- Checkmate detection.

- Call getValidMoves(), then for each "make the move" and call evaluation, then recursively call getValidMoves() again, and so on, until depth is reached.