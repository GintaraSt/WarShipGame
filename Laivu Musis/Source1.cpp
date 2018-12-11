// Laivu Musis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

const char hit = 'X';
const char miss = '+';
const char ship = 'O';
const char emptyCell = '*';

class Ocean {
private:
	char Field[11][11];

	bool AddShipUp(int x, int y, int length) {
		if (y - length < 0) {
			//cout << "Laivas iseina uz lauko ribu\n";
			return false;
		}

		if ((Field[y + 1][x] != emptyCell) && (y + 1 <= 10)) return false;
		if ((Field[y - length][x] != emptyCell) && (y - length >= 1)) return false;
		if (((Field[y + 1][x + 1] != emptyCell) || (Field[y - length][x + 1] != emptyCell)) && (x + 1 <= 10) && (y - length >= 1) && (y + 1 <= 10)) return false;
		if (((Field[y + 1][x - 1] != emptyCell) || (Field[y - length][x - 1] != emptyCell)) && (x - 1 >= 1) && (y - length >= 1) && (y + 1 <= 10)) return false;

		int i = y;

		while (i > y - length) {
			if ((Field[i][x] == ship) || ((Field[i][x + 1] != emptyCell) && (x + 1 <= 10)) || ((Field[i][x - 1] != emptyCell) && (x - 1 >= 1))) {
				//cout << "Laivas susiduria su kitu laivu\n";
				return false;
			}
			i--;
		}

		i = y;
		while (i > y - length) {
			Field[i][x] = ship;
			i--;
		}
		return true;
	}

	bool AddShipDown(int x, int y, int length) {
		if (y + length > 11) {
			//cout << "Laivas iseina uz lauko ribu\n";
			return false;
		}

		if ((Field[y - 1][x] != emptyCell) && (y - 1 >= 1)) return false;
		if ((Field[y + length][x] != emptyCell) && (y + length <= 10)) return false;
		if (((Field[y - 1][x + 1] != emptyCell) || (Field[y + length][x + 1] != emptyCell)) && (x + 1 <= 10) && (y + length <= 10) && (y - 1 >= 1)) return false;
		if (((Field[y - 1][x - 1] != emptyCell) || (Field[y + length][x - 1] != emptyCell)) && (x - 1 >= 1) && (y + length <= 10) && (y - 1 >= 1)) return false;

		int i = y;

		while (i < y + length) {
			if ((Field[i][x] == ship) || ((Field[i][x + 1] != emptyCell) && (x + 1 <= 10)) || ((Field[i][x - 1] != emptyCell) && (x - 1 >= 1))) {
				//cout << "Laivas susiduria su kitu laivu\n";
				return false;
			}
			i++;
		}

		i = y;
		while (i < y + length) {
			Field[i][x] = ship;
			i++;
		}
		return true;
	}

	bool AddShipLeft(int x, int y, int length) {
		if (x - length < 0) {
			//cout << "Laivas iseina uz lauko ribu\n";
			return false;
		}

		if ((Field[y][x + 1] != emptyCell) && (x + 1 <= 10)) return false;
		if ((Field[y][x - length] != emptyCell) && (x - length >= 1)) return false;
		if (((Field[y + 1][x + 1] != emptyCell) || (Field[y + 1][x - length] != emptyCell)) && (y + 1 <= 10) && (x - length >= 1) && (x + 1 <= 10)) return false;
		if (((Field[y - 1][x + 1] != emptyCell) || (Field[y - 1][x - length] != emptyCell)) && (y - 1 >= 1) && (x - length >= 1) && (x + 1 <= 10)) return false;

		int i = x;

		while (i > x - length) {
			if ((Field[y][i] == ship) || ((Field[y + 1][i] != emptyCell) && (y + 1 <= 10)) || ((Field[y - 1][i] != emptyCell) && (y - 1 >= 1))) {
				//cout << "Laivas susiduria su kitu laivu\n";
				return false;
			}
			i--;
		}

		i = x;
		while (i > x - length) {
			Field[y][i] = ship;
			i--;
		}
		return true;
	}

	bool AddShipRight(int x, int y, int length) {
		if (x + length > 11) {
			//cout << "Laivas iseina uz lauko ribu\n";
			return false;
		}

		if ((Field[y][x - 1] != emptyCell) && (x - 1 >= 1)) return false;
		if ((Field[y][x + length] != emptyCell) && (x + length <= 10)) return false;
		if (((Field[y + 1][x - 1] != emptyCell) || (Field[y + 1][x + length] != emptyCell)) && (y + 1 <= 10) && (x + length <= 10) && (x - 1 >= 1)) return false;
		if (((Field[y - 1][x - 1] != emptyCell) || (Field[y - 1][x + length] != emptyCell)) && (y - 1 >= 1) && (x + length <= 10) && (x - 1 >= 1)) return false;

		int i = x;
		//i > x - length
		while (i < x + length) {
			if ((Field[y][i] == ship) || ((Field[y + 1][i] != emptyCell) && (y + 1 <= 10)) || ((Field[y - 1][i] != emptyCell) && (y - 1 >= 1))) {
				//cout << "Laivas susiduria su kitu laivu\n";
				return false;
			}
			i++;
		}

		i = x;
		while (i < x + length) {
			Field[y][i] = ship;
			i++;
		}
		return true;
	}

public:
	void CleanOcean() {
		char ABC[10] = { 'A','B','C','D','E','F','G','H','I','J' };

		Field[0][0] = ' ';
		for (int i = 1; i < 11; i++) {
			Field[0][i] = ABC[i - 1];
			Field[i][0] = char(i + 47);
		}
		for (int i = 1; i < 11; i++) {
			for (int j = 1; j < 11; j++) {
				Field[i][j] = emptyCell;
			}
		}
	}

	void ShowOceans(bool cleanPrevious) {
		if (cleanPrevious) system("CLS");
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 11; j++) {
				cout << Field[i][j] << " ";
			}
			cout << endl;
		}
		cout << "----------------------\n";
	}

	bool AddShip(int x, int y, char direction, int length) {
		x++;
		y++;
		if (!((x >= 0) && (x <= 10) && (y >= 0) && (y <= 10))) { cout << "y or x is out of range\n";  return false; }

		if (direction == 'U') {
			if (AddShipUp(x, y, length)) {
				ShowOceans(true);
				return true;
			}
			else {
				return  false;
			}
		}
		else if (direction == 'D') {
			if (AddShipDown(x, y, length)) {
				ShowOceans(true);
				return true;
			}
			else {
				return  false;
			}

		}
		else if (direction == 'L') {
			if (AddShipLeft(x, y, length)) {
				ShowOceans(true);
				return true;
			}
			else {
				return  false;
			}
		}
		else if (direction == 'R') {
			if (AddShipRight(x, y, length)) {
				ShowOceans(true);
				return true;
			}
			else {
				return  false;
			}
		}
		else { cout << "direction not found\n"; return false; }
	}

	int  ShootShip(int x, int y) {
		x++;
		y++;
		if (!((x >= 0) && (x <= 10) && (y >= 0) && (y <= 10))) { cout << "y or x is out of range\n"; return 0; }

		if (Field[x][y] == ship) {
			Field[x][y] = hit;
			if ((((Field[x][y + 1] == hit) || (Field[x][y + 1] == emptyCell) || (Field[x][y + 1] == miss)) && (y + 1 <= 10)) && (((Field[x][y - 1] == hit) || (Field[x][y - 1] == emptyCell) || (Field[x][y - 1] == miss)) && (y - 1 >= 1))
				&& (((Field[x + 1][y] == hit) || (Field[x + 1][y] == emptyCell) || (Field[x + 1][y] == miss)) && (x + 1 <= 10)) && (((Field[x - 1][y] == hit) || (Field[x - 1][y] == emptyCell) || (Field[x - 1][y] == miss)) && (x - 1 >= 1))) return 2;
			return 1; // hit
		}
		else  if (Field[x][y] == emptyCell) {
			Field[x][y] = miss;
			return -1; // miss
		}
		else return 0; // already used given coordinates

	}

	void UpdateEmpty(int x, int y, char symbol) {
		x++; y++;
		Field[x][y] = symbol;
	}

	friend bool LogicalShooting(Ocean &target, int &lastHitY, int &lastHitX, bool &lastShipDestroyed);
};

int convertToInt(char a);
void GeneratePcShips(Ocean &PC);
void addShipsManualy(Ocean &human);
bool shootPC(Ocean &human, int &x, int &y, int &temp);
bool LogicalShooting(Ocean &target, int &lastHitY, int &lastHitX, bool &lastShipDestroyed);

int main()
{
	Ocean human, humanEmpty;
	Ocean PC;

	int lastHitX = 0, lastHitY = 0;
	bool lastShipDestroyed = true;

	humanEmpty.CleanOcean();

	char x;
	int y, temp;

	GeneratePcShips(PC);
	system("PAUSE");
	GeneratePcShips(human);
	//system("PAUSE");
	//addShipsManualy(human);
	humanEmpty.ShowOceans(false);

	int shipsLeftHuman = 20, shipsLeftPC = 20;
	while ((shipsLeftHuman != 0) && (shipsLeftPC != 0)) {
		/*cout << "Jusu eile speti - ";
		cin >> x >> y;
		temp = PC.ShootShip(y, convertToInt(x));
		if (temp == 1 || temp == 2) {
			humanEmpty.UpdateEmpty(y, convertToInt(x), hit);
			shipsLeftPC--;
		}
		if (temp == 0) {
			cout << "jau naudojote sias koordinates arba jos iseina uz lauko ribu" << endl;
		}
		if (temp == -1)	humanEmpty.UpdateEmpty(y, convertToInt(x), miss);*/
		temp = 1;
		if (LogicalShooting(PC, lastHitY, lastHitX, lastShipDestroyed)) shipsLeftPC--;
		//system("PAUSE");
		human.ShowOceans(true);
		//humanEmpty.ShowOceans(false);
		PC.ShowOceans(false);
		if (temp == 2) cout << "Numusete laiva" << endl;

		if (temp != 0) {
			if (LogicalShooting(human, lastHitY, lastHitX, lastShipDestroyed)) shipsLeftHuman--;
			system("PAUSE");
		}
	}

	if (shipsLeftPC == 0) cout << "Sveikiname Laimejote!\n";
	else cout << "Deje si karta nepasiseke\n";

	return 0;
}

void addShipsManualy(Ocean &human) {
	//Ocean human;
	human.CleanOcean();
	human.ShowOceans(true);
	int y, length;
	char x, direction;
	int ShipsRemaining[4] = { 1,2,3,4 };
	int noMoreShips = 10;
	while (noMoreShips > 0) {
		cout << "pridekite laiva - ";
		cin >> x >> y >> direction >> length;
		if (ShipsRemaining[4 - length] == 0) {
			cout << "Nebeturite - " << length << " - ilgio laivu\n";
		}
		else if (human.AddShip(convertToInt(x), y, direction, length)) {
			ShipsRemaining[4 - length]--;
			human.ShowOceans(true);
			noMoreShips = ShipsRemaining[0] + ShipsRemaining[1] + ShipsRemaining[2] + ShipsRemaining[3];
		}
		else cout << "LAIVAS NEPRIDETAS  PATIKRINKITE PARAMETRUS" << endl;
	}
}

void GeneratePcShips(Ocean &PC) {
	//Ocean PC;
	PC.CleanOcean();
	PC.ShowOceans(true);
	int x, y, length;
	char direction;
	int ShipsRemaining[4] = { 1,2,3,4 };
	srand(time(NULL));
	int noMoreShips = 10;
	length = 4;
	int k = 0;
	while (noMoreShips > 0) {
		x = rand() % 10 + 0;
		y = rand() % 10 + 0;
		if ((rand() % 2 + 0) == 0) direction = 'R';
		else direction = 'U';
		//cout << x << " " << y << " " << direction << " " << length << endl;
		//system("PAUSE");
		if (ShipsRemaining[4 - length] != 0) {
			if (PC.AddShip(x, y, direction, length)) {
				ShipsRemaining[4 - length]--;
				if (ShipsRemaining[k] == 0) {
					k++;
					length--;
				}
				PC.ShowOceans(true);
				noMoreShips = ShipsRemaining[0] + ShipsRemaining[1] + ShipsRemaining[2] + ShipsRemaining[3];
			}
		}
		//cout << ".";
	}
}

int convertToInt(char a) {
	switch (a)
	{
	case 'A': return 0;
	case 'B': return 1;
	case 'C': return 2;
	case 'D': return 3;
	case 'E': return 4;
	case 'F': return 5;
	case 'G': return 6;
	case 'H': return 7;
	case 'I': return 8;
	case 'J': return 9;
	case 'a': return 0;
	case 'b': return 1;
	case 'c': return 2;
	case 'd': return 3;
	case 'e': return 4;
	case 'f': return 5;
	case 'g': return 6;
	case 'h': return 7;
	case 'i': return 8;
	case 'j': return 9;
	default:
		return 15;
	}
}

/*Verified as working*/
bool shootPC(Ocean &human, int &x, int &y, int &temp) {
	int xtemp = 0, ytemp = 0;
	do {
		xtemp = rand() % 10 + 0;
		ytemp = rand() % 10 + 0;
		temp = human.ShootShip(xtemp, ytemp);
	} while (temp == 0);

	if ((temp == 1) || (temp == 2)) {
		x = xtemp;
		y = ytemp;
		return true;
	}

	return false;
}

/*All i can say about code in this function is: 😂😂😂😂😂😂😂😂😂😂😂*/
bool LogicalShooting(Ocean &target, int &lastHitY, int &lastHitX, bool &lastShipDestroyed) {
	int temp = 0;
	int availableDirections = 2222; //by default all directions for shooting is available UPLR
	char placement = 'N'; //default placement - none
	if (lastShipDestroyed) {
		if (shootPC(target, lastHitX, lastHitY, temp)) {
			if (temp == 2) lastShipDestroyed = true;
			else lastShipDestroyed = false;
			return true;
		}
		return false;
	}

	//if ((target.Field[lastHitX - 1][lastHitY] == miss) || (lastHitX - 1 < 1)) { availableDirections -= 1; cout << "-1 direction\n"; system("PAUSE"); } // - Left
	if ((target.Field[lastHitX - 1][lastHitY] != emptyCell) || (lastHitX - 1 < 1)) { availableDirections -= 1; cout << "-1 direction\n"; system("PAUSE"); } // - Left
	if (target.Field[lastHitX - 1][lastHitY] == hit) { placement = 'H'; cout << "H direction\n"; system("PAUSE"); } //ship is placed horizontaly
	if ((target.Field[lastHitX + 1][lastHitY] != emptyCell) || (lastHitX + 1 > 10)) { availableDirections -= 10; cout << "-10 direction\n"; system("PAUSE"); } // - Right
	if (target.Field[lastHitX + 1][lastHitY] == hit) { placement = 'H'; cout << "H direction\n"; system("PAUSE"); } //ship is placed horizontaly
	if ((target.Field[lastHitX][lastHitY + 1] != emptyCell) || (lastHitY + 1 > 10)) { availableDirections -= 100; cout << "-100 direction\n"; system("PAUSE"); } // - Down
	if (target.Field[lastHitX][lastHitY + 1] == hit) { placement = 'V'; cout << "V direction\n"; system("PAUSE"); } //ship is placed verticaly
	if ((target.Field[lastHitX][lastHitY - 1] != emptyCell) || (lastHitY - 1 < 1)) { availableDirections -= 1000; cout << "-1000 direction\n"; system("PAUSE"); } // - Up
	if (target.Field[lastHitX][lastHitY - 1] == hit) { placement = 'V'; cout << "V direction\n"; system("PAUSE"); } //ship is placed verticaly

	if (availableDirections % 100 == 11) placement = 'V';
	if (availableDirections / 100 == 11) placement = 'H';
	//cout << "directions - " << availableDirections << endl;
	//system("PAUSE");
	int x = 0;
	bool dirIncrease = true;
	if (placement == 'H') {
		while ((target.Field[lastHitX + x][lastHitY] != emptyCell) && (target.Field[lastHitX + x][lastHitY] != ship)) {
			//cout << "error 205\n"; system("PAUSE");
			if (dirIncrease) {
				x++;
				if ((target.Field[lastHitX + x][lastHitY] == miss) || (lastHitX + x >= 10)) {
					dirIncrease = false;
				}
			}
			else {
				x--;
				if ((target.Field[lastHitX + x][lastHitY] == miss) || (lastHitX + x < 1)) {
					//cout << "Logical Shoot Error 123\n";
					x++;
					//system("PAUSE");
					return false;
				}
			}
		}
		temp = target.ShootShip(lastHitX + x, lastHitY);
		if (temp == 2) lastShipDestroyed = true;
		else lastShipDestroyed = false;
		if (temp == 1) lastHitX += x;
		if (temp == 1 || temp == 2) return true;
		if (temp == -1) return false;
		if (temp == 0) //cout << "Logical Shoot Error 122\n";
			return false;
	}
	if (placement == 'V') {
		while ((target.Field[lastHitX][lastHitY + x] != emptyCell) && (target.Field[lastHitX][lastHitY + x] != ship)) {
			//cout << "error 206\n"; system("PAUSE");
			if (dirIncrease) {
				x++;
				if ((target.Field[lastHitX][lastHitY + x] == miss) || (lastHitY + x > 10)) {
					x--;
					dirIncrease = false;
				}
			}
			else {
				x--;
				if ((target.Field[lastHitX][lastHitY + x] == miss) || (lastHitY + x < 1)) {
					//cout << "Logical Shoot Error 125\n";
					x++;
					//system("PAUSE");
					return false;
				}
			}
		}
		//cout << "error 402\n"; system("PAUSE");
		temp = target.ShootShip(lastHitX, lastHitY + x);
		if (temp == 2) lastShipDestroyed = true;
		else lastShipDestroyed = false;
		if (temp == 1) lastHitY += x;
		if (temp == 1 || temp == 2) return true;
		if (temp == -1) return false;
		if (temp == 0) //cout << "Logical Shoot Error 124\n";
			return false;
	}

	do {
		//cout << "error 211\n" << x << endl; system("PAUSE");
		x = rand() % 4 + 0;
		if ((x == 0) && (availableDirections % 10 == 2)) temp = target.ShootShip(lastHitX + 1, lastHitY);
		else if ((x == 1) && ((availableDirections % 100) / 10 == 2)) temp = target.ShootShip(lastHitX - 1, lastHitY);
		else if ((x == 2) && ((availableDirections % 1000) / 100 == 2)) temp = target.ShootShip(lastHitX, lastHitY + 1);
		else if ((x == 3) && (availableDirections / 1000 == 2)) temp = target.ShootShip(lastHitX, lastHitY - 1);
		//cout << "temp = " << temp << endl;
	} while (temp == 0);
	if (temp == 2) lastShipDestroyed = true;
	else lastShipDestroyed = false;
	if (temp == 1) {
		if (x == 0) lastHitX++;
		else if (x == 1) lastHitX--;
		else if (x == 2) lastHitY++;
		else lastHitY--;
	}
	if (temp == 1 || temp == 2) return true;
	else return false;
}