#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool gameOver;
const int width = 20, height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw() {
	//clear screen
	system("cls");//system("clear"); //for linux
	//top map
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
	//body map
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//wall left right
			if (j == 0)
				cout << "#";
			else if (j == width - 1)
				cout << "#";

			//snak position
			else if (i == y && j == x)
				cout << "O";
			//fruit position
			else if (i == fruitY && j == fruitX)
				cout << "%";
			//spaces
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if (!print) {
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	//bottom map
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
	//print score
	cout << "score: " << score;
}
void Input() {
	//which key is pressed
	if (_kbhit()) {
		switch (_getch()) {
		case 'a': dir = LEFT;
			break;
		case 'd': dir = RIGHT;
			break;
		case 'w': dir = UP;
			break;
		case 's': dir = DOWN;
			break;
		case 'x': gameOver = true;
			break;
		}
	}
}
void Logic() {
	//tail move 
	int prevX = tailX[0];
	int prevY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	int prev2X, prev2Y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	//snake movement based on the key pressed
	switch (dir)
	{
	case LEFT: x--;
		break;
	case RIGHT: x++;
		break;
	case UP: y--;
		break;
	case DOWN: y++;
		break;
	default:
		break;
	}
	//when is game over?
	if (x >= width || x < 0 || y < 0 || y >= height)
		gameOver = true;
	//eat fruit = score up & snake tail grow
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		//tail grows
		nTail++;
	}
	//hit our tail = game over
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}
}

int main()
{
	Setup();

	while (!gameOver) {
		Sleep(100);
		Draw();
		Input();
		Logic();
	}
	getchar();
}