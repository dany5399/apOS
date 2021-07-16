#include "console.h"

struct vbuf* V_BUF = (struct vbuf*) 0xb8000; //video memory location

static uint8_t c_CURR_ROW;
static uint8_t c_CURR_COL;

void c_clear_rows(int lines){

	size_t row = 0;
	if(lines < 0){
		row = NUM_ROWS + lines; //delete from bottom
		lines = NUM_ROWS;
	}

	struct vbuf EMPTY_CHAR = (struct vbuf) {_char: ' ', color: c_THEME};
	for(; row < lines; row++){
		//if only we had memcpy
		for(size_t col = 0; col < NUM_COLS; col++){
			V_BUF[col + NUM_COLS * row] = EMPTY_CHAR;
		}
	}
}

void c_print(char* str){
	
	for(int i = 0; i < NUM_COLS; i++){
		switch(str[i]){
		case '\n':
			if(c_CURR_ROW == NUM_ROWS-1){
				c_scroll_up(1, NULL);
				c_clear_rows(-1);	//clear last line
			}else{
				c_CURR_ROW++;
			}
			c_CURR_COL = 0;
			continue;
		case '\0': 
			return;
		default:
			struct vbuf cbuf = (struct vbuf) {_char: str[i], color: c_THEME};
			V_BUF[c_CURR_COL + NUM_COLS * c_CURR_ROW] = cbuf;
		}
		c_CURR_COL++;
	}
}

void c_scroll_up(uint8_t num_lines, struct vbuf** off_screen){
	for(int i = num_lines; i < NUM_ROWS; i++){
		for(int j = 0; j < NUM_COLS; j++){
			V_BUF[j + NUM_COLS * (i-num_lines)] = V_BUF[j + NUM_COLS * i];
		}
	}
}

void c_scroll_down(uint8_t num_lines, struct vbuf** off_screen){
	for(int i = NUM_ROWS-num_lines; i >= 0; i--){
		for(int j = 0; j < NUM_COLS; j++){
			V_BUF[j + NUM_COLS * (i+num_lines)] = V_BUF[j + NUM_COLS *i];
		}
	}
}

void c_set_theme(uint8_t fg, uint8_t bg){
	c_THEME = fg | bg << 4;
}
