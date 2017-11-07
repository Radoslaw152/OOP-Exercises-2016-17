#include <iostream>
#include <queue>
const int MAX_ROWS = 5;
const int MAX_COLUMNS = 5;
/*

A bool function, which returns
if we can step on this place or not.

*/
bool CanIgoThere(char Matrix[MAX_ROWS][MAX_COLUMNS], int NextRow, int NextCol)
{
	return NextRow > -1 && NextRow < MAX_ROWS && NextCol > -1 //if we are inside the labyrinth
		&& NextCol < MAX_COLUMNS && Matrix[NextRow][NextCol] != '3' //if we have been there
		&& Matrix[NextRow][NextCol] != '2'; //if it is a wall
}
/*

StepForwards return:
0 - can't go there
1 - we can go there, but we haven't found the treasure
2 - we found the treasure

*/
int StepForward(std::queue<std::pair<int,int>>& queue,int currentRow, 
	int currentCol, char Matrix[MAX_ROWS][MAX_ROWS])
{
	if (CanIgoThere(Matrix, currentRow, currentCol))
	{
		if (Matrix[currentRow][currentCol] == '*')
		{
			return 2;
		}
		Matrix[currentRow][currentCol] = '3';
		queue.push(std::pair<int, int>(currentRow, currentCol));
		return 1;
	}
	return 0;
}
/*

This function is my implementation of Breadth-First Search.
It returns:
-1, if there isn't a way from the given position
sum, if there is a way and sum is the shortest way to it

*/
int BFS(int CurrentRow, int CurrentCol, char Matrix[MAX_ROWS][MAX_COLUMNS])
{
	if (!CanIgoThere(Matrix, CurrentRow, CurrentCol)) //Checks if we are on wall
	{
		return -1;
	}
	std::queue<std::pair<int, int>> wave;
	wave.push(std::pair<int, int>(CurrentRow, CurrentCol));
	int sum = 0;
	bool haveWeFoundIt = false;
	while (!wave.empty())
	{
		CurrentRow = std::get<0>(wave.front());
		CurrentCol = std::get<1>(wave.front());
		wave.pop();
		int Right = StepForward(wave, CurrentRow, CurrentCol + 1, Matrix);
		int Left = StepForward(wave, CurrentRow, CurrentCol - 1, Matrix);
		int Up = StepForward(wave, CurrentRow - 1, CurrentCol, Matrix);
		int Down = StepForward(wave, CurrentRow + 1, CurrentCol, Matrix);
		if (Up || Down || Left || Right)
		{
			sum++;
		}
		if (Up == 2 || Down == 2 || Left == 2 || Right == 2)
		{	//Checks if we have found the treasure
			return sum;
		}
	}
	return -1;
}
int main()
{
	/*

	A labirynth presented in 2D char array / matrix,
	as it says:
	1 - a normal place to be
	2 - a wall
	3 - a place, which we have been before

	*/
	char Labyrinth[MAX_ROWS][MAX_COLUMNS] = 
	{
		{ '1','2','*','1','1' },
		{ '1','2','2','2','1' },
		{ '1','1','1','2','1' },
		{ '1','1','1','2','1' },
		{ '2','2','1','1','1' }
	};
	std::cout << BFS(0,0,Labyrinth);
	return 0;
}