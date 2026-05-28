#include <conio.h>
#include "others.h"

bool motion;

//checking cell condition
char checkingCell(vector<string> Vector, cursorPosition gamer)
{
	cursorPosition check_cursor; //checking cursor
    int boatCellQuality = 0;
        	    
    if(Vector[gamer.y][gamer.x] == 'b') //cell == 'b'
    {
		check_cursor.x = gamer.x; //up
    	check_cursor.y = gamer.y;
  	    while(Vector[--check_cursor.y][check_cursor.x] == 'b' || Vector[check_cursor.y][check_cursor.x] == 'w') 
		{
  	    	if(Vector[check_cursor.y][check_cursor.x] == 'b') boatCellQuality++;				
		}
  	    			
  	    check_cursor.x = gamer.x; //down
        check_cursor.y = gamer.y;
  	    while(Vector[++check_cursor.y][check_cursor.x] == 'b' || Vector[check_cursor.y][check_cursor.x] == 'w') 
  	    {
  	    	if(Vector[check_cursor.y][check_cursor.x] == 'b') boatCellQuality++;					
		}
  	    			
  	    check_cursor.x = gamer.x; //right
        check_cursor.y = gamer.y;
  	    while(Vector[check_cursor.y][++check_cursor.x] == 'b' || Vector[check_cursor.y][check_cursor.x] == 'w')
  	    {
  	    	if(Vector[check_cursor.y][check_cursor.x] == 'b') boatCellQuality++;					
		}
  	    			
  	    check_cursor.x = gamer.x; //left
        check_cursor.y = gamer.y;
  	    while(Vector[check_cursor.y][--check_cursor.x] == 'b' || Vector[check_cursor.y][check_cursor.x] == 'w')
  	    {
  	    	if(Vector[check_cursor.y][check_cursor.x] == 'b') boatCellQuality++;					
		}
  	    			
  	    if(boatCellQuality == 0) 
		{
			Beep(1200, 100);
			if(motion == 0) gamerScore++;
			if(motion == 1) computerScore++;
			return 'd';
		}
        else 
		{
			Beep(1400, 100);
			return 'w';
		}
        
        }
            	
        if(Vector[gamer.y][gamer.x] == 's') //cell == 's'
        {
        	Beep(900, 100);
        	
            //gamer use
            if(motion == 0) 
			{ 
            	motion = 1;
            	return 'm';
			}
					
			//computer use
            if(motion == 1) 
			{
            	motion = 0;
            	return 'm';
			}
		}
				
		else return Vector[gamer.y][gamer.x];		
}
	
//frame around boat
void boatFrame(vector<string> &field, cursorPosition player)
{
	cursorPosition frame_leftUp;
	cursorPosition frame_rightDown;
	
		if(field[player.y - 1][player.x] == 'w' || field[player.y + 1][player.x] == 'w') //vertical
		{
			//up
			while(field[--player.y][player.x] != 's' 
			 && field[player.y][player.x] != 'm'
			 && field[player.y][player.x] != 'f') {}
			frame_leftUp.x = player.x - 1;
			frame_leftUp.y = player.y;
		
			//down
			while(field[++player.y][player.x] != 's' 
			 && field[player.y][player.x] != 'm'
			 && field[player.y][player.x] != 'f') {} 
			frame_rightDown.x = player.x + 1;
			frame_rightDown.y = player.y;
			
			goto frameForming;
		}
		if(field[player.y][player.x - 1] == 'w' || field[player.y][player.x + 1] == 'w') //gorizontal
		{
			//left
			while(field[player.y][--player.x] != 's' 
			 && field[player.y][player.x] != 'm'
			 && field[player.y][player.x] != 'f') {} 
			frame_leftUp.x = player.x;
			frame_leftUp.y = player.y - 1;
		
			//right
			while(field[player.y][++player.x] != 's' 
			 && field[player.y][player.x] != 'm'
			 && field[player.y][player.x] != 'f') {}
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

//game process
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
			SetColor(14, 0);
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
			
				case 72: if(gamer.y > 1) gamer.y--; break;
            	case 80: if(gamer.y < map_lenght - 2) gamer.y++; break;
            	case 75: if(gamer.x > 1) gamer.x--; break;
            	case 77: if(gamer.x < map_lenght - 2) gamer.x++; break;
            
            	//checking cell condition
            	case 32: 
				{
					SetColor(15, 0);
	            	computerField_vector[gamer.y][gamer.x] = checkingCell(computerField_vector, gamer); 
	            	
	            	if(computerField_vector[gamer.y][gamer.x] == 'd')
		    		{
		    			boatFrame(computerField_vector, gamer);
					}
					
	            	//printer Score
        	        SetColor(15, 0);
			        setcur(23, 7); 
			        cout << gamerScore;
					break;
				}
				
				case 104:
				{
					int value2;
					field_printer(' ', 0, 0, 40, 12, 1, 1);	
					
					setcur(1, 1); SetColor(14, 0); cout << "Space"; SetColor(15, 0); cout << " - hit the cage";
					setcur(1, 2); SetColor(14, 0); cout << "Arrows"; SetColor(15, 0); cout << " - movement on the field";
					setcur(1, 3); SetColor(14, 0); cout << "Esc"; SetColor(15, 0); cout << " - exit from game";
					setcur(1, 5); SetColor(14, 0); cout << "h"; SetColor(15, 0); cout << " - return to the game";
					
					value2 = getch();
					
					while(value2 != 104)
					{
						value2 = getch();
					}
					
					setcur(0, 0);
					printerFirstCondition();
					break;
				}
	    	}
	    	
	    	//printerTheGamerCursorSimbol
			if(computerField_vector[gamer.y][gamer.x] == 's' || computerField_vector[gamer.y][gamer.x] == 'b') field_printer('s', 15, 0, 1, 1, gamer.x  + 29, gamer.y + 1);
			else 
			field_printer(computerField_vector[gamer.y][gamer.x], 15, 0, 1, 1, gamer.x  + 29, gamer.y + 1);
	    	//---------------------------keyboard inputs processing_END
	    	
	    	if(gamerScore == 10 || computerScore == 10) break;
		}
		//--------------------------motion of gamer_END


        //--------------------------motion of computer_BEGIN
        if(motion == 1)
        {
        	//printer player
        	SetColor(12, 0);
			setcur(17, 1); cout << "Computer";
			setcur(18, 2); cout << "motion";
			Sleep(1200);
		
		    //checking cell condition
		    gamerField_vector[computer.y][computer.x] = checkingCell(gamerField_vector, computer);
		    
		    //printer Score
        	SetColor(15, 0);
        	setcur(25, 6); 
			cout << computerScore;
		    
		    //printer TheComputerCursorSimbol
			if(gamerField_vector[computer.y][computer.x] == 'm') field_printer('m', 11, 1, 1, 1, computer.x + 1, computer.y + 1);
			if(gamerField_vector[computer.y][computer.x] == 'w') field_printer('w', 15, 14, 1, 1, computer.x + 1, computer.y + 1);
			if(gamerField_vector[computer.y][computer.x] == 'd') field_printer('d', 15, 12, 1, 1, computer.x + 1, computer.y + 1);
			
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
	while(value != 27);
	
	scorePrinter(); //print winner
	computerScore = 0;
	gamerScore = 0;
	gamerField_vector.clear();
	computerField_vector.clear();
}

