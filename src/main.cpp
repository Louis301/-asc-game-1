#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <string>

using 
  std::vector, 
  std::string, 
	std::cout,
	std::endl;


const int map_lenght = 12; 
int computerScore = 0;
int gamerScore = 0;
bool motion {false};
vector<string> gamerField_vector;
vector<string> computerField_vector;


struct cursorPosition {
	int x{}, y{};
};

enum EKey {
	EK_C = 99,
	EK_Esc = 27,
  EK_Enter = 13,
  EK_H = 104,
	EK_Up = 72,
	EK_Down = 80,
	EK_Left = 75,
	EK_Right = 77
};

enum EColor {
  EC_Yellow = 14, 
	EC_Black = 0,
	EC_White = 15,
	EC_Gray = 12
};


void inicFields();
char checkingCell(vector<string> Vector, cursorPosition gamer);
void boatFrame(vector<string> &field, cursorPosition player);
void gameCicle();
void printerFirstCondition();
void scorePrinter();
void setcur(int x, int y);
void SetColor(int text, int bg);
void cursorHide();
void field_printer(char simbol, int color_text, int color_bg, int dimension_x, int dimension_y, int offset_x, int offset_y);

//----------------------------------------------------------------------------------------------------
void inicFields()
{
	srand(time(NULL));
	char field[map_lenght][map_lenght] = {0};
	cursorPosition leftUp;
	cursorPosition rightDown;
	cursorPosition gamer;
	
	//---------------------------------first filling of the fields_BEGIN
	for(int i = 0; i < map_lenght; i++)
	{
		string s = "";
		for(int j = 0; j < map_lenght; j++)
		{
			if(i == 0 || j == 0 || i == map_lenght - 1 || j == map_lenght - 1) field[i][j] = 'f';
			else
			field[i][j] = 's';		
			s += field[i][j];
		}	
		gamerField_vector.push_back(s);
		computerField_vector.push_back(s);
	}
	//---------------------------------first filling of the fields_END
	
	//---------------------------------filling field of user_BEGIN
	int boatNum = 4;
	int numBoats = 0; 
	
	//filling cicle (for user)
	do
	{
		METKA_1: 
		int quantityUsed_dir = 0;
		int quantityUsed_frameCheck = 0;
		gamer.x = rand() % 10 + 1;
		gamer.y = rand() % 10 + 1;
		
		if(gamerField_vector[gamer.y][gamer.x] == 'b' || gamerField_vector[gamer.y][gamer.x] == 'f')
		while(gamerField_vector[gamer.y][gamer.x] == 'b' || gamerField_vector[gamer.y][gamer.x] == 'f')
		{
			gamer.x = rand() % 10 + 1;
			gamer.y = rand() % 10 + 1;
		}
		
		METKA_2: 
		int dir = rand() % 4;
		
		if(dir == 0) // left
		{
			if(gamer.x - boatNum >= 0)
			{
				leftUp.x = gamer.x - boatNum;
				leftUp.y = gamer.y - 1; 
				rightDown.x = gamer.x + 1;
				rightDown.y = gamer.y + 1;
			}
			else
			{
				quantityUsed_dir++;
				if(quantityUsed_dir == 4) goto METKA_1;
				else 
					goto METKA_2;
			}
		}
		if(dir == 1) //up
		{
			if(gamer.y - boatNum >= 0)
			{
				leftUp.x = gamer.x - 1;
				leftUp.y = gamer.y - boatNum; 
				rightDown.x = gamer.x + 1;
				rightDown.y = gamer.y + 1;
			}
			else
			{
				quantityUsed_dir++;
				if(quantityUsed_dir == 4) goto METKA_1;
				else 
					goto METKA_2;
			}
		}
		if(dir == 2) //right
		{
			if(gamer.x + boatNum < map_lenght)
			{
				leftUp.x = gamer.x - 1;
				leftUp.y = gamer.y - 1; 
				rightDown.x = gamer.x + boatNum;
				rightDown.y = gamer.y + 1;
			}
			else
			{
				quantityUsed_dir++;
				if(quantityUsed_dir == 4) goto METKA_1;
				else 
					goto METKA_2;
			}
		}
		if(dir == 3) //down
		{
			if(gamer.y + boatNum < map_lenght)
			{
				leftUp.x = gamer.x - 1;
				leftUp.y = gamer.y - 1; 
				rightDown.x = gamer.x + 1;
				rightDown.y = gamer.y + boatNum;
			}
			else
			{
				quantityUsed_dir++;
				if(quantityUsed_dir == 4) goto METKA_1;
				else 
					goto METKA_2;
			}
		}
		
		bool emptyFrame = true;
    for(int i = leftUp.y; i <= rightDown.y; i++)
		{
			for(int j = leftUp.x; j <= rightDown.x; j++)
			{
				if(i == leftUp.y || j == leftUp.x || i == rightDown.y || j == rightDown.x) 
				{
					if(gamerField_vector[i][j] == 'b') 
					{
						emptyFrame = false;
						break;
					}
				}
			}
			if(!emptyFrame) 
			{
				quantityUsed_frameCheck++;
				if(quantityUsed_frameCheck == 4) 
				  goto METKA_1;
				else 
				  goto METKA_2;
				break;
			}
		}
		if(emptyFrame)
		{
			//setting of the ship
			for(int i = leftUp.y + 1; i < rightDown.y; i++)
			{
				for(int j = leftUp.x + 1; j < rightDown.x; j++)
					gamerField_vector[i][j] = 'b';
			}
			
			numBoats++;
			
			if(numBoats == 1 || numBoats == 2) boatNum = 3;
			if(numBoats == 3 || numBoats == 4 || numBoats == 5) boatNum = 2;
			if(numBoats == 6 || numBoats == 7 || numBoats == 8 || numBoats == 9) boatNum = 1;
			
			quantityUsed_frameCheck = 0;
		}
	}
	while(numBoats != 10);
	//---------------------------------filling field of user_END
	
	//---------------------------------filling field of computer_BEGIN
	boatNum = 4;
	numBoats = 0; 
	
	//filling cicle (for computer)
	do
	{
		METKA_3: 
		int quantityUsed_dir = 0;
		int quantityUsed_frameCheck = 0;
		gamer.x = rand() % 10 + 1;
		gamer.y = rand() % 10 + 1;
		
		if(computerField_vector[gamer.y][gamer.x] == 'b' || computerField_vector[gamer.y][gamer.x] == 'f')
		while(computerField_vector[gamer.y][gamer.x] == 'b' || computerField_vector[gamer.y][gamer.x] == 'f')
		{
			gamer.x = rand() % 10 + 1;
			gamer.y = rand() % 10 + 1;
		}
		
		METKA_4: 
		int dir = rand() % 4;
		
		if(dir == 0) // left
		{
			if(gamer.x - boatNum >= 0)
			{
				leftUp.x = gamer.x - boatNum;
				leftUp.y = gamer.y - 1; 
				rightDown.x = gamer.x + 1;
				rightDown.y = gamer.y + 1;
			}
			else
			{
				quantityUsed_dir++;
				if(quantityUsed_dir == 4) 
				  goto METKA_3;
				else 
					goto METKA_4;
			}
		}
		if(dir == 1) //up
		{
			if(gamer.y - boatNum >= 0)
			{
				leftUp.x = gamer.x - 1;
				leftUp.y = gamer.y - boatNum; 
				rightDown.x = gamer.x + 1;
				rightDown.y = gamer.y + 1;
			}
			else
			{
				quantityUsed_dir++;
				if(quantityUsed_dir == 4) goto METKA_3;
				else 
				
					goto METKA_4;
				
			}
		}
		if(dir == 2) //right
		{
			if(gamer.x + boatNum < map_lenght)
			{
				leftUp.x = gamer.x - 1;
				leftUp.y = gamer.y - 1; 
				rightDown.x = gamer.x + boatNum;
				rightDown.y = gamer.y + 1;
			}
			else
			{
				quantityUsed_dir++;
				if(quantityUsed_dir == 4) goto METKA_3;
				else 
				
					goto METKA_4;
				
			}
		}
		if(dir == 3) //down
		{
			if(gamer.y + boatNum < map_lenght)
			{
				leftUp.x = gamer.x - 1;
				leftUp.y = gamer.y - 1; 
				rightDown.x = gamer.x + 1;
				rightDown.y = gamer.y + boatNum;
			}
			else
			{
				quantityUsed_dir++;
				if(quantityUsed_dir == 4) goto METKA_3;
				else 
				
					goto METKA_4;
				
			}
		}
		
		bool emptyFrame = true;
		for(int i = leftUp.y; i <= rightDown.y; i++)
		{
			for(int j = leftUp.x; j <= rightDown.x; j++)
			{
				if(i == leftUp.y || j == leftUp.x || i == rightDown.y || j == rightDown.x) 
				{
					if(computerField_vector[i][j] == 'b') 
					{
						emptyFrame = false;
						break;
					}
				}
			}
			if(!emptyFrame) 
			{
				quantityUsed_frameCheck++;
				if(quantityUsed_frameCheck == 4) goto METKA_3;
				else goto METKA_4;
				break;
			}
		}
		if(emptyFrame)
		{
			//setting of the ship
			for(int i = leftUp.y + 1; i < rightDown.y; i++)
			
				for(int j = leftUp.x + 1; j < rightDown.x; j++)
				
					computerField_vector[i][j] = 'b';
				
			
			
			numBoats++;
			
			if(numBoats == 1 || numBoats == 2) boatNum = 3;
			if(numBoats == 3 || numBoats == 4 || numBoats == 5) boatNum = 2;
			if(numBoats == 6 || numBoats == 7 || numBoats == 8 || numBoats == 9) boatNum = 1;
			
			quantityUsed_frameCheck = 0;
		}
	}
	while(numBoats != 10);
	//---------------------------------filling field of computer_END	
}

//----------------------------------------------------------------------------------------------------
char checkingCell(vector<string> Vector, cursorPosition gamer)
{
	cursorPosition check_cursor;
	int boatCellQuality = 0;
        	    
	if(Vector[gamer.y][gamer.x] == 'b')
	{
		check_cursor.x = gamer.x; //up
		check_cursor.y = gamer.y;
		while(Vector[--check_cursor.y][check_cursor.x] == 'b' || Vector[check_cursor.y][check_cursor.x] == 'w') 
			if(Vector[check_cursor.y][check_cursor.x] == 'b') boatCellQuality++;				
		
		check_cursor.x = gamer.x; //down
		check_cursor.y = gamer.y;
		while(Vector[++check_cursor.y][check_cursor.x] == 'b' || Vector[check_cursor.y][check_cursor.x] == 'w')     
			if(Vector[check_cursor.y][check_cursor.x] == 'b') boatCellQuality++;
					
		check_cursor.x = gamer.x; //right
		check_cursor.y = gamer.y;
		while(Vector[check_cursor.y][++check_cursor.x] == 'b' || Vector[check_cursor.y][check_cursor.x] == 'w')
			if(Vector[check_cursor.y][check_cursor.x] == 'b') boatCellQuality++;
					
		check_cursor.x = gamer.x; //left
		check_cursor.y = gamer.y;
		while(Vector[check_cursor.y][--check_cursor.x] == 'b' || Vector[check_cursor.y][check_cursor.x] == 'w')
			if(Vector[check_cursor.y][check_cursor.x] == 'b') boatCellQuality++;
	
		if(boatCellQuality == 0) 
		{
			// Beep(1200, 100);
			if(motion == 0) gamerScore++;
			if(motion == 1) computerScore++;
			return 'd';
		}
    else 
		{
			// Beep(1400, 100);
			return 'w';
		}
  }
            	
  if(Vector[gamer.y][gamer.x] == 's')
  {
    // Beep(900, 100);
    if(motion == 0) 
		{ 
			motion = 1;
			return 'm';
		}
    if(motion == 1) 
		{
			motion = 0;
			return 'm';
		}
	}

	else 
    return Vector[gamer.y][gamer.x];
}
	
//----------------------------------------------------------------------------------------------------
void boatFrame(vector<string> &field, cursorPosition player)
{
	cursorPosition frame_leftUp;
	cursorPosition frame_rightDown;
	
	if(field[player.y - 1][player.x] == 'w' || field[player.y + 1][player.x] == 'w') //vertical
	{
		//up
		while(field[--player.y][player.x] != 's' && field[player.y][player.x] != 'm' && field[player.y][player.x] != 'f') {}
		frame_leftUp.x = player.x - 1;
		frame_leftUp.y = player.y;
	
		//down
		while(field[++player.y][player.x] != 's' && field[player.y][player.x] != 'm' && field[player.y][player.x] != 'f') {} 
		frame_rightDown.x = player.x + 1;
		frame_rightDown.y = player.y;
		
		goto frameForming;
	}

	if(field[player.y][player.x - 1] == 'w' || field[player.y][player.x + 1] == 'w') //gorizontal
	{
		//left
		while(field[player.y][--player.x] != 's' && field[player.y][player.x] != 'm' && field[player.y][player.x] != 'f') {} 
		frame_leftUp.x = player.x;
		frame_leftUp.y = player.y - 1;
	
		//right
		while(field[player.y][++player.x] != 's' && field[player.y][player.x] != 'm' && field[player.y][player.x] != 'f') {}
		frame_rightDown.x = player.x;
		frame_rightDown.y = player.y + 1;
		
		goto frameForming;
	}
	else //around
	{
		frame_leftUp.x = player.x - 1;
		frame_leftUp.y = player.y - 1;
		frame_rightDown.x = player.x + 1;
		frame_rightDown.y = player.y + 1;
	}
	
	frameForming:
	for(int i = frame_leftUp.y; i <= frame_rightDown.y; i++)
	{
		for(int j = frame_leftUp.x; j <= frame_rightDown.x; j++)
		{
			if(field[i][j] == 's') 
			{
				field[i][j] = 'm';
				if(motion == 1) field_printer('m', 11, 1, 1, 1, j + 1, i + 1);
				if(motion == 0) field_printer('m', 11, 1, 1, 1, j + 29, i + 1);
			}
		}
	}	
}	

//----------------------------------------------------------------------------------------------------
void gameCicle()
{
	system("cls");
	inicFields(); //inicialisation fields
	printerFirstCondition(); //printing first condition of monitor
	
	srand(time(NULL));
	
	int value;
	cursorPosition gamer;
	cursorPosition computer;
	
	motion = rand() % 2; //0 - gamer, 1 - computer
	gamer.x = 1;
	gamer.y = 1;
	computer.x = rand() % 10 + 1;
	computer.y = rand() % 10 + 1;

	//intel vars
	int intelGenVariant;
	cursorPosition compMemory;
	vector<int> choiceIntel_x;
	vector<int> choiceIntel_y;
	bool firstHit = 1;
	
	field_printer('s', 15, 0, 1, 1, 30, 2);
	
	//game cicle
	do
  {	
    cursorHide();
		//--------------------------motion of gamer_BEGIN
		if(motion == 0)
		{			
			//printer player 
			field_printer(' ', 0, 0, 8, 1, 17, 1);
			SetColor(EC_Yellow, EC_Black);
			setcur(19, 1); cout << "User";
			setcur(18, 2); cout << "motion";
		
			//---------------------------keyboard inputs processing_BEGIN
			value = getch();
		
			//reprint_TheGamerCursorSimbol
			if(computerField_vector[gamer.y][gamer.x] == 's' || computerField_vector[gamer.y][gamer.x] == 'b') field_printer('s', 9, 1, 1, 1, gamer.x  + 29, gamer.y + 1);
			if(computerField_vector[gamer.y][gamer.x] == 'm') field_printer('m', 11, 1, 1, 1, gamer.x  + 29, gamer.y + 1); 
			if(computerField_vector[gamer.y][gamer.x] == 'w') field_printer('w', 15, 14, 1, 1, gamer.x  + 29, gamer.y + 1); 
			if(computerField_vector[gamer.y][gamer.x] == 'd') field_printer('d', 15, 12, 1, 1, gamer.x  + 29, gamer.y + 1); 
		
	    switch(value)
			{
				case 224: break;

				case EK_Up: if(gamer.y > 1) gamer.y--; break;  // up
				case EK_Down: if(gamer.y < map_lenght - 2) gamer.y++; break;  // down
				case EK_Left: if(gamer.x > 1) gamer.x--; break;  // left
				case EK_Right: if(gamer.x < map_lenght - 2) gamer.x++; break;  // right
			
				//checking cell condition
				case EK_Enter: 
				{
					SetColor(EC_White, EC_Black);
	        computerField_vector[gamer.y][gamer.x] = checkingCell(computerField_vector, gamer); 
	        if(computerField_vector[gamer.y][gamer.x] == 'd')
		    		boatFrame(computerField_vector, gamer);
					SetColor(EC_White, EC_Black);
					setcur(23, 7); 
					cout << gamerScore;
					break;
				}
				
				case EK_H:
				{
					int value2;
					field_printer(' ', 0, 0, 40, 12, 1, 1);	
					setcur(1, 1); SetColor(EC_Yellow, EC_Black); cout << "Space"; SetColor(EC_White, EC_Black); cout << " - hit the cage";
					setcur(1, 2); SetColor(EC_Yellow, EC_Black); cout << "Arrows"; SetColor(EC_White, EC_Black); cout << " - movement on the field";
					setcur(1, 3); SetColor(EC_Yellow, EC_Black); cout << "Esc"; SetColor(EC_White, EC_Black); cout << " - exit from game";
					setcur(1, 5); SetColor(EC_Yellow, EC_Black); cout << "h"; SetColor(EC_White, EC_Black); cout << " - return to the game";
					value2 = getch();
					while(value2 != EK_H)
						value2 = getch();
					setcur(0, 0);
					printerFirstCondition();
					break;
				}
	    }
	    	
	    //printerTheGamerCursorSimbol
			if(computerField_vector[gamer.y][gamer.x] == 's' || computerField_vector[gamer.y][gamer.x] == 'b') 
			  field_printer('s', 15, 0, 1, 1, gamer.x  + 29, gamer.y + 1);
		  else 
			  field_printer(computerField_vector[gamer.y][gamer.x], 15, 0, 1, 1, gamer.x  + 29, gamer.y + 1);
	    //---------------------------keyboard inputs processing_END
	    	
	    if(gamerScore == 10 || computerScore == 10) 
			  break;
		}
		//--------------------------motion of gamer_END

    //--------------------------motion of computer_BEGIN
    if(motion == 1)
  	{
			//printer player
			SetColor(EC_Gray, EC_Black);
			setcur(17, 1); cout << "Computer";
			setcur(18, 2); cout << "motion";
			Sleep(1200);

			//checking cell condition
			gamerField_vector[computer.y][computer.x] = checkingCell(gamerField_vector, computer);

			//printer Score
			SetColor(EC_White, EC_Black);
			setcur(25, 6); 
      cout << computerScore;

		  //printer TheComputerCursorSimbol
			if(gamerField_vector[computer.y][computer.x] == 'm') 
			  field_printer('m', 11, 1, 1, 1, computer.x + 1, computer.y + 1);
			if(gamerField_vector[computer.y][computer.x] == 'w') 
			  field_printer('w', 15, 14, 1, 1, computer.x + 1, computer.y + 1);
			if(gamerField_vector[computer.y][computer.x] == 'd') 
			  field_printer('d', 15, 12, 1, 1, computer.x + 1, computer.y + 1);
			
      //-------------------------------------inicializating intellect generation variant_BEGIN
			if(gamerField_vector[computer.y][computer.x] == 'w') 
      {
        if(gamerField_vector[computer.y - 1][computer.x] == 'w' || gamerField_vector[computer.y + 1][computer.x] == 'w') //vertical
				{
					intelGenVariant = 2; 
					goto metka;
				}
        if(gamerField_vector[computer.y][computer.x - 1] == 'w' || gamerField_vector[computer.y][computer.x + 1] == 'w') //gorizontal
				{
					intelGenVariant = 3; 
					goto metka;
				}
        else //around
        {
					intelGenVariant = 1; 
					goto metka;
				}
      }

			if(gamerField_vector[computer.y][computer.x] == 'm' || gamerField_vector[computer.y][computer.x] == 'f')
			{
				if(gamerField_vector[computer.y][computer.x - 1] != 'w' 
					&& gamerField_vector[computer.y - 1][computer.x] != 'w'
					&& gamerField_vector[computer.y][computer.x + 1] != 'w'
					&& gamerField_vector[computer.y + 1][computer.x] != 'w') intelGenVariant = 4;
				else
				{
					computer.x = compMemory.x;
					computer.y = compMemory.y;
				}
			}

			if(gamerField_vector[computer.y][computer.x] == 'd') 
			{
				intelGenVariant = 4;
				firstHit = 1;
				boatFrame(gamerField_vector, computer);
			}
			//-------------------------------------inicializating intellect generation variant_END
			
			metka:
			//-------------------------------------intel generating coordinats_BEGIN
			if(intelGenVariant == 1) //around generating coordinats
			{
				//memoring central of boat
				if(firstHit)
				{
					compMemory.x = computer.x;
					compMemory.y = computer.y;
				}

				//creating a circular intelligence selection 
				if(gamerField_vector[computer.y][computer.x - 1] != 'f' 
					&& gamerField_vector[computer.y][computer.x - 1] != 'm' 
					&& gamerField_vector[computer.y][computer.x - 1] != 'w') //left
				{
					choiceIntel_x.push_back(computer.x - 1);
					choiceIntel_y.push_back(computer.y);
				}

				if(gamerField_vector[computer.y - 1][computer.x] != 'f' 
					&& gamerField_vector[computer.y - 1][computer.x] != 'm' 
					&& gamerField_vector[computer.y - 1][computer.x] != 'w') //up
				{
					choiceIntel_x.push_back(computer.x);
					choiceIntel_y.push_back(computer.y - 1);
				}
				
				if(gamerField_vector[computer.y][computer.x + 1] != 'f' 
					&& gamerField_vector[computer.y][computer.x + 1] != 'm' 
					&& gamerField_vector[computer.y][computer.x + 1] != 'w') //right
				{
					choiceIntel_x.push_back(computer.x + 1);
					choiceIntel_y.push_back(computer.y);
				}

				if(gamerField_vector[computer.y + 1][computer.x] != 'f' 
					&& gamerField_vector[computer.y + 1][computer.x] != 'm' 
					&& gamerField_vector[computer.y + 1][computer.x] != 'w') //down
				{
					choiceIntel_x.push_back(computer.x);
					choiceIntel_y.push_back(computer.y + 1);
				}
				
				//generation coordinats
				int numHitCell;
				numHitCell = rand() % choiceIntel_x.size();
				computer.x = choiceIntel_x[numHitCell];
				computer.y = choiceIntel_y[numHitCell];
				choiceIntel_x.clear();
				choiceIntel_y.clear();
				firstHit = 0;
			}

			if(intelGenVariant == 2) //vertical generating coordinats
			{
				if(gamerField_vector[computer.y + 1][computer.x] == 'w') computer.y--; //up hitting
				if(gamerField_vector[computer.y - 1][computer.x] == 'w') computer.y++; //down hitting
			}

			if(intelGenVariant == 3) //gorizontal generating coordinats
			{
				if(gamerField_vector[computer.y][computer.x + 1] == 'w') computer.x--; //left hitting
				if(gamerField_vector[computer.y][computer.x - 1] == 'w') computer.x++; //right hitting
			}

			if(intelGenVariant == 4) //random generating coordinats
			{
				if(gamerScore == 10 || computerScore == 10) break;  	
				while(gamerField_vector[computer.y][computer.x] != 's' && gamerField_vector[computer.y][computer.x] != 'b')
				{
					computer.x = rand() % 10 + 1;
					computer.y = rand() % 10 + 1;
				}
			}
			//-------------------------------------intel generating coordinats_END
		}
		//--------------------------motion of computer_END
	}
	while(value != EK_Esc);
	
	scorePrinter(); //print winner
	computerScore = 0;
	gamerScore = 0;
	gamerField_vector.clear();
	computerField_vector.clear();
}

//----------------------------------------------------------------------------------------------------
void setcur(int x, int y) 
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

//----------------------------------------------------------------------------------------------------
void SetColor(int text, int bg) 
{ 
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

//----------------------------------------------------------------------------------------------------
void cursorHide()
{
	CONSOLE_CURSOR_INFO curs = {0};
	curs.dwSize = sizeof(curs);
	curs.bVisible = FALSE;
	::SetConsoleCursorInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &curs);
}

//----------------------------------------------------------------------------------------------------
void field_printer(char simbol, int color_text, int color_bg, int dimension_x, int dimension_y, int offset_x, int offset_y)
{
	SetColor(color_text, color_bg);
	for(int i = 0; i < dimension_y; i++) 
  {
		for(int j = 0; j < dimension_x; j++)
		{
			setcur(j + offset_x, i + offset_y);
			cout << simbol;
		}
		cout << endl;
	}
}

//----------------------------------------------------------------------------------------------------
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

	SetColor(EColor::EC_White, 0);	
	setcur(18, 4); cout << "Score";
	setcur(15, 5); cout << "------------";
	setcur(15, 6); cout << "computer: ";
	setcur(17, 7); cout << "user: ";
	
	setcur(17, 9); 
	SetColor(EColor::EC_Yellow, 0); 
	cout << "h"; 
	SetColor(EColor::EC_White, 0); 
	cout << " - help";
	
	//printer Scores of gamers
	SetColor(EColor::EC_White, 0);
	setcur(25, 6); 
	cout << computerScore;
	
	SetColor(EColor::EC_White, 0);
	setcur(23, 7); 
	cout << gamerScore;
}

//----------------------------------------------------------------------------------------------------
void scorePrinter()
{	
	field_printer(' ', 0, 0, 8, 2, 17, 1);

	//printer gamer score
	if(gamerScore == 10) 
	{
		SetColor(EColor::EC_Yellow, 0);
		setcur(15, 1); cout << "------------";
		setcur(17, 2); cout << "You win!";
	}
		
	//printer computer score
	if(computerScore == 10) 
	{
		field_printer(' ', 0, 0, 8, 2, 17, 1);
		SetColor(EColor::EC_Gray, 0);
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

//====================================================================================================
int main()
{
	playAgain:
	gameCicle(); //game process
	 
	setcur(14, 10); 
	SetColor(EColor::EC_Yellow, 0); 
	cout << "c"; 

	SetColor(EColor::EC_White, 0); 
	cout << " - play again";
	
	field_printer(' ', 0, 0, 11, 1, 14, 9);
	
	againInput:
	switch(getch())
	{
		case EK_C: 
			goto playAgain; 
			break;
		case EK_Esc: 
			SetColor(EColor::EC_White, 0); 
			setcur(0, map_lenght + 2);
			Sleep(1000);
    		return 0;
		default: 
			goto againInput; 
			break;
    }
}
