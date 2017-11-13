#include<iostream>
#include <queue>

typedef std::pair<int, int> Position;
const int MAX_ROWS = 5;
const int MAX_COLUMNS = 5;

int Labirynth[MAX_ROWS][MAX_COLUMNS] =
{
	{ 1,-1,-1,-1,-1},
	{ 1, 1,-1,-1,-1},
	{-1, 1, 1, 1,-1},
	{-1,-1,-1, 1,-1},
	{ 2, 1, 1, 1, 1}
};

bool CanWeStepThere(const int row, const int column)
{
	return row > -1 && column > -1
		&& row < MAX_ROWS && column < MAX_COLUMNS
		&& Labirynth[row][column] != -1
		&& Labirynth[row][column] != 0;
}
bool OneStepAhead(const int row, const int column, std::queue<Position>& Wave)
{
	if (CanWeStepThere(row, column))
	{
		Wave.push(Position(row, column));
		return true;
	}
	return false;
}
int BFS(int CurrentRow, int CurrentCol)
{
	if (!CanWeStepThere(CurrentRow, CurrentCol))
	{
		return -1;
	}
	std::queue<Position> Wave;
	Wave.push(Position(CurrentRow, CurrentCol));
	int sum = 0;
	while (!Wave.empty())
	{
		CurrentRow = std::get<0>(Wave.front());
		CurrentCol = std::get<1>(Wave.front());
		if (Labirynth[CurrentRow][CurrentCol] == 1)
		{
			Labirynth[CurrentRow][CurrentCol] = 0;
		}
		Wave.pop();
		if (Labirynth[CurrentRow][CurrentCol] == 2)
		{
			return sum;
		}
		bool Right = OneStepAhead(CurrentRow, CurrentCol + 1, Wave);
		bool Left = OneStepAhead(CurrentRow, CurrentCol - 1, Wave);
		bool Up = OneStepAhead(CurrentRow + 1, CurrentCol, Wave);
		bool Down = OneStepAhead(CurrentRow - 1, CurrentCol, Wave);
		if (Right || Left || Up || Down)
		{
			sum++;
		}
	}
	return -1;
}
int main()
{
	std::cout << BFS(0, 0) << std::endl;
	return 0;
}