#include<iostream>
#include<windows.h>

using namespace std;

enum Colors 
{
    BLACK      = 0,
    BLUE       = 1,
    GREEN      = 2,
    CYAN       = 3,
    RED        = 4,
    MAGENTA    = 5,
    BROWN      = 6,
    LGREY      = 7,
    DGREY      = 8,
    LBLUE      = 9,
    LGREEN     = 10,
    LCYAN      = 11,
    LRED       = 12,
    LMAGENTA   = 13,
    YELLOW     = 14,
    WHITE      = 15
};

void gotoxy(int x, int y) 
{ 
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE); 
COORD c; 
   c.X=x; 
   c.Y=y; 
   SetConsoleCursorPosition(h,c); 
}

void showcursor(bool cursor)
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = cursor;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void setColor(int Background, int Text)
{ 
    int colorTexto= Text + (Background * 16);         // los colores van del 0 al 255 por eso se multiplica por 16
    HANDLE terminal = GetStdHandle(STD_OUTPUT_HANDLE);   // referenciamos a la consola.
    SetConsoleTextAttribute(terminal, colorTexto); 
}

void progressbar(int length, int delay, char simb)
{
    for (int i=0; i<=100; i++){
        
        int perc=i*length/100;

        cout<<'\r';

        for (int j=0; j<length; j++){
           
           cout<<((j<=perc)? simb : ' ');
            
        }

        cout<<' '<<i<<'%';

        Sleep(delay);
    }
    
}