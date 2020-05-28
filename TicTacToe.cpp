#include<iostream>
#include<cmath>
#include<map>
#include<vector>
using namespace std;
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
void Display_Board(vector<char> &board)
{
	int n = board.size();
	int mod = (int)sqrt(n);

	for (int x = 1; x <= n; x++) {
		cout << " | " << board[x - 1];
		if (x % mod == 0)
			cout << " |" << endl;
	}
}

bool Check_Move(vector<char>& board, int move)
{
	if (board[move] == 'x' || board[move] == 'o') {
		cout << "spot is already taken, please try again." << endl;
		return false;
	}
	return true;
}

void Move(vector<char>& board, int move) { board[move] = 'x'; }

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

//If this returns 0: game is still going, 1: x wins, 2: draw, 3: o wins .
int _3x3Win(vector<char>& board)
{
	//Check horizontal and vertical win.
	for (int i = 0; i < 9; i+=3)
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

int Min(vector<char> &board);
int Max(vector<char> &board);

int MinMax(vector<char> &board)
{
	vector<int> actions = Actions(board);
	int max = -99999;
	int j;
	vector<char> copy;

	for (int i = 0; i < actions.size(); i++)
	{
		copy = board;
		copy[actions[i]] = 'o';
		//board[actions[i]] = 'o';
		int min = Min(copy);
		if (min > max)
		{
			max = min;
			j = actions[i];
		}
	}
	return j;
}

int Min(vector<char> &board)
{
	int state = _3x3Win(board);
	if (state != 0)
	{
		return state;
	}
	vector<int> actions = Actions(board);
	vector<char> copy;

	int v = 99999;
	for (int i = 0; i < actions.size(); i++)
	{
		copy = board;
		copy[actions[i]] = 'x';
		//board[actions[i]] = 'o';
		int max = Max(copy);
		if (v > max)
		{
			v = max;
		}
	}
	return v;
}

int Max(vector<char> &board)
{
	int state = _3x3Win(board);
	vector<int> actions = Actions(board);
	vector<char> copy;
	if (state != 0)
	{
		return state;
	}

	int v = -9999;
	for (int i = 0; i < actions.size(); i++)
	{
		copy = board;
		copy[actions[i]] = 'o';
		//board[actions[i]] = 'x';
		int min = Min(copy);
		if (v < min) 
		{
			v = min;
		}
	}
	return v;
}

int Robit_Move(vector<char>& board)
{
	return MinMax(board);
}

int main()
{
	int n = 3;
	//initialize board.
	vector<char> board = Initialize_Board(n);
	int player_move;
	cout << "Welcome to the game." << endl;
	Display_Board(board);
	cout << endl;
	bool turn = true;
	while (true)
	{
		//Player goes first.
		if (turn) {
			cout << "Please enter the move you want to make(0-8): ";
			cin >> player_move;
			while (!Check_Move(board, player_move))
			{
				cout << "Please enter the move you want to make(0-8): ";
				cin >> player_move;
			}
			Move(board, player_move);
			Display_Board(board);
			cout << endl;
			turn = false;
			int state = _3x3Win(board);
			if (state == 1)
			{
				cout << "Congrats, human player has won." << endl;
				break;
			}
			else if (state == 2)
			{
				cout << "A draw... darn it." << endl;
				break;
			}
			else
			{
				cout << "Robit is making a move." << endl;
				board[Robit_Move(board)] = 'o';
				turn = true;
				Display_Board(board);
				cout << endl;
				state = _3x3Win(board);
				if (state == 3)
				{
					cout << "Robit has won. So sad." << endl;
					break;
				}
				else if (state == 2)
				{
					cout << "A draw... darn it." << endl;
					break;
				}
			}
		}
	}
	system("pause");
	return 0;
}