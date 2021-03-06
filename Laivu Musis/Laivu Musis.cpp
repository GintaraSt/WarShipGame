// Laivu Musis.cpp : This file contains the 'main' function. Program execution begins and ends there.	
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

using namespace std;

const char hit = 'X';
const char miss = '+';
const char ship = 'O';
const char emptyCell = '_';

class Ocean {
private:
	char Field[11][11]; // Array  of game field

	/* Adds ship up from given coordinate*/
	bool AddShipUp(int x, int y, int length) {
		if (y - length < 0) {
			return false;
		}

		if ((Field[y + 1][x] != emptyCell) && (y + 1 <= 10)) return false;
		if ((Field[y - length][x] != emptyCell) && (y - length >= 1)) return false;
		if (((Field[y + 1][x + 1] != emptyCell) || (Field[y - length][x + 1] != emptyCell)) && (x + 1 <= 10) && (y - length >= 1) && (y + 1 <= 10)) return false;
		if (((Field[y + 1][x - 1] != emptyCell) || (Field[y - length][x - 1] != emptyCell)) && (x - 1 >= 1) && (y - length >= 1) && (y + 1 <= 10)) return false;

		int i = y;

		while (i > y - length) {
			if ((Field[i][x] == ship) || ((Field[i][x+1] != emptyCell) &&  (x+1 <= 10)) || ((Field[i][x - 1] != emptyCell) && (x - 1 >= 1))) {
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

	/* Adds ship down from given coordinate*/
	bool AddShipDown(int x, int y, int length) {
		if (y + length > 11) {
			return false;
		}

		if ((Field[y-1][x] != emptyCell) && (y - 1 >= 1)) return false;
		if ((Field[y + length][x] != emptyCell) && (y +length <= 10)) return false;
		if (((Field[y - 1][x + 1] != emptyCell) || (Field[y + length][x + 1] != emptyCell)) && (x + 1 <= 10) && (y + length <= 10) && (y - 1 >= 1)) return false;
		if (((Field[y - 1][x - 1] != emptyCell) || (Field[y + length][x - 1] != emptyCell)) && (x - 1 >= 1) && (y + length <= 10) && (y - 1 >= 1)) return false;

		int i = y;

		while (i < y + length) {
			if ((Field[i][x] == ship) || ((Field[i][x + 1] != emptyCell) && (x + 1 <= 10)) || ((Field[i][x - 1] != emptyCell) && (x - 1 >= 1))) {
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

	/* Adds ship left from given coordinate*/
	bool AddShipLeft(int x, int y, int length) {
		if (x - length < 0) {
			return false;
		}

		if ((Field[y][x+1] != emptyCell) && (x + 1 <= 10)) return false;
		if ((Field[y][x - length] != emptyCell) && (x - length >= 1)) return false;
		if (((Field[y + 1][x + 1] != emptyCell) || (Field[y + 1][x - length] != emptyCell)) && (y + 1 <= 10) && (x - length >= 1) && (x + 1 <= 10)) return false;
		if (((Field[y - 1][x + 1] != emptyCell) || (Field[y - 1][x - length] != emptyCell)) && (y - 1 >= 1) && (x - length >= 1) && (x + 1 <= 10)) return false;

		int i = x;

		while (i > x - length) {
			if ((Field[y][i] == ship) || ((Field[y+1][i] != emptyCell) && (y + 1 <= 10)) || ((Field[y-1][i] != emptyCell) && (y - 1 >= 1))) {
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

	/* Adds ship right from given coordinate*/
	bool AddShipRight(int x, int y, int length) {
		if (x + length > 11) {
			return false;
		}

		if ((Field[y][x - 1] != emptyCell) && (x - 1 >= 1)) return false;
		if ((Field[y][x + length] != emptyCell) && (x + length <= 10)) return false;
		if (((Field[y + 1][x - 1] != emptyCell) || (Field[y + 1][x + length] != emptyCell)) && (y + 1 <= 10) && (x + length <= 10) && (x - 1 >= 1)) return false;
		if (((Field[y - 1][x - 1] != emptyCell) || (Field[y - 1][x + length] != emptyCell)) && (y - 1 >= 1) && (x + length <= 10) && (x - 1 >= 1)) return false;

		int i = x;
		while (i < x + length) {
			if ((Field[y][i] == ship) || ((Field[y + 1][i] != emptyCell) && (y + 1 <= 10)) || ((Field[y - 1][i] != emptyCell) && (y - 1 >= 1))) {
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

	/* Checks if ship wasnt destroyed*/
	bool ShipIsDestroyed(int x, int y) {
		int availableDirections = 2222;  //UDRL
		char placement = 'N';
		if ((Field[x - 1][y] == miss) || (x - 1 < 1)) availableDirections -= 1;  // - Left
		if (Field[x - 1][y] == hit) placement = 'H'; //ship is placed horizontaly
		if ((Field[x + 1][y] == miss) || (x + 1 > 10)) availableDirections -= 10; // - Right
		if (Field[x + 1][y] == hit) placement = 'H'; //ship is placed horizontaly
		if ((Field[x][y + 1] == miss) || (y + 1 > 10)) availableDirections -= 100; // - Down
		if (Field[x][y + 1] == hit) placement = 'V'; //ship is placed verticaly
		if ((Field[x][y - 1] == miss) || (y - 1 < 1)) availableDirections -= 1000; // - Up
		if (Field[x][y - 1] == hit) placement = 'V'; //ship is placed verticaly

		if (((Field[x - 1][y] == emptyCell) || (Field[x - 1][y] == miss) || (x - 1 < 1)) && ((Field[x + 1][y] == emptyCell) || (Field[x + 1][y] == miss) || (x + 1 > 10))
			&& ((Field[x][y + 1] == emptyCell) || (Field[x][y + 1] == miss) || (y + 1 > 10)) && ((Field[x][y - 1] == emptyCell) || (Field[x][y - 1] == miss) || (y - 1 < 1))) return true;

		if (availableDirections % 100 == 11) placement = 'V';
		if (availableDirections / 100 == 11) placement = 'H';

		bool dirIncrease = true;
		int counter = 0;

		if (placement == 'H') {
			while ((Field[x + counter][y] != emptyCell) && (Field[x + counter][y] != miss)) {
				if (dirIncrease) {
					counter++;
					if ((Field[x + counter][y] == miss) || (Field[x + counter][y] == emptyCell) || (x + counter >= 10)) {
						counter--;
						dirIncrease = false;
					}
					else if (Field[x + counter][y] == ship) return false;
				}
				else {
					counter--;
					if ((Field[x + counter][y] == miss) || (Field[x + counter][y] == emptyCell) || (x + counter < 1)) {
						return true;
					}
					else if (Field[x + counter][y] == ship) return false;
				}
			}
		}

		dirIncrease = true;
		counter = 0;

		if (placement == 'V') {
			while ((Field[x][y + counter] != emptyCell) && (Field[x][y + counter] != miss)) {
				if (dirIncrease) {
					counter++;
					if ((Field[x][y + counter] == miss) || (Field[x][y + counter] == emptyCell) || (y + counter >= 10)) {
						counter--;
						dirIncrease = false;
					}
					else if (Field[x][y + counter] == ship) return false;
				}
				else {
					counter--;
					if ((Field[x][y + counter] == miss) || (Field[x][y + counter] == emptyCell) || (y + counter < 1)) {
						return true;
					}
					else if (Field[x][y + counter] == ship) return false;
				}
			}
		}

		return  false;
	}

public:
	/* Clears the game field*/
	void CleanOcean() {
		char ABC[10] = { 'A','B','C','D','E','F','G','H','I','J' };

		Field[0][0] = ' ';
		for (int i = 1; i < 11; i++) {
			Field[0][i] = ABC[i-1];
			Field[i][0] = char(i+47);
		}
		for (int i = 1; i < 11; i++) {
			for (int j = 1; j < 11; j++) {
				Field[i][j] = emptyCell;
			}
		}
	}

	/* outputs game field to the screen*/
	void ShowOceans(bool cleanPrevious) {
		if(cleanPrevious) system("CLS");
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 11; j++) {
				cout << Field[i][j] << " ";
			}
			cout << endl;
		}
		cout << "----------------------\n";
	}

	/* Adds ship to game field*/
	bool AddShip(int x, int y, char direction, int length) {
		x++;
		y++;
		if (!((x >= 0) && (x <= 10) && (y >= 0) && (y <= 10))) { cout << "Koordinates iseina uz lauko ribu\n";  return false; }

		if (direction == 'U') {
			if (AddShipUp(x, y, length)) return true;
			else return  false;
		}
		else if (direction == 'D') {
			if (AddShipDown(x, y, length)) return true;
			else return  false;
		}
		else if (direction == 'L') {
			if (AddShipLeft(x, y, length)) return true;
			else return  false;
		}
		else if (direction == 'R') {
			if (AddShipRight(x, y, length)) return true;
			else return  false;
		}
		else { cout << "Nerasta kryptis - galimos kryptys UDRL\n"; return false; }
	}

	/* Shoots to the coordinates in the field*/
	int  ShootShip(int x, int y) {
		x++;
		y++;
		if (!((x >= 0) && (x <= 10) && (y >= 0) && (y <= 10))) return 0;

		if (Field[x][y] == ship) {
			Field[x][y] = hit;
			if (ShipIsDestroyed(x, y)) return 2; // ship was hit and destroyed
			return 1; // hit
		}
		else  if (Field[x][y] == emptyCell) {
			Field[x][y] = miss;
			return -1; // miss
		}
		else return 0; // already used given coordinates
	}

	/* changes selected coordinates of field into a selected symbol
	(used to mark places where player or computer already shoot*/
	void UpdateEmpty(int x, int y, char symbol) {
		x++; y++;
		Field[x][y] = symbol;
	}

	//These functions checks if shoot wasnt made to a coordinates near the ship that is already destroyed
	friend bool shootPC(Ocean &human, int &x, int &y, int &temp);
	friend bool ShootNoDirection(Ocean &target, int &lastHitX, int &lastHitY, int &temp, bool &lastShipDestroyed, char &Orientation);
	friend bool ShootHorizontal(Ocean &target, int &lastHitX, int &lastHitY, bool &lastShipDestroyed, int &temp, char &Orientation);
	friend bool ShootVertical(Ocean &target, int &lastHitX, int &lastHitY, bool &lastShipDestroyed, int &temp, char &Orientation);
};

int convertToInt(char a);
void GeneratePcShips(Ocean &PC);
void addShipsManualy(Ocean &human);
bool shootPC(Ocean &human, int &x, int &y, int &temp);
bool ShootLogically(Ocean &target, int &lastHitX, int &lastHitY, bool &lastShipDestroyed, char &Orientation);
bool ShootHorizontal(Ocean &target, int &lastHitX, int &lastHitY, bool &lastShipDestroyed, int &temp, char &Orientation);
bool ShootVertical(Ocean &target, int &lastHitX, int &lastHitY, bool &lastShipDestroyed, int &temp, char &Orientation);
bool ShootNoDirection(Ocean &target, int &lastHitY, int &lastHitX, int &temp, bool &lastShipDestroyed, char &Orientation);

int main()
{
	Ocean human, humanEmpty;
	Ocean PC;

	int lastHitX = 0, lastHitX1 = 0, lastHitY = 0, lastHitY1 = 0;
	bool lastShipDestroyed = true, lastShipDestroyed1 = true;
	char Orientation = 'N', Orientation1 = 'N';

	humanEmpty.CleanOcean();

	char x;
	int y, temp;
	

	GeneratePcShips(PC);
	addShipsManualy(human);
	human.ShowOceans(true);
	humanEmpty.ShowOceans(false);

	int shipsLeftHuman = 20, shipsLeftPC = 20;
	while ((shipsLeftHuman != 0) && (shipsLeftPC != 0)) {
		cout << "Jusu eile speti - ";
		cin >> x >> y;
		temp = PC.ShootShip(y, convertToInt(x));
		if (temp == 1 || temp == 2) {
			humanEmpty.UpdateEmpty(y, convertToInt(x), hit);
			shipsLeftPC--;
		}
		if (temp == 0) {
			cout << "jau naudojote sias koordinates arba jos iseina uz lauko ribu" << endl;
		}
		if (temp == -1)	humanEmpty.UpdateEmpty(y, convertToInt(x), miss);

		if (temp != 0) {
			if (ShootLogically(human, lastHitX, lastHitY, lastShipDestroyed, Orientation)) shipsLeftHuman--;
			human.ShowOceans(true);
			humanEmpty.ShowOceans(false);
			if (temp == 2) cout << "Numusete laiva" << endl;
		}
	}

	if (shipsLeftPC == 0) cout << "Sveikiname Laimejote!\n";
	else cout << "Deje si karta nepasiseke\n";

	return 0;
}

/*manualy add ships*/
void addShipsManualy(Ocean &human) {
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
		else if(human.AddShip(convertToInt(x), y, direction, length)){
			ShipsRemaining[4 - length]--;
			human.ShowOceans(true);
			noMoreShips = ShipsRemaining[0] + ShipsRemaining[1] + ShipsRemaining[2] + ShipsRemaining[3];
		}
		else cout << "LAIVAS NEPRIDETAS  PATIKRINKITE PARAMETRUS" << endl;
	}
}

/*randomly generate ships*/
void GeneratePcShips(Ocean &PC) {
	PC.CleanOcean();
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
		if (ShipsRemaining[4 - length] != 0) {
			if (PC.AddShip(x, y, direction, length)) {
				ShipsRemaining[4 - length]--;
				if (ShipsRemaining[k] == 0) {
					k++;
					length--;
				}
				noMoreShips = ShipsRemaining[0] + ShipsRemaining[1] + ShipsRemaining[2] + ShipsRemaining[3];
			}
		}
	}
}

/*char to int*/
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

/*shoot randomly*/
bool shootPC(Ocean &human, int &x, int &y, int &temp) {
	int xtemp = 0, ytemp = 0;
	temp = 0;
	do {
		xtemp = rand() % 10 + 0;
		ytemp = rand() % 10 + 0;
		if(!((human.Field[xtemp][ytemp] == hit) || (human.Field[xtemp+1][ytemp] == hit) || (human.Field[xtemp + 2][ytemp] == hit) || (human.Field[xtemp][ytemp+1] == hit)
			|| (human.Field[xtemp][ytemp + 2] == hit) || (human.Field[xtemp + 1][ytemp + 2] == hit)
			|| (human.Field[xtemp + 2][ytemp + 2] == hit) || (human.Field[xtemp + 2][ytemp + 1] == hit))) temp = human.ShootShip(xtemp, ytemp);
		else temp = 0;
 	} while (temp == 0);
	if ((temp == 1) || (temp == 2)) {
		y = xtemp + 1;
		x = ytemp + 1;
		return true;
	}

	return false;
}

/*shooting function*/
bool ShootLogically(Ocean &target, int &lastHitX, int &lastHitY, bool &lastShipDestroyed, char &Orientation) {
	int temp;
	if (lastShipDestroyed) {
		if (shootPC(target, lastHitX, lastHitY, temp)) {
			if (temp == 2) lastShipDestroyed = true;
			else{ lastShipDestroyed = false;
			lastHitX--;
			lastHitY--;
			}
				return true;
		}
		else return false;
	}
	
	if (Orientation == 'N') {
		if (ShootNoDirection(target, lastHitY, lastHitX, temp, lastShipDestroyed, Orientation)) {
			return true;
		}
		else return false;
	}

	else if (Orientation == 'H') {
		if (ShootHorizontal(target, lastHitY, lastHitX, lastShipDestroyed, temp, Orientation)) return true;
		else return false;
	}
	else {
		if (ShootVertical(target, lastHitY, lastHitX, lastShipDestroyed, temp, Orientation)) return true;
		else return false;
	}
}

/*shoots ship to find out its orientation*/
bool ShootNoDirection(Ocean &target, int &lastHitX, int &lastHitY, int &temp, bool &lastShipDestroyed, char &Orientation) {
	if(!((target.Field[lastHitX+2][lastHitY+1] == emptyCell) && (target.Field[lastHitX + 3][lastHitY + 1] == hit)))
	temp = target.ShootShip(lastHitX + 1, lastHitY);
	else temp = 0;
	if (temp == 2) {
		lastShipDestroyed = true;
		Orientation = 'N';
		return true;
	}
	else if (temp == 1) {
		lastShipDestroyed = false;
		Orientation = 'H';
		lastHitX++;
		return true;
	}
	else if (temp == -1) return false;
	else {
		if (!((target.Field[lastHitX][lastHitY + 1] == emptyCell) && (target.Field[lastHitX - 1][lastHitY + 1] == hit)))
		temp = target.ShootShip(lastHitX - 1, lastHitY);
		else temp = 0;
		if (temp == 2) {
			lastShipDestroyed = true;
			Orientation = 'N';
			return true;
		}
		else if (temp == 1) {
			lastShipDestroyed = false;
			lastHitX--;
			Orientation = 'H';
			return true;
		}
		else if (temp == -1) return false;
		else {
			if (!((target.Field[lastHitX + 1][lastHitY + 2] == emptyCell) && (target.Field[lastHitX + 1][lastHitY + 3] == hit)))
			temp = target.ShootShip(lastHitX, lastHitY + 1);
			else temp = 0;
			if (temp == 2) {
				lastShipDestroyed = true;
				Orientation = 'N';
				return true;
			}
			else if (temp == 1) {
				lastShipDestroyed = false;
				Orientation = 'V';
				lastHitY++;
				return true;
			}
			else if (temp == -1) return false;
			else {
				if (!((target.Field[lastHitX + 1][lastHitY] == emptyCell) && (target.Field[lastHitX + 1][lastHitY - 1] == hit)))
				temp = target.ShootShip(lastHitX, lastHitY - 1);
				else temp = 0;
				if (temp == 2) {
					Orientation = 'N';
					lastShipDestroyed = true;
					return true;
				}
				else if (temp == 1) {
					lastShipDestroyed = false;
					Orientation = 'V';
					lastHitY--;
					return true;
				}
				else if (temp == -1) return false;
				else {
					cout << "How the F**K is this possible?\n";
					cout << lastHitX << " - " << lastHitY << " - - " << temp << endl;
					system("PAUSE");
				}
			}
		}
	}
}

/*shoots ship  horizontaly*/
bool ShootHorizontal(Ocean &target, int &lastHitX, int &lastHitY, bool &lastShipDestroyed, int &temp, char &Orientation) {
	if (!((target.Field[lastHitX + 2][lastHitY + 1] == emptyCell) && (target.Field[lastHitX + 3][lastHitY + 1] == hit)))
	temp = target.ShootShip(lastHitX + 1, lastHitY);
	else temp = 0;
	if (temp == 2) {
		Orientation = 'N';
		lastShipDestroyed = true;
		return true;
	}
	else if (temp == 1) {
		lastHitX++;
		return true;
	}
	else if (temp == -1) return false;
	else {
		while (true) {
			temp = target.ShootShip(lastHitX - 1, lastHitY);
			if (temp == 2) {
				Orientation = 'N';
				lastShipDestroyed = true;
				return true;
			}
			else if (temp == 1) {
				lastHitX--;
				return true;
			}
			else if (temp == -1) return false;
			else lastHitX--;
		}
	}
}

/*Shoots ship verticaly*/
bool ShootVertical(Ocean &target, int &lastHitX, int &lastHitY, bool &lastShipDestroyed, int &temp, char &Orientation) {
	if (!((target.Field[lastHitX + 1][lastHitY + 2] == emptyCell) && (target.Field[lastHitX + 1][lastHitY + 3] == hit)))
	temp = target.ShootShip(lastHitX, lastHitY + 1);
	else temp = 0;
	if (temp == 2) {
		Orientation = 'N';
		lastShipDestroyed = true;
		return true;
	}
	else if (temp == 1) {
		lastHitY++;
		return true;
	}
	else if (temp == -1) return false;
	else {
		while (true) {
			temp = target.ShootShip(lastHitX, lastHitY - 1);
			if (temp == 2) {
				Orientation = 'N';
				lastShipDestroyed = true;
				return true;
			}
			else if (temp == 1) {
				lastHitY--;
				return true;
			}
			else if (temp == -1) return false;
			else lastHitY--;
		}
	}
}
//ships coordinates for testing
// A 6 D 1 B 0 R 2 C 2 D 3 C 8 R 2 D 6 L 1 F 0 D 4 F 6 R 3 I 2 D 2 J 0 U 1 I 9 U 1