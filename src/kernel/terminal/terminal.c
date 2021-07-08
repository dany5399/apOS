#include "terminal.h"

//video buffer
struct vbuf_t{
	uint8_t _char;
	uint8_t color;
};

struct vbuf_t* V_BUF = (struct vbuf_t*) 0xb8000; //video memory location

static uint8_t t_CURR_ROW;
static uint8_t t_CURR_COL;

void t_clear_rows(int lines){

	size_t row = 0;
	if(lines < 0){
		row = NUM_ROWS + lines; //delete from bottom
		lines = NUM_ROWS;
	}

	struct vbuf_t EMPTY_CHAR = (struct vbuf_t) {_char: ' ', color: t_THEME};
	for(; row < lines; row++){
		//if only we had memcpy
		for(size_t col = 0; col < NUM_COLS; col++){
			V_BUF[col + NUM_COLS * row] = EMPTY_CHAR;
		}
	}
}

#define CLR_SCRL(_LINES, _DIRECTION)	\
do{										\
	t_clear_rows(_LINES);					\
	t_scroll(_DIRECTION, _LINES);		\
}while(0)

void t_print(char* str){
	
	for(int i = 0; i < NUM_COLS; i++){
		switch(str[i]){
		case '\n':
			if(t_CURR_ROW == NUM_ROWS-1){
			//	t_clear_rows(1);
				t_scroll(t_UP, 1);
				t_clear_rows(-1);
			}else{
				t_CURR_ROW++;
			}
			t_CURR_COL = 0;
			continue;
		case '\0': 
			return;
		default:
			struct vbuf_t cbuf = (struct vbuf_t) {_char: str[i], color: t_THEME};
			V_BUF[t_CURR_COL + NUM_COLS * t_CURR_ROW] = cbuf;
		}
		t_CURR_COL++;
	}
}

void t_scroll(int direction, uint8_t num_lines){
	for(int k = 0; k < num_lines; k++){
		for(int i = 1; i < NUM_ROWS; i++){
			for(int j = 0; j < NUM_COLS; j++){
				V_BUF[j + NUM_COLS * (i-1)] = V_BUF[j + NUM_COLS * i];
			}
		}
	}
}

void t_set_theme(uint8_t fg, uint8_t bg){
	t_THEME = fg | bg << 4;
}
