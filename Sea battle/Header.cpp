#include <iostream>, <ctime>
#include "Header.h"
#include "Windows.h"
#include <conio.h>

using namespace std;
   
void gotoxy(int x, int y) {
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

void printMap(char** mapPlayer, const int row, const int col)
{

	cout << "    1   2   3   4   5   6   7   8   9   10     X" << endl;
	cout << "  ";
	for (size_t i = 0; i < 1; i++)
	{
		cout<< char(201);
		for (size_t i = 1; i < 40; i++)
		{
			if (i % 4 == 0 && i > 1) {
				cout << char(203);
			}
			else { cout << char(205); }
		}
		cout << char(187);
	}
	cout << endl;

	for (size_t i = 0, s = 0, q = 1; i < 20; i++)
	{
		if (i % 2 == 0) {

			if (q > 9) {
				cout << q;
			}
			else {
				cout << q << " ";
			}
			for (size_t j = 0; j < 10; j++)
			{
				cout << char(186) << " " << mapPlayer[s][j] << " ";
				if (j >= 9) { cout << char(186); }
			}
				s++;
			cout << endl;
			q++;
		}
		else {
			if (i < 18)
			{
				cout << "  ";
				cout << char(204);
				for (size_t j = 1; j < 40; j++)
				{
					if (j % 4 == 0) { cout << char(206); }
					else { cout << char(205); }
				}
				cout << char(185);
				cout << endl;
			}
			else {
				cout << "  ";
				cout << char(200);
				for (size_t j = 1; j < 40; j++)
				{
					if (j % 4 == 0) { cout << char(202); }
					else { cout << char(205); }
				}
				cout << char(188);
				cout << endl;
			}
		}
	}
	cout << "Y" << endl;
	
}

bool isValidOneShipCoord(char** map, const int row, const int col, int x, int y)
{
	if (x < 0  || y < 0 || x >= col || y >= row) return false;

	if (map[y][x] != ' ') return false;

	if (x != 0 && map[y][x - 1] != ' ') return false;
	if (x != col - 1 && map[y][x + 1] != ' ') return false;

	if (y != 0 && map[y - 1][x] != ' ') return false;
	if (y != row - 1 && map[y + 1][x] != ' ') return false;

	if (x != 0 && y != 0 && map[y - 1][x - 1] != ' ') return false;
	if (x != col - 1 && y != 0 && map[y - 1][x + 1] != ' ') return false;
	if (x != col - 1 && y != row - 1 && map[y + 1][x + 1] != ' ') return false;
	if (y != row - 1 && x != 0 && map[y + 1][x - 1] != ' ') return false;

	return true;
}
bool isValidTwoShipCoord(char** map, const int row, const int col, int x, int y, bool isVertical)
{
	if (isVertical)
	{
		if (!isValidOneShipCoord(map, row, col, x, y)) return false;
		else if (!isValidOneShipCoord(map, row, col, x, y+1)) return false;
	}
	else
	{
		if (!isValidOneShipCoord(map, row, col, x, y)) return false;
		else if (!isValidOneShipCoord(map, row, col, x + 1, y)) return false;
	}

	return true;
}
bool isValidThreeShipCoord(char** map, const int row, const int col, int x, int y, bool isVertical)
{
	if (isVertical)
	{
		if (!isValidOneShipCoord(map, row, col, x, y)) return false;
		else if (!isValidOneShipCoord(map, row, col, x, y + 1)) return false;
		else if (!isValidOneShipCoord(map, row, col, x, y + 2)) return false;
	}
	else
	{
		if (!isValidOneShipCoord(map, row, col, x, y)) return false;
		else if (!isValidOneShipCoord(map, row, col, x + 1, y)) return false;
		else if (!isValidOneShipCoord(map, row, col, x + 2, y)) return false;
	}

	return true;
}
bool isValidFourShipCoord(char** map, const int row, const int col, int x, int y, bool isVertical)
{
	if (isVertical)
	{
		if (!isValidOneShipCoord(map, row, col, x, y)) return false;
		else if (!isValidOneShipCoord(map, row, col, x, y - 1)) return false;
		else if (!isValidOneShipCoord(map, row, col, x, y + 1)) return false;
		else if (!isValidOneShipCoord(map, row, col, x, y + 2)) return false;
	}
	else
	{
		if (!isValidOneShipCoord(map, row, col, x, y)) return false;
		else if (!isValidOneShipCoord(map, row, col, x - 1, y)) return false;
		else if (!isValidOneShipCoord(map, row, col, x + 1, y)) return false;
		else if (!isValidOneShipCoord(map, row, col, x + 2, y)) return false;
	}

	return true;
}

void initMap(char** map, const int row, const int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			map[i][j] = ' ';
		}
	}
}
void createShips(char** map, const int row, const int col)
{
	int x, y;
	////////// one-cell ships
	for (size_t i = 0; i < ONE_CELL_SHIPS; i++)
	{
		do
		{
			x = rand() % col;
			y = rand() % row;

		} while (!isValidOneShipCoord(map, row, col, x, y));

		map[y][x] = char(254);
	}

	bool isVertical;
	////////// two-cell ships
	for (size_t i = 0; i < TWO_CELL_SHIPS; i++)
	{
		do
		{
			x = rand() % col;
			y = rand() % row;
			isVertical = rand() % 2;

		} while (!isValidTwoShipCoord(map, row, col, x, y, isVertical));

		if (isVertical == 0) {
			map[y][x] = char(221);
			map[y][x + 1] = char(221);
		}
		else {
			map[y][x] = char(221);
			map[y + 1][x] = char(221);
		}
	}
	////////// three-cell ships
	for (size_t i = 0; i < THREE_CELL_SHIPS; i++)
	{
		do
		{
			x = rand() % col;
			y = rand() % row;
			isVertical = rand() % 2;

		} while (!isValidThreeShipCoord(map, row, col, x, y, isVertical));

		if (isVertical == 0) {
			map[y][x] = char(176);
			map[y][x + 1] = char(176);
			map[y][x + 2] = char(176);
		}
		else {
			map[y][x] = char(176);
			map[y + 1][x] = char(176);
			map[y + 2][x] = char(176);
		}
	}
	////////// four-cell ships
	for (size_t i = 0; i < FOUR_CELL_SHIPS; i++)
	{
		do
		{
			x = rand() % col;
			y = rand() % row;
			isVertical = rand() % 2;

		} while (!isValidFourShipCoord(map, row, col, x, y, isVertical));

		if (isVertical == 0) {
			map[y][x] = char(178);
			map[y][x + 1] = char(178);
			map[y][x + 2] = char(178);
			map[y][x - 1] = char(178);
		}
		else {
			map[y][x] = char(178);
			map[y + 1][x] = char(178);
			map[y + 2][x] = char(178);
			map[y - 1][x] = char(178);
		}
	}
}

int changeCoordinateX(int x)
{
	switch (x)
	{
	case 1: return x = 4; break;
	case 2: return x = 8; break;
	case 3: return x = 12; break;
	case 4: return x = 16; break;
	case 5: return x = 20; break;
	case 6: return x = 24; break;
	case 7: return x = 28; break;
	case 8: return x = 32; break;
	case 9: return x = 36; break;
	case 10: return x = 40; break;
	default:
		break;
	}
}
int changeCoordinateY(int y)
{
	switch (y)
	{
	case 1: return y = 3; break;
	case 2: return y = 5; break;
	case 3: return y = 7; break;
	case 4: return y = 9; break;
	case 5: return y = 11; break;
	case 6: return y = 13; break;
	case 7: return y = 15; break;
	case 8: return y = 17; break;
	case 9: return y = 19; break;
	case 10: return y = 21; break;
	default:
		break;
	}
}
int changeCoordinateBotY(int y)
{
	switch (y)
	{
	case 1: return y = 28; break;
	case 2: return y = 30; break;
	case 3: return y = 32; break;
	case 4: return y = 34; break;
	case 5: return y = 36; break;
	case 6: return y = 38; break;
	case 7: return y = 40; break;
	case 8: return y = 42; break;
	case 9: return y = 44; break;
	case 10: return y = 46; break;
	default:
		break;
	}
}

bool isValidCoordinate(char** map, int x, int y)
{
	if (x > 0 && x < 10 && y > 0 && y < 10 && map[y][x] == ' ')
		return true;
	else if (x == 10 && map[y - 1][x - 1] == ' ' && y == 10 && map[y - 1][x - 1] == ' ' && map[y][x] == ' ')
		return true;
	else if (x == 10 && map[y][x - 1] == ' ' || y == 10 && map[y - 1][x] == ' ' && map[y][x] == ' ')
		return true;
	else 
		return false;
}
void stepPlayer(char** mapBot, char** mapBotVisible, const int row, const int col)
{
	int x, y;
	while (true)
	{
		gotoxy(60, 2);
		cout << "Enter position X :: ";
		gotoxy(80, 2);
		cin >> x;
		gotoxy(60, 3); 
		cout << "Enter position Y :: ";
		gotoxy(80, 3);
		cin >> y;
		gotoxy(80, 2);
		cout << "       ";
		gotoxy(80, 3);
		cout << "       ";
		if (!isValidCoordinate(mapBotVisible, x, y)) {
			gotoxy(60, 5);
			cout << "Error! Try again" << endl;
		}
		else {
			break;
		}

	}
	gotoxy(60, 5);
	cout << "                       ";
	gotoxy(60, 6);
	cout << "                       ";


	if (mapBot[y - 1][x - 1] == char(254) || mapBot[y - 1][x - 1] == char(221) || mapBot[y - 1][x - 1] == char(176) || mapBot[y - 1][x - 1] == char(178)) {
		mapBot[y - 1][x - 1] = ' ';
		x = changeCoordinateX(x);
		y = changeCoordinateY(y);
		gotoxy(x, y);
		cout << char(88);
	}
	else {
		mapBot[y - 1][x - 1] = ' ';
		x = changeCoordinateX(x);
		y = changeCoordinateY(y);
		gotoxy(x, y);
		cout << char(15);
	}

	cin.get();
}
void stepBot(char** mapPlayer, const int row, const int col)
{
	int x, y;
	while (true)
	{
		x = rand() % col;
		y = rand() % row;
		
		if (!isValidCoordinate(mapPlayer, x, y)) {
			continue;
		}
		else {
			break;
		}
		
	}
	if (mapPlayer[y - 1][x - 1] == char(254) || mapPlayer[y - 1][x - 1] == char(221) || mapPlayer[y - 1][x - 1] == char(176) || mapPlayer[y - 1][x - 1] == char(178)) {
		mapPlayer[y - 1][x - 1] = ' ';
		x = changeCoordinateX(x);
		y = changeCoordinateBotY(y);
		gotoxy(x, y);
		cout << char(88);
	}
	else {
		mapPlayer[y - 1][x - 1] = ' ';
		x = changeCoordinateX(x);
		y = changeCoordinateBotY(y);
		gotoxy(x, y);
		cout << char(15);
	}

}

bool checkWinner(char** map, const int row, const int col)
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			if (map[i][j] != ' ') {
				return false;
			}
		}
	}
	return true;
}



//void fillPlayer(char** Map_Player, const int row, const int col)
//{
//	int x, y;
//	srand(unsigned(time(NULL)));
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			Map_Player[i][j] = ' ';
//		}
//	}
//	for (int i = 0; i < 2; i++)
//	{
//		x = 1 + rand() % 8;
//		y = 1 + rand() % 8;
//		cout << x << y << endl;;
//		if (Map_Player[y][x] == char(254) || Map_Player[y + 1][x] == char(254) || Map_Player[y - 1][x] == char(254) || Map_Player[y][x + 1] == char(254) || Map_Player[y][x - 1] == char(254)) {
//			i--;
//			continue;
//		}
//
//		else {
//			Map_Player[y][x] = char(254);
//		}
//	}
//
//	for (size_t i = 0, count = 0; i < 2; i++)
//	{
//		if (count < 2) {
//			x = 1 + rand() % 8;
//			y = 1 + rand() % 8;
//			cout << x << y << endl;;
//			if (Map_Player[y][x] == char(254) || Map_Player[y + 1][x] == char(254) || Map_Player[y - 1][x] == char(254) || Map_Player[y][x + 1] == char(254) || Map_Player[y][x - 1] == char(254) || Map_Player[y][x + 2] == char(254) || Map_Player[y + 1][x + 1] == char(254) || Map_Player[y - 1][x + 1] == char(254)) {
//				i--;
//				continue;
//			}
//			else if (Map_Player[y][x] == char(221) || Map_Player[y + 1][x] == char(221) || Map_Player[y - 1][x] == char(221) || Map_Player[y][x + 1] == char(221) || Map_Player[y][x - 1] == char(221) || Map_Player[y][x + 2] == char(221) || Map_Player[y + 1][x + 1] == char(221) || Map_Player[y - 1][x + 1] == char(221)) {
//				i--;
//				continue;
//			}
//			else {
//				Map_Player[y][x] = char(221);
//				Map_Player[y][x + 1] = char(221);
//			}
//			count++;
//		}
//		else {
//			x = 1 + rand() % 8;
//			y = 1 + rand() % 8;
//
//			if (Map_Player[y][x] == char(254) || Map_Player[y + 1][x] == char(254) || Map_Player[y - 1][x] == char(254) || Map_Player[y][x + 1] == char(254) || Map_Player[y][x - 1] == char(254) || Map_Player[y + 2][x] == char(254) || Map_Player[y + 1][x - 1] == char(254) || Map_Player[y + 1][x + 1] == char(254)) {
//				i--;
//				continue;
//			}
//			else if (Map_Player[y][x] == char(221) || Map_Player[y + 1][x] == char(221) || Map_Player[y - 1][x] == char(221) || Map_Player[y][x + 1] == char(221) || Map_Player[y][x - 1] == char(221) || Map_Player[y + 2][x] == char(221) || Map_Player[y + 1][x - 1] == char(221) || Map_Player[y + 1][x + 1] == char(221)) {
//				i--;
//				continue;
//			}
//			else {
//				Map_Player[y][x] = char(221);
//				Map_Player[y + 1][x] = char(221);
//			}
//		}
//	}
//	
//	for (size_t i = 0, count = 0; i < 2; i++)
//	{
//		if (count == 0) {
//			x = 1 + rand() % 7;
//			y = 1 + rand() % 7;
//
//			if (Map_Player[y][x] == char(254) || Map_Player[y + 1][x] == char(254) || Map_Player[y - 1][x] == char(254) || Map_Player[y][x + 1] == char(254) || Map_Player[y][x - 1] == char(254) || Map_Player[y][x + 2] == char(254) || Map_Player[y + 1][x + 1] == char(254) || Map_Player[y - 1][x + 1] == char(254) || Map_Player[y][x + 3] == char(254) || Map_Player[y + 1][x + 2] == char(254) || Map_Player[y - 1][x + 2] == char(254)) {
//				i--;
//				continue;
//			}
//			else if (Map_Player[y][x] == char(221) || Map_Player[y + 1][x] == char(221) || Map_Player[y - 1][x] == char(221) || Map_Player[y][x + 1] == char(221) || Map_Player[y][x - 1] == char(221) || Map_Player[y][x + 2] == char(221) || Map_Player[y + 1][x + 1] == char(221) || Map_Player[y - 1][x + 1] == char(221) || Map_Player[y][x + 3] == char(221) || Map_Player[y + 1][x + 2] == char(221) || Map_Player[y - 1][x + 2] == char(221)) {
//				i--;
//				continue;
//			}
//			else if (Map_Player[y][x] == char(176) || Map_Player[y + 1][x] == char(176) || Map_Player[y - 1][x] == char(176) || Map_Player[y][x + 1] == char(176) || Map_Player[y][x - 1] == char(176) || Map_Player[y][x + 2] == char(176) || Map_Player[y + 1][x + 1] == char(176) || Map_Player[y - 1][x + 1] == char(176) || Map_Player[y][x + 3] == char(176) || Map_Player[y + 1][x + 2] == char(176) || Map_Player[y - 1][x + 2] == char(176)) {
//				i--;
//				continue;
//			}
//			else {
//				Map_Player[y][x] = char(176);
//				Map_Player[y][x + 1] = char(176);
//				Map_Player[y][x + 2] = char(176);
//			}
//			count++;
//		}
//		else if (count == 1) {
//			x = 1 + rand() % 7;
//			y = 1 + rand() % 7;
//			if (Map_Player[y][x] == char(254) || Map_Player[y + 1][x] == char(254) || Map_Player[y - 1][x] == char(254) || Map_Player[y][x + 1] == char(254) || Map_Player[y][x - 1] == char(254) || Map_Player[y + 2][x] == char(254) || Map_Player[y + 1][x - 1] == char(254) || Map_Player[y + 1][x + 1] == char(254) || Map_Player[y + 3][x] == char(254) || Map_Player[y + 2][x + 1] == char(254) || Map_Player[y + 2][x - 1] == char(254)) {
//				i--;
//				continue;
//			}
//			else if (Map_Player[y][x] == char(221) || Map_Player[y + 1][x] == char(221) || Map_Player[y - 1][x] == char(221) || Map_Player[y][x + 1] == char(221) || Map_Player[y][x - 1] == char(221) || Map_Player[y + 2][x] == char(221) || Map_Player[y + 1][x - 1] == char(221) || Map_Player[y + 1][x + 1] == char(221) || Map_Player[y + 3][x] == char(221) || Map_Player[y + 2][x + 1] == char(221) || Map_Player[y + 2][x - 1] == char(221)) {
//				i--;
//				continue;
//			}
//			else if (Map_Player[y][x] == char(176) || Map_Player[y + 1][x] == char(176) || Map_Player[y - 1][x] == char(176) || Map_Player[y][x + 1] == char(176) || Map_Player[y][x - 1] == char(176) || Map_Player[y + 2][x] == char(176) || Map_Player[y + 1][x - 1] == char(176) || Map_Player[y + 1][x + 1] == char(176) || Map_Player[y + 3][x] == char(176) || Map_Player[y + 2][x + 1] == char(176) || Map_Player[y + 2][x - 1] == char(176)) {
//				i--;
//				continue;
//			}
//			else {
//				Map_Player[y][x] = char(176);
//				Map_Player[y + 1][x] = char(176);
//				Map_Player[y + 2][x] = char(176);
//			}
//			count++;
//		}
//	}
//	
//	for (int i = 0; i < 1; i++)
//	{
//		x = 2 + rand() % 6;
//		y = 2 + rand() % 6;
//
//		if (Map_Player[y][x] == char(254) || Map_Player[y + 1][x] == char(254) || Map_Player[y - 1][x] == char(254) || Map_Player[y][x + 1] == char(254) || Map_Player[y][x - 1] == char(254) || Map_Player[y][x + 2] == char(254) || Map_Player[y + 1][x + 1] == char(254) || Map_Player[y - 1][x + 1] == char(254) || Map_Player[y][x + 3] == char(254) || Map_Player[y + 1][x + 2] == char(254) || Map_Player[y - 1][x + 2] == char(254) || Map_Player[y][x + 4] == char(254) || Map_Player[y + 1][x + 3] == char(254) || Map_Player[y - 1][x + 3] == char(254)) {
//			i--;
//			continue;
//		}
//
//		else if (Map_Player[y][x] == char(221) || Map_Player[y + 1][x] == char(221) || Map_Player[y - 1][x] == char(221) || Map_Player[y][x + 1] == char(221) || Map_Player[y][x - 1] == char(221) || Map_Player[y][x + 2] == char(221) || Map_Player[y + 1][x + 1] == char(221) || Map_Player[y - 1][x + 1] == char(221) || Map_Player[y][x + 3] == char(221) || Map_Player[y + 1][x + 2] == char(221) || Map_Player[y - 1][x + 2] == char(221) || Map_Player[y][x + 4] == char(221) || Map_Player[y + 1][x + 3] == char(221) || Map_Player[y - 1][x + 3] == char(221)) {
//			i--;
//			continue;
//		}
//
//		else if (Map_Player[y][x] == char(176) || Map_Player[y + 1][x] == char(176) || Map_Player[y - 1][x] == char(176) || Map_Player[y][x + 1] == char(176) || Map_Player[y][x - 1] == char(176) || Map_Player[y][x + 2] == char(176) || Map_Player[y + 1][x + 1] == char(176) || Map_Player[y - 1][x + 1] == char(176) || Map_Player[y][x + 3] == char(176) || Map_Player[y + 1][x + 2] == char(176) || Map_Player[y - 1][x + 2] == char(176) || Map_Player[y][x + 4] == char(176) || Map_Player[y + 1][x + 3] == char(176) || Map_Player[y - 1][x + 3] == char(176)) {
//			i--;
//			continue;
//		}
//
//		else if (Map_Player[y][x] == char(178) || Map_Player[y + 1][x] == char(178) || Map_Player[y - 1][x] == char(178) || Map_Player[y][x + 1] == char(178) || Map_Player[y][x - 1] == char(178) || Map_Player[y][x + 2] == char(178) || Map_Player[y + 1][x + 1] == char(178) || Map_Player[y - 1][x + 1] == char(178) || Map_Player[y][x + 3] == char(178) || Map_Player[y + 1][x + 2] == char(178) || Map_Player[y - 1][x + 2] == char(178) || Map_Player[y][x + 4] == char(178) || Map_Player[y + 1][x + 3] == char(178) || Map_Player[y - 1][x + 3] == char(178)) {
//			i--;
//			continue;
//		}
//
//		else {
//			Map_Player[y][x] = char(178);
//			Map_Player[y][x + 1] = char(178);
//			Map_Player[y][x + 2] = char(178);
//			Map_Player[y][x + 3] = char(178);
//		}
//	}
