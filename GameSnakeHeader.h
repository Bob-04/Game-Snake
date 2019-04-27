// GameSnakeHeader.h

#include <windows.h>
#include <ctime>
#include <cassert>
#include <fstream>
#include "Snake.h"

void setCursorPosition(const int x, const int y, const int color = 10);
void redrawSymbolAt(const size_t x, const size_t y, const char ch);
void clearLine(const size_t y);

void startSnakeGame(void);
void startingWindwow(const int bestScore, int& sizeField, int& difficult);
void finishWindwow(const int score, const bool isWin, int& bestScore);

class Field {
private:
	size_t _size;
	char** _allocator;
	Snake* _snake;

public:
	Field(const size_t size)
		: _size(size), _allocator(new char*[size]), _snake(new Snake()) {
		for (size_t i = 0; i < size; i++)
			_allocator[i] = new char[size];

		// fill space
		for (size_t i = 1; i < size - 1; i++)
			for (size_t j = 1; j < size - 1; j++)
				_allocator[i][j] = ' ';

		// fill border
		for (size_t i = 0; i < size; i++) {
			_allocator[0][i] = '#';
			_allocator[size - 1][i] = '#';
			_allocator[i][0] = '#';
			_allocator[i][size - 1] = '#';
		}

		// fill snake
		auto iter = _snake->getStart();
		for (size_t i = 0; i < snakeLength(); i++, iter++)
			_allocator[iter->second][iter->first] = '@';
	}
	~Field() {
		for (size_t i = 0; i < size(); i++)
			delete[] _allocator[i];
		delete[] _allocator;
	}

	inline const size_t size() const {
		return _size;
	}
	inline const size_t snakeLength() const {
		return _snake->length();
	}

	void generateFood() const {
		srand(static_cast<unsigned int>(time(NULL)));

		size_t foodX(0);
		size_t foodY(0);
		do {
			foodX = 1 + rand() % (size() - 2);
			assert(foodX >= 1 && foodX < size() - 1);
			foodY = 1 + rand() % (size() - 2);
			assert(foodY >= 1 && foodY < size() - 1);
		} while (_allocator[foodX][foodY] != ' ');

		_allocator[foodX][foodY] = '*';
		redrawSymbolAt(foodX, foodY, '*');
	}

	bool moveSnake() {
		_snake->chooseWay();

		size_t headX = _snake->headX();
		size_t headY = _snake->headY();

		// hit into wall or body
		if ((*this)(headX, headY) == '#' || (*this)(headX, headY) == '@')
			return false;

		if ((*this)(headX, headY) == '*') { // snake eat
			_snake->eat();
			if (snakeLength() == pow(size() - 2, 2))
				return false;
			generateFood();
		}
		else { // snake did not eat
			size_t tailX = _snake->tailX();
			size_t tailY = _snake->tailY();
			_allocator[tailX][tailY] = ' ';
			redrawSymbolAt(tailX, tailY, ' ');
			_snake->move();
		}
		_allocator[headX][headY] = '@';
		redrawSymbolAt(headX, headY, '@');
		return true;
	}

	inline const char& operator()(size_t x, size_t y) const {
		assert(x < size() && y < size());
		return _allocator[x][y];
	}

	void show() const {
		setCursorPosition(0, 0);
		for (size_t y = 0; y < size(); y++) {
			for (size_t x = 0; x < size(); x++)
				std::cout << _allocator[x][y];
			std::cout << std::endl;
		}
	}
};