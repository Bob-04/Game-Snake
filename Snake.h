// Snake.h

#include <deque>
#include <iostream>
#include <conio.h>

class Snake {
private:
	size_t _length;
	short _way;
	std::deque< std::pair<size_t, size_t> >* _body;

	void changeWay() {
		if (_kbhit()) { // 72-up, 80-down, 75-left, 77-right
			_getch();
			const short ch = _getch();

			// if the button does not fit
			if (ch != 72 && ch != 75 && ch != 77 && ch != 80)
				return;

			// snake can't turn around
			if (!(_way == 72 && ch == 80) && !(_way == 80 && ch == 72) &&
				!(_way == 75 && ch == 77) && !(_way == 77 && ch == 75)) {
				_way = ch;
			}
		}
	}

public:
	Snake(size_t length = 3)
		: _length(length), _way(77), _body(new std::deque< std::pair<size_t, size_t> >) {
		for (size_t x = 1; x <= length; x++)
			_body->emplace_back(std::make_pair(1, x));
	}
	~Snake() {
		delete _body;
		_body = nullptr;
	}

	inline size_t length() {
		return _length;
	}

	void chooseWay() {
		changeWay();
		size_t headY = _body->back().first;
		size_t headX = _body->back().second;

		switch (_way) {
		case 72: // up
			_body->emplace_back(std::make_pair(headY - 1, headX));
			break;
		case 80: // down
			_body->emplace_back(std::make_pair(headY + 1, headX));
			break;
		case 75: // left
			_body->emplace_back(std::make_pair(headY, headX - 1));
			break;
		case 77: // right
			_body->emplace_back(std::make_pair(headY, headX + 1));
			break;
		}
	}

	const inline size_t headX() const { return _body->back().second; }
	const inline size_t headY() const { return _body->back().first; }
	const inline size_t tailX() const { return _body->front().second; }
	const inline size_t tailY() const { return _body->front().first; }

	inline void eat() {
		_length++;
	}
	inline void move() {
		_body->pop_front();
	}

	inline std::deque< std::pair<size_t, size_t> >::iterator getStart() {
		return _body->begin();
	}
};