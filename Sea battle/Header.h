#pragma once

const int ONE_CELL_SHIPS = 4;
const int TWO_CELL_SHIPS = 3;
const int THREE_CELL_SHIPS = 2;
const int FOUR_CELL_SHIPS = 1;

void printMap(char** Map_Player, const int row, const int col);
void createShips(char** map, const int row, const int col);
void initMap(char** map, const int row, const int col);
void stepBot(char** mapPlayer, const int row, const int col);
void stepPlayer(char** map, char** mapBotVisible, const int row, const int col);
bool checkWinner(char** map, const int row, const int col);

//void printMapComp(char** Map_Comp);
//void fillComp(char** Map_Comp);