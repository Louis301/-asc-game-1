#include "outputFormating.h"
#include "fields.h"

int computerScore = 0;
int gamerScore = 0;

//printing first condition of fields
void printerFirstCondition()
{
	//printing of main frame
	for(int i = 0; i < 14; i++)
	{
		for(int j = 0; j < 42; j++)
		{
			if(i == 0 && j == 0) {cout << char(201); continue;} //left_up
			if(i == 0 && j == 41) {cout << char(187); continue;} //right_up
			if(i == 13 && j == 41) {cout << char(188); continue;} //right_down
			if(i == 13 && j == 0) {cout << char(200); continue;} //left_down
			
			if(j == 0) {cout << char(186); continue;} //left
			if(i == 0) {cout << char(205); continue;} //up
			if(j == 41) {cout << char(186); continue;} //right
			if(i == 13) {cout << char(205); continue;} //down
			
			cout << " ";
		}
		cout << endl;
	}
	
	//printing gamer's field
	for(int i = 0; i < map_lenght; i++)
	{
		for(int j = 0; j < map_lenght; j++)
		{
			if(gamerField_vector[i][j] == 's') field_printer('s', 9, 1, 1, 1, j + 1, i + 1);
			if(gamerField_vector[i][j] == 'm') field_printer('m', 11, 1, 1, 1, j + 1, i + 1);
			if(gamerField_vector[i][j] == 'w') field_printer('w', 15, 14, 1, 1, j + 1, i + 1);
			if(gamerField_vector[i][j] == 'd') field_printer('d', 15, 12, 1, 1, j + 1, i + 1);
			if(gamerField_vector[i][j] == 'f') field_printer('f', 8, 8, 1, 1, j + 1, i + 1);
			if(gamerField_vector[i][j] == 'b') field_printer('b', 15, 7, 1, 1, j + 1, i + 1);
		}
	}
	
	//printing computer's field
	for(int i = 0; i < map_lenght; i++)
	{ 
		for(int j = 0; j < map_lenght; j++)
		{
			if(computerField_vector[i][j] == 's' || computerField_vector[i][j] == 'b') field_printer('s', 9, 1, 1, 1, j + 29, i + 1);
			if(computerField_vector[i][j] == 'm') field_printer('m', 11, 1, 1, 1, j + 29, i + 1);
			if(computerField_vector[i][j] == 'w') field_printer('w', 15, 14, 1, 1, j + 29, i + 1);
			if(computerField_vector[i][j] == 'd') field_printer('d', 15, 12, 1, 1, j + 29, i + 1);
			if(computerField_vector[i][j] == 'f') field_printer('f', 8, 8, 1, 1, j + 29, i + 1);
		}
	}

	SetColor(15, 0);	
  	setcur(18, 4); cout << "Score";
  	setcur(15, 5); cout << "------------";
  	setcur(15, 6); cout << "computer: ";
  	setcur(17, 7); cout << "user: ";
	setcur(17, 9); SetColor(14, 0); cout << "h"; SetColor(15, 0); cout << " - help";
	
	//printer Scores of gamers
    SetColor(15, 0);
    setcur(25, 6); 
	cout << computerScore;
	
	SetColor(15, 0);
	setcur(23, 7); 
	cout << gamerScore;
}

//print score of players
void scorePrinter()
{	
	field_printer(' ', 0, 0, 8, 2, 17, 1);

	//printer gamer score
	if(gamerScore == 10) 
	{
		SetColor(14, 0);
		setcur(15, 1); cout << "------------";
		setcur(17, 2); cout << "You win!";
	}
		
	//printer computer score
	if(computerScore == 10) 
	{
		field_printer(' ', 0, 0, 8, 2, 17, 1);
		SetColor(12, 0);
		setcur(15, 1); cout << "------------";
		setcur(17, 2); cout << "You fail";
	}
	
	setcur(15, 3); cout << "------------";
	
	//printing computer's field
	for(int i = 0; i < map_lenght; i++)
	{ 
		for(int j = 0; j < map_lenght; j++)
		{
			if(computerField_vector[i][j] == 'b') field_printer('b', 15, 7, 1, 1, j + 29, i + 1);
			if(computerField_vector[i][j] == 's') field_printer('s', 9, 1, 1, 1, j + 29, i + 1);
			if(computerField_vector[i][j] == 'm') field_printer('m', 11, 1, 1, 1, j + 29, i + 1);
			if(computerField_vector[i][j] == 'w') field_printer('w', 15, 14, 1, 1, j + 29, i + 1);
			if(computerField_vector[i][j] == 'd') field_printer('d', 15, 12, 1, 1, j + 29, i + 1);
			if(computerField_vector[i][j] == 'f') field_printer('f', 8, 8, 1, 1, j + 29, i + 1);
		}
	}
}

