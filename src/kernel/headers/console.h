#pragma once

#include <stdint.h>
#include <stddef.h>

//terminal size
const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

//video buffer
struct vbuf{
	uint8_t _char;
	uint8_t color;
};

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

//terminal theme - i mean it's colors so i guess i can call it a theme?
static uint8_t c_THEME = BLACK << 4 | WHITE; //b01111

void c_set_theme(uint8_t fg, uint8_t bg);
void c_print(char* str);
void c_clear_rows(int lines);

void c_scroll_up(uint8_t num_lines, struct vbuf** off_screen);
void c_scroll_down(uint8_t num_lines, struct vbuf** off_screen);
void c_set_cursor(int row, int col);

