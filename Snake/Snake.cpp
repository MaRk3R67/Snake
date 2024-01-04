#include <iostream>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <time.h>

#define MAXSNAKESIZE 100

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

class Point {
private:
    int x;
    int y;

public:
    Point() {
        x = y = 10;
    }
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    void SetPoint(int x, int y) {
        this->x = x;
        this->y = y;
    }
    int GetX() {
        return x;
    }
    int GetY() {
        return y;
    }
    void MoveUp() {
        y--;
    }
    void MoveDown() {
        y++;
    }
    void MoveLeft() {
        x--;
    }
    void MoveRight() {
        x++;
    }
    void Draw(char symbol) {
        gotoxy(x, y);
        cout << symbol;
    }
    void Erase() {
        gotoxy(x, y);
        cout << " ";
    }
    void CopyPos(Point* p) {
        p->x = x;
        p->y = y;
    }
    void Debug() {
        cout << "(" << x << "," << y << ") ";
    }
};

class Snake {
private:
    Point* cell[MAXSNAKESIZE];
    int size;
    char dir;
    Point fruit;

public:
    Snake() {
        size = 1;
        cell[0] = new Point(20, 20);
        for (int i = 1; i < MAXSNAKESIZE; i++) {
            cell[i] = NULL;
        }
        fruit.SetPoint(rand() % 50, rand() % 25);
    }
    void AddCell(int x, int y) {
        cell[size++] = new Point(x, y);
    }
    void TurnUp() {
        if (dir != 's')
            dir = 'w';
    }
    void TurnDown() {
        if (dir != 'w')
            dir = 's';
    }
    void TurnLeft() {
        if (dir != 'd')
            dir = 'a';
    }
    void TurnRight() {
        if (dir != 'a')
            dir = 'd';
    }
    void Move() {
        system("cls");

        for (int i = 1; i < size; i++) {
            if (cell[0]->GetX() == cell[i]->GetX() && cell[0]->GetY() == cell[i]->GetY()) {
                cout << "Game Over! Collision with self.\n";
                exit(0);
            }
        }

        for (int i = size - 1; i > 0; i--) {
            cell[i - 1]->CopyPos(cell[i]);
        }

        switch (dir) {
        case 'w':
            cell[0]->MoveUp();
            break;
        case 's':
            cell[0]->MoveDown();
            break;
        case 'a':
            cell[0]->MoveLeft();
            break;
        case 'd':
            cell[0]->MoveRight();
            break;
        }

        if (fruit.GetX() == cell[0]->GetX() && fruit.GetY() == cell[0]->GetY()) {
            AddCell(0, 0);
            fruit.SetPoint(rand() % 50, rand() % 25);
        }

        for (int i = 0; i < size; i++) {
            if (i == 0)
                cell[i]->Draw('O');
            else
                cell[i]->Draw('o');
        }

        fruit.Draw('*');
        Sleep(100);

        if (IsGameWon()) {
            cout << "Congratulations! You've won the game!\n";
            exit(0);
        }
    }

    bool IsGameWon() {
        return size == MAXSNAKESIZE;
    }

    void Debug() {
        for (int i = 0; i < size; i++) {
            cell[i]->Debug();
        }
    }
};

int main() {
    srand((unsigned)time(NULL));

    Snake snake;
    char op = 'l';
    do {
        if (_kbhit()) {
            op = _getch();
        }
        switch (op) {
        case 'w':
        case 'W':
            snake.TurnUp();
            break;

        case 's':
        case 'S':
            snake.TurnDown();
            break;

        case 'a':
        case 'A':
            snake.TurnLeft();
            break;

        case 'd':
        case 'D':
            snake.TurnRight();
            break;
        }
        snake.Move();
    } while (op != 'e');

    return 0;
}
