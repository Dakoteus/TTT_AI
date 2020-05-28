//TicTacToe.cpp
#include<iostream>
#include<cmath>
#include<map>
#include<vector>
using namespace std;

//functions are all listed here
int MinMax(vector<char>& board);
int Min(vector<char>& board, int a, int b);
int Max(vector<char>& board, int a, int b);
vector<char> Initialize_Board(int n);
void Display_Board(vector<char>& board);
bool Check_Move(vector<char>& board, int move);
vector<int> Actions(vector<char>& board);
int _3x3Win(vector<char>& board);
int Robit_Move(vector<char>& board);



//initialize n x n board.
//oriented from top left to bottom right in increasing ints.
vector<char> Initialize_Board(int n) {
	vector<char> board;
	for (int i = 0; i < n * n; i++)
	{
		board.push_back('-');
	}
	return board;
}

//display the board element by element.
void Display_Board(vector<char>& board)
{
	int n = board.size();
	int mod = (int)sqrt(n);

	for (int x = 1; x <= n; x++) {
		cout << " | " << board[x - 1];
		if (x % mod == 0)
			cout << " |" << endl;
	}
}

//checks to see if move is legal
bool Check_Move(vector<char>& board, int move)
{
	if (board[move] == 'x' || board[move] == 'o') {
		cout << "spot is already taken, please try again." << endl;
		return false;
	}
	return true;
}

//moves piece for player
void Move(vector<char>& board, int move) { 
	board[move] = 'x'; 
}

//given a board state, this returns a vector of the legal actions the player can take
vector<int> Actions(vector<char>& board)
{
	vector<int> actions;
	for (int i = 0; i < board.size(); i++)
	{
		if (board[i] != 'x' && board[i] != 'o')
			actions.push_back(i);
	}
	return actions;
}

//If this returns 0: game is still going, 1: x wins, 2: draw, 3: o wins 
int _3x3Win(vector<char>& board)
{
	//Check horizontal and vertical win.
	for (int i = 0; i < 9; i += 3)
	{
		if (board[i] == 'x' && board[i + 1] == 'x' && board[i + 2] == 'x')
			return 1;
		if (board[i] == 'o' && board[i + 1] == 'o' && board[i + 2] == 'o')
			return 3;
	}

	for (int i = 0; i < 3; i++)
	{
		if (board[i] == 'x' && board[i + 3] == 'x' && board[i + 6] == 'x')
			return 1;

		if (board[i] == 'o' && board[i + 3] == 'o' && board[i + 6] == 'o')
			return 3;
	}

	//Check diagonal win.
	if ((board[0] == 'x' && board[4] == 'x' && board[8] == 'x') || (board[2] == 'x' && board[4] == 'x' && board[6] == 'x'))
		return 1;
	if ((board[0] == 'o' && board[4] == 'o' && board[8] == 'o') || (board[2] == 'o' && board[4] == 'o' && board[6] == 'o'))
		return 3;

	//Check draw.
	bool notfull = false;
	for (int x = 0; x < board.size(); x++) {
		if (board[x] != 'o' && board[x] != 'x')
		{
			notfull = true;
			break;
		}
	}
	if (notfull == false)
		return 2;

	return 0;
}

//computes minimax move for robot
int Robit_Move(vector<char>& board)
{
	return MinMax(board);
}