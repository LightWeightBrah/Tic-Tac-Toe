#pragma once

enum Turn;
void SetPosition(int& position, char data[9], Turn& turn, char& letter);
void InvalidPositionDraw(char  data[9], int& position);
bool InRange(const int lowest, const int highest, const int& numberToCheck);
void DrawMap(char data[9]);
void Win(char letter, Turn& turn, std::string winType);
void CheckForWinner(char data[9], char letter, Turn& turn);
void InitData(char  data[9]);
void PlayAgain(Turn& turn, char  data[9]);

