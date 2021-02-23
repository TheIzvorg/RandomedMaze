#include <iostream>;
#include <Windows.h>;
#include <conio.h>;
#include <ctime>;

using namespace std;
// Game options
struct Options {
	int Map[21][21];
	int mapY = sizeof(Map) / sizeof(Map[0]);
	int mapX = sizeof(Map) / sizeof(Map[0][0]) / mapY;
	// Map textures
	char mapWallTexture,
		mapFieldTexture;
	int wallColor;
	int fieldColor;
	// Player data
	int playerX, playerY;
	char playerModel;
	int playerColor;
	// Finish data
	char endModel;
	int endColor;
	// Item
	int itemColor;
	char itemModel;
	// Scores
	int score;
	int Counter;
};

void SetColor(char symbol, int color) {
	HANDLE _color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(_color, color);
	cout << symbol << " ";
	SetConsoleTextAttribute(_color, 7);
}

void movement(Options& settings) {
	bool isStop = false;
	while (!isStop) {
		switch (_getch())
		{
			case 'A':
			case 'a':
			case 75:
				if (settings.Map[settings.playerX - 1][settings.playerY] != 1) {
					if (settings.Map[settings.playerX - 1][settings.playerY] == 2) {
						settings.score++;
					}
					settings.playerX--;
					settings.Map[settings.playerX + 1][settings.playerY] = 0;
				}
				isStop = true;
				break;
			case 'D':
			case 'd':
			case 77:
				if (settings.Map[settings.playerX + 1][settings.playerY] != 1) {
					if (settings.Map[settings.playerX + 1][settings.playerY] == 2) {
						settings.score++;
					}
					settings.playerX++;
					settings.Map[settings.playerX - 1][settings.playerY] = 0;
				}
				isStop = true;
				break;
			case 'S':
			case 's':
			case 80:
				if (settings.Map[settings.playerX][settings.playerY + 1] != 1) {
					if (settings.Map[settings.playerX][settings.playerY + 1] == 2) {
						settings.score++;
					}
					settings.playerY++;
					settings.Map[settings.playerX][settings.playerY - 1] = 0;
				}
				isStop = true;
				break;
			case 'W':
			case 'w':
			case 72:
				if (settings.Map[settings.playerX][settings.playerY - 1] != 1) {
					if (settings.Map[settings.playerX][settings.playerY - 1] == 2) {
						settings.score++;
					}
					settings.playerY--;
					settings.Map[settings.playerX][settings.playerY + 1] = 0;
				}
				isStop = true;
				break;
		}
	}
	settings.Map[settings.playerX][settings.playerY] = 3;
}

void ShowMap(Options settings) {
	for (int y = 0; y < settings.mapY; y++) {
		for (int x = 0; x < settings.mapX; x++) {
			if (settings.Map[x][y] == 1) {
				// Walls
				SetColor(settings.mapWallTexture, settings.wallColor);
			}
			else if (settings.Map[x][y] == 3) {
				// Player
				SetColor(settings.playerModel, settings.playerColor);
			}
			else if (settings.Map[x][y] == 2) {
				// Items
				SetColor(settings.itemModel, settings.itemColor);
			}
			else if (settings.Map[x][y] == 4) {
				// End
				SetColor(settings.endModel, settings.endColor);
			}
			else if (settings.Map[x][y] == 0) {
				// Field
				SetColor(settings.mapFieldTexture, settings.fieldColor);
			}
		}
		cout << endl;
	}
	cout << "Control: [A] Left, [D] Right, [S] Down, [W] Up";
}

void Win() {
	system("CLS");
	cout << "|---------------------------------------------------|\n"
	     << "|----Congratulations on winning the game \"Maze\"!----|\n"
	     << "|-----------Game created by TheIzvorg---------------|\n"
	     << "|---------------------------------------------------|\n";
}

bool DeadEnd(int x, int y, Options settings) {
	int Flag = 0;

	if (x > 2 && settings.Map[x - 2][y] != 1) {
		Flag++;

	}
	else {
	}

	if (y > 2 && settings.Map[x][y - 2] != 1) {
		Flag++;

	}
	else {
	}

	if (x < 17 && settings.Map[x + 2][y] != 1) {
		Flag++;
	}
	else {
	}

	if (y < 17 && settings.Map[x][y + 2] != 1) {
		Flag++;
	}
	else {
	}
	
	if (Flag == 4)
		return true;
	else
		return false;
}

void CreateMaze(Options& settings) {
	for (int y = 0; y < settings.mapY; y++) {
		for (int x = 0; x < settings.mapX; x++) {
			settings.Map[x][y] = 1;
		}
	}
	int buff[] = {0,0};
	for (int x = 3, y = 3;;) {
		for (;;) {
			int c = rand() % 4 + 1;
			switch (c) {
			case 1:
				if (x > 2 && settings.Map[x - 2][y] == 1) {
					settings.Map[x - 2][y] = 0;
					settings.Map[x - 1][y] = 0;
					x -= 2;
				}
					break;
			case 2:
				if (x < settings.mapX - 3 && settings.Map[x + 2][y] == 1) {
					settings.Map[x + 2][y] = 0;
					settings.Map[x + 1][y] = 0;
					x += 2;
				}
					break;
			case 3:
				if (y > 2 && settings.Map[x][y - 2] == 1) {
					settings.Map[x][y - 2] = 0;
					settings.Map[x][y - 1] = 0;
					y -= 2;
				}
					break;
			case 4:
				if (y < settings.mapY - 3 && settings.Map[x][y + 2] == 1) {
					settings.Map[x][y + 2] = 0;
					settings.Map[x][y + 1] = 0;
					y += 2;
				}
					break;
			}
			if (DeadEnd(x, y, settings) || buff[0] == x && buff[1] == y) {
				settings.Counter++;
				break;
			}
			buff[0] = x;
			buff[1] = y;
		}
		if (settings.Counter <= 600) {
			do {
				x = 2 * (rand() % ((settings.mapX - 1) / 2)) + 1;
				y = 2 * (rand() % ((settings.mapY - 1) / 2)) + 1;
			} while (settings.Map[x][y] != 0);
		}
		else{
			break;
		}
	}
}

int main() {
	setlocale(0, "");

	Options settings;
	settings.score = 0;
	settings.Counter = 0;
	settings.mapWallTexture = '#';
	settings.mapFieldTexture = '.';
	settings.wallColor = 15;
	settings.fieldColor = 8;
	settings.playerModel = 'O';
	settings.playerColor = 13;
	settings.itemModel = 'I';
	settings.itemColor = 14;
	settings.endModel = 'F';
	settings.endColor = 12;

	srand(time(NULL));
	int count = 0;
	CreateMaze(settings);
	for (int x = rand() % 10 + 1, y = rand() % 10 + 1; y < settings.mapY && x < settings.mapX; x++) {
		if (settings.Map[x][y] == 0) {
			settings.playerX = x;
			settings.playerY = y;
		}
		if (settings.playerX == x) {
			break;
		}
	}
	for (int x = rand() % 21, y = rand() % 21;;x = rand() % 21, y = rand() % 21) {
		if (settings.Map[x][y] == 0 && count != 4) {
			settings.Map[x][y] = 2;
			count++;
		}
		else if (count == 4) {
			break;
		}
		
	}
	settings.Map[settings.playerX][settings.playerY] = 3;

	SetConsoleTitle(L"Maze");
	// Cursor disable
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);

	for (;;) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
		if (settings.score == 4) {
			for (int y = 18; y < settings.mapY; y++) {
				for (int x = 17; x < settings.mapX; x++) {
					if (settings.Map[x][y] == 0 && settings.Map[x][y+1] != 0) {
						settings.Map[x][y] = 4;
						settings.Map[x][y+1] = 4;
						x += 3;
						y += 3;
					}
				}
			}
			settings.score++;
		}
		ShowMap(settings);
		if (settings.Map[settings.playerX][settings.playerY + 1] == 4) {
			Win();
			break;
		}
		movement(settings);
	}

	int _; cin >> _;
	return 0;
}
