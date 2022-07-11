/*
---------------------------------------------
Dev:		Emilio Armas, Diaz Cristofer
Subject:	PROYECTO 1B
			SNAKE GAME
---------------------------------------------

*/


#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

#include "../lib/utility.h"

using namespace std;

const int sqrx = 30;
const int sqry = 25;

char name[10];

int delay_ms, score;

bool finish;

int snakeH[2];

int food[2];

int snakedir;

int cola;

int colaX[100];

int colaY[100];

void intro()
{
	showcursor(false);

	system("cls");

	setColor(BLACK, LGREEN);
	progressbar(25, 20, char(219));

	system("cls");

	setColor(BLACK, WHITE);
	cout << "\rWELCOME TO ";
	setColor(BLACK, LGREEN);
	cout << "SNAKE GAME!";
	setColor(BLACK, WHITE);

	cout << "\n\nIngresa tu nombre: ";
	cin >> name;

	system("cls");
	cout << "Bienvenido, " << name << "!";

	setColor(BLACK, LGREEN);
	cout << "\n\nInstrucciones: ";

	setColor(BLACK, WHITE);
	cout << "\n> Alimenta a la serpiente consumiendo las frutas (δ).";
	cout << "\n> Si te chocas con tu propio cuerpo o las paredes, el juego termina.";
	cout << "\n\n> Muevete con wasd.";
	cout << "\n> Presiona x para terminar el juego.";
	cout << "\n\n> Si terminas el juego:\n\t -> presiona c para comenzar de nuevo.\n\t -> presiona cualquier tecla para salir.";
	cout << "\n\n> Buena suerte y disfruta!";

	setColor(BLACK, LBLUE);
	cout << "\n\nPresiona cualquier tecla para continuar...";

	setColor(BLACK, WHITE);

	getch();
}

void inic()
{
	finish = false;
	delay_ms = 25;
	score = 0;
	cola = 0;

	snakeH[0] = sqrx / 2;
	snakeH[1] = sqry / 2;

	food[0] = (rand()%(sqrx-4))+2;
	food[1] = (rand()%(sqry-4))+2;
}

void draw()
{
	gotoxy(0, 0);
	setColor(BLACK, WHITE);
	for (int j = 0; j < sqry; j++)
	{
		if (j == 0 || j == sqry - 1)
		{

			// marco superior e inferior

			for (int i = 0; i < sqrx; i++)
			{
				cout<<char(35);
			}

			cout << "\n";
		}
		else
		{

			// parte interna

			for (int i = 0; i < sqrx; i++)
			{

				if (i == 0 || i == sqrx - 1)
				{
					cout << char(35);
				}
				else if (snakeH[0] == i && snakeH[1] == j)
				{	
					setColor(BLACK, LGREEN);
					cout << char(232);
					setColor(BLACK, WHITE);
				}
				else if (food[0] == i && food[1] == j)
				{
					setColor(BLACK, LRED);
					cout << char(235);
					setColor(BLACK, WHITE);
				}
				else 
				{
					bool printspace = true;

					for (int m = 0; m < cola; m++){
						if(colaX[m] == i && colaY[m] == j){
							setColor(BLACK, LGREEN);
							cout<<'o';
							setColor(BLACK, WHITE);
							printspace = false;
						}
					}

					if(printspace)
					cout<<" ";
				}
			}
			cout << "\n";
		}
	}

	cout<<"\nJUGADOR: "<<name;

	cout<<"\nSCORE: "<<score;
}

void controls()
{	
	if (_kbhit())
	{
		switch (_getch())
		{
			case ('a'):
				if(snakedir == 2)
				break;
				snakedir = 1;
				break;
			case ('d'):
				if(snakedir == 1)
				break;
				snakedir = 2;
				break;
			case ('w'):
				if(snakedir == 4)
				break;
				snakedir = 3;
				break;
			case ('s'):
				if(snakedir == 3)
				break;
				snakedir = 4;
				break;
			case ('x'):
				finish = true;
				break;
		}

	}
}

void logic()
{

	int colaX1, colaY1, colaX2, colaY2;

	colaX1 = colaX[0];
	colaY1 = colaY[0];
	
	colaX[0] = snakeH[0];
	colaY[0] = snakeH[1];

	for (int i = 1; i < cola; i++){
		colaX2 = colaX[i];
		colaY2 = colaY[i];

		colaX[i] = colaX1;
		colaY[i] = colaY1;
		
		colaX1 = colaX2;
		colaY1 = colaY2;
	}

	switch(snakedir)
	{
		case(1):
			snakeH[0]--;
			break;
		case(2):
			snakeH[0]++;
			break;
		case(3):
			snakeH[1]--;
			Sleep(5);
			break;
		case(4):
			snakeH[1]++;
			Sleep(5);
			break;
		default:
			break;
	}

	if(snakeH[0] == 0 || snakeH[0] == sqrx-1 || snakeH[1] == 0 || snakeH[1] == sqry-1){
		finish = true;
	}

	for (int j = 0; j < cola; j++){
		if (colaX[j] == snakeH[0] && colaY[j] == snakeH[1])
		finish = true;
	}

	if (food[0] == snakeH[0] && food[1] == snakeH[1])
	{
		//food[0] = (rand()%(sqrx-2))+1;	//comida hasta los bordes
		//food[1] = (rand()%(sqry-2))+1;	 
		food[0] = (rand()%(sqrx-4))+2;  	//comida hasta uno antes de los bordes
		food[1] = (rand()%(sqry-4))+2;
		cola++;
		score = score + 10;
	}

	switch(score){
		case(0):
			delay_ms = 25;
			break;
		case(100):
			delay_ms = 15;
			break;
		case(200):
			delay_ms = 10;
			break;
		default:
			delay_ms = 25;
			break;	
	}

}

void end(){

	setColor(BLACK, LRED);
	char mensajefin [16] = {'F','I','N',' ','D','E','L',' ','J','U','E','G','O',' ',':','('};

	for(int i = 0; i < 16; i++){
		gotoxy(sqrx/2-8+i, sqry/2-4);
		cout<<mensajefin[i];
		Sleep(100);
	}

	setColor(BLACK, WHITE);
	gotoxy(sqrx/2-8, sqry/2-2);
	cout<<"FINAL SCORE: "<<score;

 	setColor(BLACK, DGREY);
	gotoxy(sqrx/2-11, sqry/2+1);
	cout<<"Press c to play again";
	gotoxy(sqrx/2-11, sqry/2+2);
	cout<<"Press x to exit"; 
	
	setColor(BLACK, WHITE);
	for(int i = 0; i < sqry/2+2; i++){
		cout<<endl;
	}
	
}

int main()
{
	intro();
	again:
	srand(time(0)); // seed para rand()
	inic();
	system("cls");

	while (!finish)
	{
		draw();
		controls();
		logic();

		Sleep(delay_ms);
	}
	end();
	
 	Sleep(100);
	
	bool pressXC = false;

	while(!pressXC)
	{
		switch(_getch()){
			case('c'):
				pressXC = true;
				finish = false;
				snakedir = 0;
				goto again;
				break;
			case('x'):
				pressXC = true;
				break;
			default:
				break;
		}
	} 

	return 0;
}
