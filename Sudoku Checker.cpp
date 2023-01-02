#include <iostream>
#include <fstream>
#include <vector>
#include <string>

bool checkSudokuSolution(std::vector<std::vector<int>> sudoku)
{
	//size of sudoku
	int size = 9;
	//creating a vector to remember seen numbers
	std::vector<bool> checked(size);
	//check column
	for (int j = 0; j < size; j++)
	{
		checked.assign(size, false);
		for (int i = 0; i < size; i++)
		{
			//if this number exist in column
			if (sudoku[i][j] - 1 == -1 || checked[sudoku[i][j] - 1])
				return false;
			checked[sudoku[i][j] - 1] = true;
		}
	}
	//check row
	for (int i = 0; i < size; i++)
	{
		checked.assign(size, false);
		for (int j = 0; j < size; j++)
		{
			//if this number exist in row
			if (sudoku[i][j] - 1 == -1 || checked[sudoku[i][j] - 1])
				return false;
			checked[sudoku[i][j] - 1] = true;
		}
	}
	//check boxes
	for (int x = 0; x < size; x += 3)
	{
		for (int y = 0; y < size; y += 3)
		{
			checked.assign(size, false);
			for (int i = x; i < x + 3; i++)
			{
				for (int j = y; j < y + 3; j++)
				{
					//if this number exist in column
					if (sudoku[i][j] - 1 == -1 || checked[sudoku[i][j] - 1])
						return false;
					checked[sudoku[i][j] - 1] = true;
				}
			}
		}
	}
	return true;
}

bool readFromFile(std::string fileName, std::vector<std::vector<int>>& sudoku)
{
	//initiate variables
	std::ifstream sudokuFile(fileName);
	int countInLine = 0;
	std::string line;
	//check if file exist
	if (!sudokuFile.is_open())
	{
		return false;
	}
	//while can read line from file 
	while (std::getline(sudokuFile, line))
	{
		std::vector<int> temp;
		for (char c : line)
		{
			//check if c is a digit and in correct spot in the line.
			if (!std::isdigit(c) && c != 32 && countInLine % 2 == 0 || (!std::isdigit(c) && countInLine % 2 != 0))
			{
				return false;
			}
			//ignore if c is space
			if (c != 32)
			{
				temp.emplace_back(c - '0');
			}
		}
		countInLine = 0;
		//check if size from this line is correct
		if (temp.size() != 9)
		{
			return false;
		}
		sudoku.emplace_back(temp);
		//check if file have too many lines from
		if (sudoku.size() > 9)
			return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		std::vector<std::vector<int>> sudoku;
		std::string file = argv[1];
		if (!readFromFile(argv[1], sudoku))
		{
			std::cout << "ERROR" << std::endl;
			return 1;
		}
		if (checkSudokuSolution(sudoku))
			std::cout << "CORRECT" << std::endl;
		else
			std::cout << "WRONG" << std::endl;
	}
	else
		std::cout << "ERROR" << std::endl;
	return 1;
}
