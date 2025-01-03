# tictactoe
## Overview

This is a simple implementation of the Tic Tac Toe game in C++. The game is played on a 3x3 grid where two players take turns marking a cell with their respective symbols (X or O). The player who succeeds in placing three of their marks in a horizontal, vertical, or diagonal row wins the game.

## Features

- Two-player mode
- Simple text-based interface
- Input validation
- Win detection

## Requirements

- C++11 or higher
- A C++ compiler (e.g., g++)

## How to Compile

To compile the program, navigate to the directory containing the source code and run the following command:

```sh
g++ -o tictactoe tictactoe.cpp
```

## How to Run

After compiling, you can run the program with:

```sh
./tictactoe
```

## How to Play

1. The game will prompt Player 1 (X) to enter their move.
2. Player 1 will enter the row and column number to place their mark.
3. The game will then prompt Player 2 (O) to enter their move.
4. Players take turns until one player wins or the game ends in a draw.

## Example

```
Player 1 (X) - Enter your move (row and column): 1 1
Player 2 (O) - Enter your move (row and column): 1 2
...
```

## License

This project is licensed under the MIT License.