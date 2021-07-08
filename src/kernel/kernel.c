#include "terminal.h"

void k_main(){
	t_clear_rows(NUM_ROWS);
	int i = 48;
	while(1){
		char str[3];
		//*
		for(int j = 0; j < 100000000; j++){
			str[0] = i;
		}
		//*/
		str[0] = (char) i;
		str[1] = '\n';
		str[2] = '\0';
		t_print((char*)str);
		i = (i == 58) ? 48:i+1;
	}
}
