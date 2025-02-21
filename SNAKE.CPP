#include <iostream.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>
int gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail = 0;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    gameOver = 0;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    clrscr();

    for (int k = 0; k < width; k++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
	for (int j = 0; j < width; j++) {
	    if (j == 0) cout << "#";
	    else if (i == y && j == x) cout << "O";
	    else if (i == fruitY && j == fruitX) cout << "F";
	    else {
		int print = 0;
		for (int d = 0; d < nTail; d++) {
		    if (tailX[d] == j && tailY[d] == i) {
			cout << "o";
			print = 1;
		    }
		}
		if (!print) cout << " ";
	    }
	    if (j == width - 1) cout << "#";
	}
	cout << endl;
    }

    for (int l = 0; l < width; l++) cout << "#";
    cout << endl << endl;
    cout << "Your Score: " << score;
}
void Input() {
    if (kbhit()) {
	switch (getch()) {
	    case 'a': dir = LEFT; break;
	    case 'd': dir = RIGHT; break;
	    case 'w': dir = UP; break;
	    case 's': dir = DOWN; break;
	    case 'x': gameOver = 1; break;
	}
    }
}
void Logic() {

    for (int i = nTail - 1; i > 0; i--) {
	tailX[i] = tailX[i - 1];
	tailY[i] = tailY[i - 1];
    }
    tailX[0] = x;
    tailY[0] = y;

    switch (dir) {
	case LEFT: x--; break;
	case RIGHT: x++; break;
	case UP: y--; break;
	case DOWN: y++; break;
    }
    if (x >= width) x = 0;
    else if (x < 0) x = width - 1;
    if (y >= height) y = 0;
    else if (y < 0) y = height - 1;

    for (int t = 0; t < nTail; t++) {
	if (tailX[t] == x && tailY[t] == y) {
	    gameOver = 1;
	}
    }
    if (x == fruitX && y == fruitY) {
	score += 10;
	fruitX = rand() % width;
	fruitY = rand() % height;
	nTail++;
    }
}

void gameOverScreen() {
    clrscr();
    int midX = 37;
    int midY = 12;

    gotoxy(midX, midY);
    cout << "GAME OVER";

    gotoxy(midX - 7, midY + 2);
    cout << "Press any key to exit...";

    getch();
}

int main() {
    Setup();
    while (gameOver == 0) {
	Draw();
	Input();
	Logic();
	delay(100);
    }
    gameOverScreen();
    return 0;
}
