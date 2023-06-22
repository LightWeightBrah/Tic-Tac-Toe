#include <iostream>
#include <string>
#include <windows.h>
#include "TicTacToe.h"

enum Turn
{
	TurnX,
	TurnO,
	TurnGameEnd
};

const std::string border = "-------------\n";
const int asciiNumbersIndex = 49;
const char xLetter = 'X';
const char oLetter = 'O';
const int xColor = 12;
const int oColor = 9;
const int defaultColor = 15;
const int winColor = 10;
const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);


int main()
{
	int position;
	Turn turn = TurnX;
	char data[9];
	InitData(data);
	DrawMap(data);

	while (turn != TurnGameEnd)
	{
		char letter = turn == TurnX ? xLetter : oLetter;
		std::cout << "\nIt's " << letter << " turn! Type position (1 - 9)\n";
		SetPosition(position, data, turn, letter);
		CheckForWinner(data, letter, turn);
		PlayAgain(turn, data);
	}

}

void PlayAgain(Turn& turn, char  data[9])
{
	if (turn == TurnGameEnd)
	{
		SetConsoleTextAttribute(handle, defaultColor);

		std::cout << "Do you want to play again? (Type y if you do)\n";
		char decision;
		std::cin >> decision;
		if (decision == 'y' || decision == 'Y')
		{
			InitData(data);
			turn = TurnX;
			DrawMap(data);
		}
	}
}

void InitData(char data[9])
{
	for (int i = 0; i < 9; i++)
		data[i] = asciiNumbersIndex + i;
}

void CheckForWinner(char data[9], char letter, Turn& turn)
{
	for (int i = 0; i < 3; i++)
	{
		if (data[i * 3] == data[i * 3 + 1] && data[i * 3 + 1] == data[i * 3 + 2])
			Win(letter, turn, "ROW");
		else if (data[i] == data[3 + i] && data[3 + i] == data[3 + i + 3])
			Win(letter, turn, "COLLUMN");
	}

	if (data[0] == data[4] && data[4] == data[8])
		Win(letter, turn, "DIAGONAL");
	else if (data[2] == data[4] && data[4] == data[6])
		Win(letter, turn, "DIAGONAL");

	for (int i = 0; i < 3*3; i++)
	{
		if (data[i] != xLetter && data[i] != oLetter)
			return;
	}

	std::cout << "NO WINNERS THIS TIME\n";
	turn = TurnGameEnd;
	PlayAgain(turn, data);
}

void Win(char letter, Turn& turn, std::string winType)
{
	int winnerColor = letter == xLetter ? xColor : oColor;

	SetConsoleTextAttribute(handle, winColor);
	std::cout << "WINNER IS ";
	SetConsoleTextAttribute(handle, winnerColor);
	std::cout << letter;
	SetConsoleTextAttribute(handle, winColor);
	std::cout << " WON BY ";
	SetConsoleTextAttribute(handle, winnerColor);
	std::cout << winType << "\n";

	turn = TurnGameEnd;
}

void SetPosition(int& position, char data[9], Turn& turn, char& letter)
{
	position = -1;

	while (!InRange(1, 9, position))
	{
		std::cin >> position;

		if (!InRange(1, 9, position))
			InvalidPositionDraw(data, position);
	}

	if (data[position - 1] != xLetter && data[position - 1] != oLetter)
	{
		data[position - 1] = letter;
		turn = turn == TurnX ? TurnO : TurnX;
		DrawMap(data);
	}
	else
	{
		InvalidPositionDraw(data, position);
		SetPosition(position, data, turn, letter);
	}
}

void InvalidPositionDraw(char  data[9], int& position)
{
	DrawMap(data);
	std::cout << "\n" << position << " is invalid position! Try again.\n";
}

bool InRange(const int lowest, const int highest, const int& numberToCheck)
{
	return (numberToCheck >= lowest && numberToCheck <= highest);
}

void DrawMap(char data[9])
{
	system("cls");

	for (int y = 0; y < 3; y++)
	{
		std::cout << border;
		std::cout << "| ";
		for (int x = 0; x < 3; x++)
		{
			int index = y * 3 + x;
			if (data[index] == xLetter)
			{
				SetConsoleTextAttribute(handle, xColor);
			}
			else if (data[index] == oLetter)
			{
				SetConsoleTextAttribute(handle, oColor);
			}
			else
				SetConsoleTextAttribute(handle, defaultColor);

			std::cout << data[index];
			SetConsoleTextAttribute(handle, defaultColor);
			std::cout << " | ";
		}
		std::cout << "\n";
	}
	std::cout << border;
}
