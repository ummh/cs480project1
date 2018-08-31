#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
int board[9][9];
struct boardMove//an object used to store individual moves
{
	int locationC;
	int locationR;
	int move;



	boardMove()
	{
		locationC = 0;
		locationR = 0;
		move = 0;
	}

};

//visually shows the board
void printBoard(int b[][9])
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			cout << " " << b[i][j];
		}
		cout << endl;
	}
}



//generates all possible moves given the square to check
vector<boardMove> possibleMoves(int cboard[9][9], int c, int r)
{
	vector<boardMove> moveList;
	vector<int> moves{ 1,2,3,4,5,6,7,8,9 };
	//find out what cell block the cell is in
	int cblock = c / 3;
	int rblock = r / 3;

	cblock = cblock * 3 + 1;
	rblock = rblock * 3 + 1;
	//collumn then row
	//top row
	if (find(moves.begin(), moves.end(), cboard[cblock - 1][rblock - 1]) != moves.end())
		moves[(cboard[cblock - 1][rblock - 1]) - 1] = -1;
	if (find(moves.begin(), moves.end(), cboard[cblock][rblock - 1]) != moves.end())
		moves[(cboard[cblock][rblock - 1]) - 1] = -1;
	if (find(moves.begin(), moves.end(), cboard[cblock + 1][rblock - 1]) != moves.end())
		moves[(cboard[cblock + 1][rblock - 1]) - 1] = -1;
	//mid row
	if (find(moves.begin(), moves.end(), cboard[cblock - 1][rblock]) != moves.end())
		moves[(cboard[cblock - 1][rblock]) - 1] = -1;
	if (find(moves.begin(), moves.end(), cboard[cblock][rblock]) != moves.end())
		moves[(cboard[cblock][rblock]) - 1] = -1;
	if (find(moves.begin(), moves.end(), cboard[cblock + 1][rblock]) != moves.end())
		moves[(cboard[cblock + 1][rblock]) - 1] = -1;
	//bottom row

	if (find(moves.begin(), moves.end(), cboard[cblock - 1][rblock + 1]) != moves.end())
		moves[(cboard[cblock - 1][rblock + 1]) - 1] = -1;
	if (find(moves.begin(), moves.end(), cboard[cblock][rblock + 1]) != moves.end())
		moves[(cboard[cblock][rblock + 1]) - 1] = -1;

	if (find(moves.begin(), moves.end(), cboard[cblock + 1][rblock + 1]) != moves.end())
		moves[(cboard[cblock + 1][rblock + 1]) - 1] = -1;


	//checks the current row
	for (int i = 0; i <9; i++)
	{
		if (find(moves.begin(), moves.end(), cboard[i][r]) != moves.end())
			moves[(cboard[i][r]) - 1] = -1;
	}
	//checks the current collumn
	for (int i = 0; i <9; i++)
	{
		if (find(moves.begin(), moves.end(), cboard[c][i]) != moves.end())
			moves[(cboard[c][i]) - 1] = -1;
	}
	for (int i = 0; i < moves.size(); i++) {
		if (moves[i] != -1)
		{
			boardMove b = boardMove();
			b.locationC = c;
			b.locationR = r;
			b.move = moves[i];
			moveList.push_back(b);
		}
	}

	return moveList;//returns list of move-objects
}
//checks if the board is currently solved
bool solved(int b[][9])
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (b[i][j] == 0)
				return false;
	cout << endl << "solution:" << endl;
	printBoard(b);
	return true;
}
//solve function for the board using a stack
bool solve(int b[][9], stack<boardMove> s)
{
	vector<boardMove> curMove;

	if (solved(b))
	{
		//printBS(b);
		return true;
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (b[i][j] == 0)
			{
				curMove = possibleMoves(b, i, j);
				break;
			}
		}
	}
	//cout << curMove.size() << endl;
	for (int k = 0; k < curMove.size(); k++)
	{
		int newBoard[9][9];
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				newBoard[i][j] = b[i][j];
		//cout << "board position" << newBoard[curMove[k].locationC][curMove[k].locationR] << endl;
		newBoard[curMove[k].locationC][curMove[k].locationR] = curMove[k].move;
		//cout << "board position after" << newBoard[curMove[k].locationC][curMove[k].locationR] << endl;
		if (solve(newBoard, s))
		{
			s.push(curMove[k]);
			return true;
		}
	}
	return false;
}
//reads in the input file to get the board
void readFile(string filen)
{
	ifstream mfile;
	mfile.open(filen);
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			mfile >> board[i][j];
		}
	}

}
//main function
int main() {
	cout << "Insert name of file" << endl;
	string file;
	cin >> file;
	readFile(file);
	int masterBoard[9][9];
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			masterBoard[i][j] = board[i][j];
		}
	}
	cout << "Input Board:" << endl;
	printBoard(masterBoard);
	stack<boardMove> bMove;
	vector<boardMove> pmoves = possibleMoves(masterBoard, 0, 0);
	if (solve(masterBoard, bMove))
		cout << "solved" << endl;
	else
		cout << "No Solution" << endl;
}
