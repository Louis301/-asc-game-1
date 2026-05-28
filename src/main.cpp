/*
	Name: Sea Battle
	Copyright: 
	Author: Louis
	Date: 28.09.21 21:49
	Description: This is my first console game
*/


#include "gameLogic.h"
using namespace std;

enum cmd
{
	c = 99,
	Esc = 27
};

int main()
{
	playAgain:
	gameCicle(); //game process
	 
	setcur(14, 10); 
	SetColor(14, 0); 
	cout << "c"; 
	SetColor(15, 0); 
	cout << " - play again";
	
	field_printer(' ', 0, 0, 11, 1, 14, 9);
	
	againInput:
	switch(getch())
	{
		case c: 
			goto playAgain; 
			break;
		case Esc: 
			SetColor(15, 0); 
			setcur(0, map_lenght + 2);
			Sleep(1000);
    		return 0;
		default: 
			goto againInput; 
			break;
    }
}


