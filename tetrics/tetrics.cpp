#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <ctime>
using namespace std;

const int WIDTH = 14;
const int HEIGTH = 20;

struct cood {
	int x;
	int y;
	cood(int xx = 0, int yy = 0) :x(xx), y(yy) {};
};

class Tetris {
	cood type[4];
	int shape;
	int angle;
	bool iscreated = false;

public:
	friend class Game;
	void creatType() {
		if (iscreated == true) return;
		srand(time(NULL));
		int tmp = rand() % 5;
		switch (tmp) {
		case 0: {
			type[0].x = 5; type[0].y = 0;
			type[1].x = 6; type[1].y = 0;
			type[2].x = 7; type[2].y = 0;
			type[3].x = 8; type[3].y = 0;
		}break;

		case 1: {
			type[0].x = 6; type[0].y = 1;
			type[1].x = 5; type[1].y = 0;
			type[2].x = 6; type[2].y = 0;
			type[3].x = 7; type[3].y = 0;
		}break;

		case 2: {
			type[0].x = 5; type[0].y = 1;
			type[1].x = 6; type[1].y = 1;
			type[2].x = 6; type[2].y = 0;
			type[3].x = 7; type[3].y = 0;
		}break;

		case 3: {
			type[0].x = 6; type[0].y = 1;
			type[1].x = 7; type[1].y = 1;
			type[2].x = 7; type[2].y = 0;
			type[3].x = 6; type[3].y = 0;
		}break;

		case 4: {
			type[0].x = 5; type[0].y = 1;
			type[1].x = 5; type[1].y = 0;
			type[2].x = 6; type[2].y = 0;
			type[3].x = 7; type[3].y = 0;
		}break;
		}

		iscreated = true;
		shape = tmp;
		angle = 0;
	}

	void show() {
		for (int i = 0; i < 4; ++i) {
			setfillcolor(RGB(255, 255, 255));
			fillrectangle(type[i].x * 30, type[i].y * 30,
				          type[i].x * 30 + 30, type[i].y * 30 + 30);
		}
	}
};

class Game {
	int arr[HEIGTH][WIDTH];
	Tetris tetris;
public:
	void init() {
		for (int i = 0; i < WIDTH; ++i) {
			arr[HEIGTH - 1][i] = 1;
		}
		for (int i = 0; i < HEIGTH; ++i) {
			arr[i][WIDTH - 1] = 1;
			arr[i][0] = 1;
		}
		for (int i = 0; i < HEIGTH - 1; ++i) {
			for (int j = 1; j < WIDTH - 1; ++j) {
				arr[i][j] = 0;
			}
		}
	}

	void startGame() {
		cout << "欢迎来到俄罗斯方块小游戏" << endl
			<< "操作说明：\nA:<-\tD:->\tS:v\tW:rotate" << endl
			<< "按任意键继续...";
		char tmp = cin.get();
		init();
	}

	void vanish() {
		int i;
		int j;
		for (i = HEIGTH - 2; i > 0; --i) {
			for (j = 1; j < WIDTH - 1; ++j) {
				if (arr[i][j] == 0) break;
			}
			if (j == WIDTH - 1) {
				for (int p = i; p > 0; --p) {
					for (int q = 1; q < WIDTH - 1; ++q) {
						arr[p][q] = arr[p - 1][q];
					}
				}
			}
		}
	}

	void operate() {
		if (_kbhit()) {
			char tmp;
			while (_kbhit()) {
				tmp = _getch();
			}
			bool canMove = true;
			switch (tmp) {
			case'a': {
				for (int i = 0; i < 4; ++i) {
					if (arr[tetris.type[i].y][tetris.type[i].x - 1] == 1) {
						canMove = false;
						break;
					}
				}
				if (canMove) {
					for (int i = 0; i < 4; ++i) {
						--tetris.type[i].x;
					}
				}
			}break;

			case'd': {
				for (int i = 0; i < 4; ++i) {
					if (arr[tetris.type[i].y][tetris.type[i].x + 1] == 1) {
						canMove = false;
						break;
					}
				}
				if (canMove) {
					for (int i = 0; i < 4; ++i) {
						++tetris.type[i].x;
					}
				}
			}break;

			case's': {
				while (move()) {}
			}break;

			case'w': {
				rotate();
			}break;
			}
		}
	}

	void rotate() {
		switch (tetris.shape) {
		case 0: {
			if (tetris.angle == 0) {
				tetris.type[0] = tetris.type[1];
				tetris.type[1].y -= 1;
				tetris.type[2] = tetris.type[1]; tetris.type[2].y -= 1;
				tetris.type[3] = tetris.type[1]; tetris.type[3].y -= 2;
				tetris.angle = 90;
			}
			else {
				int l = tetris.type[0].x;
				int r = l;
				int y = tetris.type[1].y;
				int i;
				for (i = 1; i <= 4; ++i) {
					if (arr[y][l - i] == 1 || i == 4) {
						l = l - i + 1;
						break;
					}
				}
				for (i = 1; i <= 4; ++i) {
					if (arr[y][r + i] == 1 || i == 4) {
						r = r + i - 1;
						break;
					}
				}
				if (r - l < 3) return;

				for (int i = 0; i < 4; ++i) {
					tetris.type[i].x = l + i;
					tetris.type[i].y = y;
				}
				tetris.angle = 0;
			}
		}break;

		case 1: {
			switch (tetris.angle) {
			case 0: {
				++tetris.type[1].x; --tetris.type[1].y;
				tetris.angle = 90;
			}break;
			case 90: {
				if (arr[tetris.type[2].y][tetris.type[2].x - 1] != 1) {
					--tetris.type[0].x; --tetris.type[0].y;
					tetris.angle = 180;
				}
			}break;
			case 180: {
				if (arr[tetris.type[2].y + 1][tetris.type[2].x] != 1) {
					--tetris.type[3].x; ++tetris.type[3].y;
					tetris.angle = 270;
				}
			}break;
			case 270: {
				tetris.type[1] = tetris.type[0];
				tetris.type[0] = tetris.type[3];
				++tetris.type[3].x; --tetris.type[3].y;
				tetris.angle = 0;
			}break;
			}
		}break;

		case 2: {
			if (tetris.angle == 0) {
				if (arr[tetris.type[0].y - 1][tetris.type[0].x] != 1 &&
					arr[tetris.type[0].y - 2][tetris.type[0].x] != 1) {
					tetris.type[0].y -= 2;
					tetris.type[3].x -= 2;
					tetris.angle = 90;
				}
			}
			else {
				if (arr[tetris.type[0].y][tetris.type[0].x + 1] != 1 &&
					arr[tetris.type[0].y][tetris.type[0].x + 2] != 1) {
					++tetris.type[0].y;
					--tetris.type[1].y;
					--tetris.type[2].y;
					tetris.type[3].x += 2; --tetris.type[3].y;
					tetris.angle = 0;
				}
				else if (arr[tetris.type[0].y][tetris.type[0].x + 1] != 1 &&
					     arr[tetris.type[3].y][tetris.type[3].x - 1] != 1) {
					tetris.type[1] = tetris.type[3];
					tetris.type[2] = tetris.type[2];
					--tetris.type[0].x; ++tetris.type[0].y;
					++tetris.type[3].x; --tetris.type[3].y;
					tetris.angle = 0;
				}
			}
		}break;

		case 3: break;

		case 4: {
			switch (tetris.angle) {
			case 0: {
				if (arr[tetris.type[1].y - 1][tetris.type[1].x] != 1 &&
					arr[tetris.type[1].y - 2][tetris.type[1].x] != 1) {
					tetris.type[0] = tetris.type[2];
					--tetris.type[2].x;
					--tetris.type[2].y;
					tetris.type[3].x -= 2;
					tetris.type[3].y -= 2;
					tetris.angle = 90;
				}
			}break;
			case 90: {
				if (arr[tetris.type[2].y][tetris.type[2].x + 1] != 1 &&
					arr[tetris.type[2].y][tetris.type[2].x - 1] != 1 &&
					arr[tetris.type[3].y][tetris.type[3].x + 1] != 1) {
					tetris.type[0].y -= 2;
					++tetris.type[1].x; --tetris.type[1].y;
					--tetris.type[3].x; ++tetris.type[3].y;
					tetris.angle = 180;
				}
				else if (arr[tetris.type[2].y][tetris.type[2].x + 1] != 1 &&
					 	 arr[tetris.type[2].y][tetris.type[2].x + 2] != 1 &&
					 	 arr[tetris.type[2].y - 1][tetris.type[2].x + 2] != 1) {
						 tetris.type[3] = tetris.type[2];
						 ++tetris.type[2].x;
						 tetris.type[1] = tetris.type[2]; ++tetris.type[1].x;
						 tetris.type[0] = tetris.type[1]; --tetris.type[0].y;
						 tetris.angle = 180;
				}
			}break;
			case 180: {
				if (arr[tetris.type[1].y + 1][tetris.type[1].x] != 1 &&
					arr[tetris.type[0].y][tetris.type[0].x - 1] != 1) {
					++tetris.type[2].x;
					--tetris.type[1].y;
					--tetris.type[0].x;
					tetris.type[3] = tetris.type[2]; ++tetris.type[3].y;
					tetris.angle = 270;
				}
			}break;
			case 270: {
				if (arr[tetris.type[0].y - 1][tetris.type[0].x] != 1 &&
					arr[tetris.type[1].y][tetris.type[1].x + 1] != 1) {
					tetris.type[3] = tetris.type[1]; ++tetris.type[3].x;
					tetris.type[2] = tetris.type[1];
					tetris.type[1] = tetris.type[0];
					++tetris.type[0].y;
					tetris.angle = 0;
				}
				else if (arr[tetris.type[0].y][tetris.type[0].x - 1] != 1 &&
					     arr[tetris.type[2].y][tetris.type[2].x - 2] != 1) {
					tetris.type[3] = tetris.type[1];
					tetris.type[2] = tetris.type[0];
					tetris.type[1].x -= 2;
					tetris.type[0] = tetris.type[1]; ++tetris.type[0].y;
					tetris.angle = 0;
				}
			}break;
			}
		}break;
		}
	}

	void stop() {
		if (tetris.iscreated == false) {
			for (int i = 0; i < 4; ++i) {
				arr[tetris.type[i].y][tetris.type[i].x] = 1;
			}
		}
	}

	bool move() {
		bool canMove = true;
		for (int i = 0; i < 4; ++i) {
			if (arr[tetris.type[i].y + 1][tetris.type[i].x] == 1) {
				canMove = false;
				tetris.iscreated = false;
				break;
			}
		}
		if (canMove) {
			for (int i = 0; i < 4; ++i) {
				++tetris.type[i].y;
			}
		}
		return canMove;
	}

	void show() {
		for (int i = 0; i < HEIGTH; ++i) {
			for (int j = 0; j < WIDTH; ++j) {
				switch (arr[i][j]){
				case 0: {
					setfillcolor(RGB(0, 0, 0));
					fillrectangle(j * 30, i * 30, j * 30 + 30, i * 30 + 30);
				}break;

				case 1: {
					setfillcolor(RGB(150, 150, 150));
					fillrectangle(j * 30, i * 30, j * 30 + 30, i * 30 + 30);
				}break;
				}
			}
		}
	}

	bool gameOver() {
		for (int i = 1; i < WIDTH - 1; ++i) {
			if (arr[0][i] == 1) {
				cout << "GameOver" << endl;
				return true;
			}
		}
		return false;
	}

	bool replay() {
		static int n = 0;
		if (n == 0) {
			++n;
			return true;
		}
		else {
			cout << "再来一次请按y（其他键退出)：";
			char tmp = cin.get();
			if (tmp == 'y') {
				cin.get();
				init();
				return true;
			}
			else {
				cout << "游戏结束！";
				return false;
			}
		}
	}

	void playGame() {
		while (replay()) {
			initgraph(WIDTH * 30, HEIGTH * 30);
			while (true) {
				show();
				tetris.creatType();
				operate();
				move();
				tetris.show();
				stop();
				vanish();
				if (gameOver()) break;
				Sleep(500);
			}
			_getch();
			closegraph();
		}
	}
};

int main()
{
	Game game;
	game.startGame();
	game.playGame();
	return 0;
}
