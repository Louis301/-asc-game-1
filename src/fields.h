#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

class cursorPosition
{
	public:
		int x, y;
};

const int map_lenght = 12; 
vector<string> gamerField_vector;
vector<string> computerField_vector;

//inicialization of fields
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
				{
					goto METKA_2;
				}
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
				{
					goto METKA_2;
				}
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
				{
					goto METKA_2;
				}
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
				{
					goto METKA_2;
				}
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
						if(quantityUsed_frameCheck == 4) goto METKA_1;
						else goto METKA_2;
						break;
					}
				}
				if(emptyFrame)
				{
					//setting of the ship
					for(int i = leftUp.y + 1; i < rightDown.y; i++)
					{
						for(int j = leftUp.x + 1; j < rightDown.x; j++)
						{
							gamerField_vector[i][j] = 'b';
						}
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
				if(quantityUsed_dir == 4) goto METKA_3;
				else 
				{
					goto METKA_4;
				}
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
				{
					goto METKA_4;
				}
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
				{
					goto METKA_4;
				}
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
				{
					goto METKA_4;
				}
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
					{
						for(int j = leftUp.x + 1; j < rightDown.x; j++)
						{
							computerField_vector[i][j] = 'b';
						}
					}
					
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

