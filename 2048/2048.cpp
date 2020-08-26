#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

struct Cood{
    int x;
    int y;
    Cood(int xx = 0, int yy = 0) :x(xx), y(yy) {};
};

class Game {
    int arr[4][4];

public:
    void gameInit() {
        srand(time(NULL));
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                arr[i][j] = 0;
            }
        }
        printf("欢迎来到2048小游戏！\n");
    }

    void play() {
        while (replay()) {
            gameInit();
            while (randgen()) {
                show();
                operate();
            }
        }
    }

    void show() {
        system("cls");
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                    printf("%d\t", arr[i][j]);
            }
            printf("\n");
        }
        printf("使用awds控制方向：");
    }

    bool randgen() {
        vector<Cood> v;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (arr[i][j] == 0) v.push_back(Cood(i, j));
            }
        }
        if (v.empty()) return false;
        int tmp = rand() % v.size();
        int num = (rand() % 2) * 2 + 2;
        arr[v[tmp].x][v[tmp].y] = num;
        return true;
    }

    void operate() {
        char dir = cin.get();
        cin.get();
        switch (dir) {
        case 'a': {
            for (int i = 0; i < 4; ++i) {
                int* a = new int[4];
                for (int j = 0; j < 4; ++j) {
                    a[j] = arr[i][j];
                }
                line(a);
                for (int j = 0; j < 4; ++j) {
                    arr[i][j] = a[j];
                }
            }
            break; 
        }

        case 'd': {
            for (int i = 0; i < 4; ++i) {
                int* a = new int[4];
                for (int j = 0; j < 4; ++j) {
                    a[j] = arr[i][3 - j];
                }
                line(a);
                for (int j = 0; j < 4; ++j) {
                    arr[i][3 - j] = a[j];
                }
            }
            break;
        }

        case 's': {
            for (int i = 0; i < 4; ++i) {
                int* a = new int[4];
                for (int j = 0; j < 4; ++j) {
                    a[j] = arr[3 - j][i];
                }
                line(a);
                for (int j = 0; j < 4; ++j) {
                    arr[3 - j][i] = a[j];
                }
            }
            break;
        }

        case 'w': {
            for (int i = 0; i < 4; ++i) {
                int* a = new int[4];
                for (int j = 0; j < 4; ++j) {
                    a[j] = arr[j][i];
                }
                line(a);
                for (int j = 0; j < 4; ++j) {
                    arr[j][i] = a[j];
                }
            }
            break;
        }
        }
    }

    void line(int* a) {
        move(a);
        for (int i = 0; i < 3; ++i) {
            if (a[i] == a[i + 1] && a[i] != 0) {
                a[i] *= 2;
                a[i + 1] = 0;
                ++i;
            }
        }
        move(a);
    }

    void move(int* a) {
        int p = 0;
        for (int i = 0; i < 4; ++i) {
            if (a[i] != 0) {
                a[p] = a[i];
                if(i != p) a[i] = 0;
                ++p;
            }
        }
    }

    bool replay() {
        static int i = 0;
        if (i == 0) {
            ++i;
            return true;
        }
        else {
            printf("不可再移动！再来一次请输入y：");
            char tmp = cin.get();
            cin.get();
            if (tmp == 'y') return true;
            else return false;
        }
    }
};

int main()
{
    Game game;
    game.play();
    return 0;
}