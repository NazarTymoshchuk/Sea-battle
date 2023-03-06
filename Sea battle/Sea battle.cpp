#include <iostream>
#include "Header.h"
#include "Windows.h"
#include <conio.h>

using namespace std;


int main()
{
    srand(time(nullptr));

    const int ROWS = 10, COLS = 10;
    char* playerMap[ROWS];
    char* compMap[ROWS];
    char* compMapVisible[ROWS];
    for (size_t i = 0; i < ROWS; i++)
    {
        playerMap[i] = new char[COLS];
    }
    for (size_t i = 0; i < ROWS; i++)
    {
        compMap[i] = new char[COLS];
    }
    for (size_t i = 0; i < ROWS; i++)
    {
        compMapVisible[i] = new char[COLS];
    }
    cout << "================== BOT ====================" << endl;
    initMap(compMap, ROWS, COLS);
    initMap(compMapVisible, ROWS, COLS);
    createShips(compMap, ROWS, COLS);
    printMap(compMapVisible, ROWS, COLS);

    cout << endl;
    cout << "================== YOU ====================" << endl;
    initMap(playerMap, ROWS, COLS);
    createShips(playerMap, ROWS, COLS);
    printMap(playerMap, ROWS, COLS);

    while (true)
    {
        stepPlayer(compMap, compMapVisible, ROWS, COLS);
        stepBot(playerMap, ROWS, COLS);
        if (checkWinner(playerMap, ROWS, COLS)) {
            cout << "Yoy lose!";
                break;
        }
        else if (checkWinner(compMap, ROWS, COLS)) {
            cout << "Yoy Win!!!";
                break;
        }
    }

    cin.get();
}

