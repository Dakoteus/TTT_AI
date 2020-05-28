#include"ToeHead.h"
using namespace std;

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
		int min = Min(copy,-9999,9999);
		if (min > max)
		{
			max = min;
			j = actions[i];
		}
	}
	return j;
}

int Min(vector<char> &board, int a, int b)
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
		int max = Max(copy,a,b);
		if (v > max){v = max;}
		if (v <= a){return v;}
		if (v < b) { b = v; }
	}
	return v;
}

int Max(vector<char> &board, int a, int b)
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
		int min = Min(copy,a,b);
		if (v < min) {v = min;}
		if (v >= b){return v;}
		if (v > a) { a = v; }
	}
	return v;
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
	//hot garbage for turn dialogue
	while (true)
	{
		//Player goes first.
		if (turn) {
			cout << "Please enter the move you want to make(1-9): ";
			cin >> player_move;
			while (!Check_Move(board, player_move-1))
			{
				cout << "Please enter the move you want to make(1-9): ";
				cin >> player_move;
			}
			Move(board, player_move-1);
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