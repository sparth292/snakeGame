#include<iostream.h>
#include<conio.h>
#include<stdlib.h>

int gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;

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
    clrscr(); // Clear screen

    for (int i = 0; i < width; i++) {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) {
                cout << "#";
            } else if (i == y && j == x) {
                cout << "O"; // Snake head
            } else if (i == fruitY && j == fruitX) {
                cout << "F"; // Fruit
            } else {
                cout << " ";
            }

            if (j == width - 1) {
                cout << "#";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width; i++) {
        cout << "#";
    }
    cout << endl;
}

void Input() {
    if (kbhit()) { // Check if a key is pressed
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

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

void main() { // Use 'void main()' in Turbo C++
    Setup();
    while (gameOver == 0) {
        Draw();
        Input();
        Logic();
        delay(100); // Slow down the loop
    }
    getch(); // Wait for a key press before closing
}
