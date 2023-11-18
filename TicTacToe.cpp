#include <iostream>
#include <climits>

char board[3][3];
const char PLAYER = 'X';
const char PLAYER2 = 'O';
const char COMPUTER = 'O';
int choice = 0;

// Function prototypes
void reset_board();
void print_board();
int check_free_spaces();
void player_move();
void player2_move();
void computer_move();
char check_winner();
void print_winner(char winner);
int minimax(char board[3][3], int depth, bool isMaximizing);

int main()
{
    char playAgain;
    do
    {
        std::cout << "Welcome to Tic-Tac-Toe!\n";
        std::cout << "Choose an option:\n";
        std::cout << "1. Play against the computer\n";
        std::cout << "2. Play against another player\n";
        std::cin >> choice;

        reset_board();
        char winner = ' ';
        while (winner == ' ' && check_free_spaces() != 0)
        {
            print_board();
            if (choice == 1)
            {
                player_move();
                winner = check_winner();
                if (winner != ' ' || check_free_spaces() == 0)
                    break;
                print_board();
                computer_move();
                winner = check_winner();
                if (winner != ' ' || check_free_spaces() == 0)
                    break;
            }
            else if (choice == 2)
            {
                player_move();
                winner = check_winner();
                if (winner != ' ' || check_free_spaces() == 0)
                    break;
                print_board();
                player2_move();
                winner = check_winner();
                if (winner != ' ' || check_free_spaces() == 0)
                    break;
            }
            else
                std::cout << "Invalid choice. Please choose 1 or 2.\n";
        }
        print_board();
        print_winner(winner);

        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> playAgain;
    }
    while (playAgain == 'y' || playAgain == 'Y');


    return 0;
}

void reset_board()
{
    for (int i = 0; i < 3; i++)
	{
        for (int j = 0; j < 3; j++)
		{
            board[i][j] = ' ';
        }
    }
}

void print_board()
{
    std::cout << "   1   2   3\n";
    std::cout << "1  " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
    std::cout << "  ---|---|---\n";
    std::cout << "2  " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n";
    std::cout << "  ---|---|---\n";
    std::cout << "3  " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n";
}

int check_free_spaces()
{
    int free_spaces = 9;
    for (int i = 0; i < 3; i++)
	{
        for (int j = 0; j < 3; j++)
		{
            if (board[i][j] != ' ')
                free_spaces--;
        }
    }

    return free_spaces;
}

void player_move()
{
    int x, y;
    std::cout << "Player 1 turn\n";
    do
	{
        std::cout << "Enter row number from 1 to 3: ";
        std::cin >> x;
        x--;

        std::cout << "Enter column number from 1 to 3: ";
        std::cin >> y;
        y--;

        if (board[x][y] != ' ')
            std::cout << "This cell is occupied!\n";
		else
            board[x][y] = PLAYER;
            break;
    } while (board[x][y] != ' ');
}

void player2_move()
{
    int x, y;
    std::cout << "Player 2 turn\n";
    do
	{
        std::cout << "Enter row number from 1 to 3: ";
        std::cin >> x;
        x--;

        std::cout << "Enter column number from 1 to 3: ";
        std::cin >> y;
        y--;

        if (board[x][y] != ' ')
            std::cout << "This cell is occupied!\n";
        else
		{
            board[x][y] = PLAYER2;
            break;
        }
    } while (board[x][y] != ' ');
}

void computer_move()
{
    int bestMove[2] = {-1, -1};
    int bestScore = INT_MIN;

    for (int i = 0; i < 3; ++i)
	{
        for (int j = 0; j < 3; ++j)
		{
            if (board[i][j] == ' ')
			{
                board[i][j] = COMPUTER;
                int score = minimax(board, 0, false);
                board[i][j] = ' ';

                if (score > bestScore)
				{
                    bestScore = score;
                    bestMove[0] = i;
                    bestMove[1] = j;
                }
            }
        }
    }

    int x = bestMove[0];
    int y = bestMove[1];

    std::cout << "Computer chose: " << x + 1 << ", " << y + 1 << "\n";
    board[x][y] = COMPUTER;
}

char check_winner()
{
    // Row check
    for (int i = 0; i < 3; i++)
	{
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
            return board[i][0];
    }
    // Column check
    for (int i = 0; i < 3; i++)
	{
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return board[0][i];
    }
    // Diagonal check
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
        return board[0][0];
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
        return board[0][2];

    return ' ';
}

void print_winner(char winner)
{
    if (winner == 'X')
        std::cout << "\nPlayer 1 won!\n";
	else if (winner == 'O' && choice == 1)
		std::cout << "\nComputer won!\n";
	else if (winner == 'O' && choice == 2)
        std::cout << "\nPlayer 2 won!\n";
	else
        std::cout << "\nDraw!\n";
}

int minimax(char board[3][3], int depth, bool isMaximizing)
{
	//Checks if the game ended
    char result = check_winner();
    if (result != ' ') {
        if (result == COMPUTER)
            return 1;
        else if (result == PLAYER)
            return -1;
        else
            return 0;
    }
	//Checks if the board is full
    if (check_free_spaces() == 0)
        return 0;

	//MiniMax algorithm - Evaluates all posible moves
    if (isMaximizing) //if isMaximizing == true then computer's move is evaluated
	{
        int maxEval = INT_MIN; //maxEval (Best score) variable represents best move of a computer
        for (int i = 0; i < 3; ++i)
		{
            for (int j = 0; j < 3; ++j)
			{
                if (board[i][j] == ' ')
				{
                    board[i][j] = COMPUTER; //Assumes if the curent move is made by a computer
					//depth represents a game tree. Bigger value of depth means computer goes deeper in the game tree
                    int eval = minimax(board, depth + 1, false);
                    board[i][j] = ' '; //Undo the move made by a computer
                    maxEval = std::max(maxEval, eval);
                }
            }
        }
        return maxEval;
    }
	else
	{
        int minEval = INT_MAX; //minEval (best score) variable represents best move of a player
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
			{
                if (board[i][j] == ' ')
				{
                    board[i][j] = PLAYER;
                    int eval = minimax(board, depth + 1, true);
                    board[i][j] = ' ';
                    minEval = std::min(minEval, eval);
                }
            }
        }
        return minEval;
    }
}


