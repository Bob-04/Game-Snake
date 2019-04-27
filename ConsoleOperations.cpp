#include "GameSnakeHeader.h"

// Colors:
//Black = 0,
//Blue = 1,
//Green = 2,
//Cyan = 3,
//Red = 4,
//Magenta = 5,
//Brown = 6,
//LightGray = 7,
//DarkGray = 8,
//LightBlue = 9,
//LightGreen = 10,
//LightCyan = 11,
//LightRed = 12,
//LightMagenta = 13,
//Yellow = 14,
//White = 15
void setCursorPosition(const int x, const int y, const int color)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, color);
	std::cout.flush();
	SetConsoleCursorPosition(hOut, { (SHORT)x, (SHORT)y });
}

void redrawSymbolAt(const size_t x, const size_t y, const char ch)
{
	setCursorPosition(x, y);
	std::cout << ch;
}

void clearLine(const size_t y)
{
	for (int x = 0; x < 20; x++) {
		setCursorPosition(x * 10, y);
		std::cout << "          ";
	}
}