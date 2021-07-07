#pragma once

#include <stdint.h>
#include <stddef.h>

//terminal size
const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

//terminal theme - i mean it's colors so i guess i can call it a theme?
uint8_t t_THEME = BLACK << 4 | WHITE; //b01111

enum{
	BLACK,			//0
	BLUE,			//1	
	GREEN,			//2
	CYAN,			//3
	RED,			//4
	MAGENTA,		//5
	BROWN,			//6
	LIGHT_GRAY,		//7
	DARK_GRAY,		//8
	LIGHT_BLUE,		//9
	LIGHT_GREEN,	//10
	LIGHT_CYAN,		//11
	LIGHT_RED,		//12
	PINK,			//13
	YELLOW,			//14
	WHITE			//15
};

void t_color(uint8_t fg, uint8_t bg);

void t_print(char* str);
void t_clear_rows(int lines);

#define t_UP	-1
#define t_DOWN	 1
void t_scroll(int direction, int lines);


