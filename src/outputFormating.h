#include <iostream>
#include <windows.h>

using namespace std;

//setting the cursor to the x y position 
void setcur(int x, int y) 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

//changing the text color
void SetColor(int text, int bg) 
{ 
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

//cursor hiding
void cursorHide()
{
	CONSOLE_CURSOR_INFO curs = {0};
   		curs.dwSize = sizeof(curs);
  		curs.bVisible = FALSE;
   		::SetConsoleCursorInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &curs);
}

//printing objects
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
