#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <random>
#include <ctime>

using namespace std;

struct Coor{
    int x;
    int y;
    Coor(int xx = 0, int yy = 0) { x = xx; y = yy; }
};

class Snake {
    int len;
    Coor loc[100];  //MAXSIZE
    char direction;

public:
    friend class Food;

    Snake() {
        len = 3;
        int initx = 150;
        int inity = 150;
        for (int i = 0; i < len; ++i) {
            loc[i].x = initx;
            loc[i].y = inity;
            initx += 10;
        }
        direction = 'a';
    }

    void show() {
        for (int i = 1; i < len; ++i)
            rectangle(loc[i].x, loc[i].y, loc[i].x + 10, loc[i].y + 10);
        setfillcolor(RGB(150, 150, 150));
        fillrectangle(loc[0].x, loc[0].y, loc[0].x + 10, loc[0].y + 10);
    }

    void change() {
        char tmp = _getch();
        switch (tmp) {
        case 'a': if (direction != 'd') { direction = 'a'; } break;
        case 'w': if (direction != 's') { direction = 'w'; } break;
        case 'd': if (direction != 'a') { direction = 'd'; } break;
        case 's': if (direction != 'w') { direction = 's'; } break;
        }
    }

    void move() {
        bodymove();
        switch (direction) {
        case 'a': loc[0].x -= 10; break;
        case 'w': loc[0].y -= 10; break;
        case 'd': loc[0].x += 10; break;
        case 's': loc[0].y += 10; break;
        }
    }

    void bodymove() {
        for (int i = len - 1; i != 0; --i) {
            loc[i].x = loc[i - 1].x;
            loc[i].y = loc[i - 1].y;
        }
    }

    void lengthen(int xx, int yy) {
        ++len;
        bodymove();
        loc[0].x = xx;
        loc[0].y = yy;

        switch (direction) {
        case 'a': loc[0].x -= 10; break;
        case 'w': loc[0].y -= 10; break;
        case 'd': loc[0].x += 10; break;
        case 's': loc[0].y += 10; break;
        }
    }

    bool over() {
        if (loc[0].x < 0 || loc[0].x >= 320 || loc[0].y < 0 || loc[0].y >= 320) return true;
        for (int i = 1; i < len; ++i) {
            if (loc[0].x == loc[i].x && loc[0].y == loc[i].y) return true;
        }
        return false;
    }
};

class Food {
    Coor loc;
    bool iseated = true;

public:
    void CreateFood(Snake& snake) {
        if (snake.loc[0].x == loc.x && snake.loc[0].y == loc.y) {
            iseated = true;
            snake.lengthen(loc.x, loc.y);
        }
        if (iseated == false) return;
        bool flag = true;
        while (flag) {
            flag = false;
            loc.x = rand() % 32 * 10;
            loc.y = rand() % 32 * 10;
            for (int i = 0; i < snake.len; ++i)
                if (loc.x == snake.loc[i].x && loc.y == snake.loc[i].y) flag = true;
        }
        iseated = false;
    }

    void show() {
        setfillcolor(RGB(150, 150, 150));
        fillcircle(loc.x + 5, loc.y + 5, 5);
    }
};

class Game {
    Snake snake;
    Food food;

public:
    void GameStart() {
        cout << "欢迎来到贪吃蛇游戏！\n游戏规则：\nA:<-\tW:^\tD:->\tS:v\n按两次回车键开始";
        cin.get();
    }
    void Playing() {
        srand(time(NULL));
        initgraph(320, 320);
        bool flag = true;
        while (flag) {
            while (!_kbhit()) {
                cleardevice();
                food.CreateFood(snake);
                food.show();
                snake.move();
                snake.show();
                if (snake.over()) {
                    flag = false;
                    break;
                }
                Sleep(150);
            }
            snake.change();
        }
        cout << "GameOver" << endl;
        closegraph();
    }

    bool replay() {
        cleardevice();
        cout << "再来一次请按'y'，结束按其他键" << endl;
        char tmp = _getch();
        if (tmp == 'y') {
            snake = Snake();
            food = Food();
            return true;
        }
        else return false;

    }
};

int main() {
    Game game;
    game.GameStart();
    game.Playing();
    while (game.replay()) {
        game.Playing();
    }
    return 0;
}
