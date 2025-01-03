#include <iostream>
#include <climits> // For INT_MIN and INT_MAX
using namespace std;

// Function prototypes
void displayBoard(char board[3][3]);                 // Displays the current state of the game board
bool checkWinner(char board[3][3], char player);     // Checks if the specified player has won
bool isBoardFull(char board[3][3]);                  // Checks if the board is full (i.e., no more moves)
int minimax(char board[3][3], bool isMaximizing);     // Implements the Minimax algorithm
int findBestMove(char board[3][3]);                   // Determines the best move for the computer

int main() {
    // Initialize the game board with numbers 1-9 representing each cell
    char board[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    char currentPlayer = 'X'; // Player always starts as 'X'
    int move;                  // Variable to store the player's move input
    bool gameRunning = true;   // Flag to control the game loop

    cout << "Welcome to Tic Tac Toe!\n";
    cout << "Player: X | Computer: O\n" << endl;

    // Main game loop
    while (gameRunning) {
        displayBoard(board); // Show the current board

        if (currentPlayer == 'X') {
            // Player's turn
            cout << "Player " << currentPlayer << ", enter your move (1-9): ";
            cin >> move;

            // Validate the input move
            if (move < 1 || move > 9) {
                cout << "Invalid move! Please enter a number between 1 and 9.\n";
                continue; // Prompt the player to enter a valid move
            }

            // Convert the move number to board coordinates (row and column)
            int row = (move - 1) / 3;
            int col = (move - 1) % 3;

            // Check if the chosen cell is already occupied
            if (board[row][col] == 'X' || board[row][col] == 'O') {
                cout << "Cell already taken! Please choose another cell.\n";
                continue; // Prompt the player to enter a different move
            }

            // Update the board with the player's move
            board[row][col] = currentPlayer;
        } else {
            // Computer's turn
            cout << "Computer's turn...\n";
            int bestMove = findBestMove(board); // Determine the best move for the computer

            // Convert the best move number to board coordinates
            int row = (bestMove - 1) / 3;
            int col = (bestMove - 1) % 3;

            // Update the board with the computer's move
            board[row][col] = 'O';
        }

        // Check if the current player has won the game
        if (checkWinner(board, currentPlayer)) {
            displayBoard(board); // Show the final board state
            if (currentPlayer == 'X') {
                cout << "Congratulations! You win!\n";
            } else {
                cout << "Computer wins! Better luck next time.\n";
            }
            gameRunning = false; // End the game
            continue;
        }

        // Check if the game is a draw (i.e., the board is full with no winner)
        if (isBoardFull(board)) {
            displayBoard(board); // Show the final board state
            cout << "It's a draw! Well played.\n";
            break; // End the game
        }

        // Switch turns between player and computer
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0; // Exit the program
}

// Function to display the current state of the game board
void displayBoard(char board[3][3]) {
    cout << "\n";
    for (int i = 0; i < 3; i++) { // Iterate through each row
        for (int j = 0; j < 3; j++) { // Iterate through each column in the row
            cout << board[i][j]; // Display the cell value
            if (j < 2) cout << " | "; // Add separator between cells
        }
        cout << "\n";
        if (i < 2) cout << "--|---|--\n"; // Add separator between rows
    }
    cout << "\n";
}

// Function to check if a specific player has won the game
bool checkWinner(char board[3][3], char player) {
    // Check all rows for a win
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player)) {
            return true; // Player has three in a row horizontally
        }
    }

    // Check all columns for a win
    for (int i = 0; i < 3; i++) {
        if ((board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true; // Player has three in a row vertically
        }
    }

    // Check the two diagonals for a win
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || // Main diagonal
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) { // Secondary diagonal
        return true; // Player has three in a row diagonally
    }

    return false; // No win condition met
}

// Function to check if the game board is full (no empty cells left)
bool isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++) { // Iterate through each row
        for (int j = 0; j < 3; j++) { // Iterate through each column in the row
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false; // Found an empty cell
            }
        }
    }
    return true; // All cells are occupied
}

// Minimax algorithm implementation to determine the optimal move
int minimax(char board[3][3], bool isMaximizing) {
    // Base cases: check if the computer or player has won, or if it's a draw
    if (checkWinner(board, 'O')) return 10;    // Computer wins
    if (checkWinner(board, 'X')) return -10;   // Player wins
    if (isBoardFull(board)) return 0;          // Draw

    if (isMaximizing) {
        int bestScore = INT_MIN; // Initialize to the smallest possible integer

        // Iterate through all cells to find the best move for the computer
        for (int i = 0; i < 3; i++) { // Rows
            for (int j = 0; j < 3; j++) { // Columns
                // Check if the cell is empty
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j]; // Store the current cell value
                    board[i][j] = 'O';       // Make the move for the computer

                    // Recursively call minimax for the next move (player's turn)
                    int score = minimax(board, false);

                    board[i][j] = temp; // Undo the move

                    bestScore = max(bestScore, score); // Choose the maximum score
                }
            }
        }
        return bestScore; // Return the best score for the computer
    } else {
        int bestScore = INT_MAX; // Initialize to the largest possible integer

        // Iterate through all cells to find the best move for the player
        for (int i = 0; i < 3; i++) { // Rows
            for (int j = 0; j < 3; j++) { // Columns
                // Check if the cell is empty
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j]; // Store the current cell value
                    board[i][j] = 'X';       // Make the move for the player

                    // Recursively call minimax for the next move (computer's turn)
                    int score = minimax(board, true);

                    board[i][j] = temp; // Undo the move

                    bestScore = min(bestScore, score); // Choose the minimum score
                }
            }
        }
        return bestScore; // Return the best score for the player
    }
}

// Function to find the best possible move for the computer using the Minimax algorithm
int findBestMove(char board[3][3]) {
    int bestScore = INT_MIN; // Initialize to the smallest possible integer
    int bestMove = -1;       // Variable to store the best move

    // Iterate through all cells to evaluate each possible move
    for (int i = 0; i < 3; i++) { // Rows
        for (int j = 0; j < 3; j++) { // Columns
            // Check if the cell is empty
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char temp = board[i][j]; // Store the current cell value
                board[i][j] = 'O';       // Make the move for the computer

                // Evaluate the move using minimax
                int score = minimax(board, false);

                board[i][j] = temp; // Undo the move

                // Update the best score and move if the current move is better
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = (i * 3 + j) + 1; // Convert row and column back to move number (1-9)
                }
            }
        }
    }
    return bestMove; // Return the best move number for the computer
}
