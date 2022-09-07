# Domina

**Domina** is a project realised during the first year at Ca' Foscari University, required as a project for the programming and laboratory exam.

## Description

The project consisted of creating the class 'player.cpp' which was to simulate some clever strategy in order to create an executable that would play draughts automatically, with simplified rules.

The simulation of a match takes place in this manner:
1. Initially, the verifier creates an initial chessboard and saves it in "board_1.txt".
2. Player1 loads "board_1.txt", makes a move, and saves the resulting chessboard in "board_2.txt".
3. The verifier loads board_2.txt and verifies that the move is valid. If it is not, the player is disqualified. If it is, the game continues.
4. Player2 loads "board_2.txt", makes a move, and saves the resulting chessboard in "board_3.txt".
5. The verifier verifies that the move is valid. If it is not, the player is disqualified. If it is, the game continues.
6. ... and so on, until the end of the game. 

## Usage

```bash
# to compile
make play

#to cleanup boards folder
make clean
```

## Implemented Strategy

I chose to use a pseudo-random strategy in order to avoid stalemates during the game. 
I wrote pseudo-random because I have decided to implement a system that creates a sort of prioritisation with moves that can potentially bring the game to a more advanced state, prioritising the movement of dames or pieces that can eliminate opposing pieces.

**N.B.** According to the project rules, you could not import external libraries, except for 'player.hpp'.

## Contributing

Pull requests are welcome as well as advice and criticism.