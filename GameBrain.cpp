#include "GameSnakeHeader.h"

using namespace std;

void startSnakeGame()
{
	int bestScore(0);
	int sizeField(0);
	int difficult(0);

	std::ifstream in("res/best.score");
	if (in.is_open()) {
		in >> bestScore; // read the best score from file
	}
	in.close();

	while (true) {
		startingWindwow(bestScore, sizeField, difficult);

		Field field(sizeField + 2);

		system("pause >> NUL");
		system("cls");
		field.show();
		field.generateFood();

		do { // loop for one game
			Sleep(800 / difficult);
		} while (field.moveSnake());

		finishWindwow(field.snakeLength() - 3, (field.snakeLength() == sizeField * sizeField), bestScore);
	}
}