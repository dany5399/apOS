#include "kprintf.h"

//TODO: redo this when the heap is done

typedef struct _fmt_info{
	int		msg_len;
	int		fmt_count;
}fmt_info_t;

static inline void get_format_info(const char* fmt, fmt_info_t* fmt_info){
	while(*fmt){
		fmt_info->msg_len++;
		if(*fmt == '%')
			fmt_info->fmt_count++;
	}
	fmt_info->msg_len += fmt_info->fmt_count*20; //for good measure in case it's large numbers or addresses
}

void kprintf(const char* format, ...){
	
	fmt_info_t fmt_info = {msg_len: 0, fmt_count: 0};
	get_format_info(format, &fmt_info);

	int msg_pos = 0;
	int fmt_num = 0;

	char msg[fmt_info.msg_len];
	char fmt_pos[fmt_info.fmt_count];
	char fmt_msg[fmt_info.fmt_count][20];	//for now...

	//TODO: fix/impl all specifiers
	va_list args;
	va_start(args, format);
	while(*format){
		if(*format++ == '%'){
	
			int i = 0;
			fmt_pos[fmt_num] = msg_pos;

			switch(*format++){
			//for some reason these also do unsigned short
			case 'd':
			case 'i':
				int num = va_arg(args, int);
				while(num > 9){
					int digit = num % 10;
					fmt_msg[fmt_num][i++] = digit + '0';
				}
				fmt_msg[fmt_num++][i] = '\0';
				msg_pos += i;
				continue;

			case 's':
				char* str = va_arg(args, char*);
				while(*str){
					fmt_msg[fmt_num][i++] = *str;
				}
				fmt_msg[fmt_num++][i] = '\0';
				msg_pos += i;
				continue;

			//just assuming unsigned for now
			case 'x':
			case 'X':
				unsigned long lnum = va_arg(args, unsigned long);
				while(lnum > 9){
					uint32_t digit = lnum % 10;
					fmt_msg[fmt_num][i++] = digit + '0';
				}
				fmt_msg[fmt_num++][i] = '\0';
				msg_pos += i;
				continue;
			}
		}
		msg[msg_pos++] = *format;
	}

	for(int i = 0; i < fmt_info.fmt_count; i++){
		int j = 0;
		for(char c = fmt_msg[i][j]; c != '\0'; j++){
			msg[fmt_pos[i] + j] = c;
		}
	}
	va_end(args);

	c_print((char*) msg);
}
//for later. dont feel like properly copy pasting format specs and comments
/*
	while(*format){
		if(*format++ == '%'){
	
			int i = 0;
			fmt_pos[fmt_num] = msg_pos;

			switch(*format++){
			case '%': continue;
			
			case 'c': continue;
			
			//for some reason these also do unsigned short
			case 'd':
			case 'i':
				int num = va_arg(args, int);
				while(num > 9){
					int digit = num % 10;
					fmt_msg[fmt_num][i++] = digit + '0';
				}
				fmt_msg[fmt_num++][i] = '\0';
				msg_pos += i;
				continue;

			case 'f': continue;

			//floats but also does doubles cuz y not
			case 'e':
			case 'E':
			case 'g':
			case 'G': continue;
					
			//short
			case 'h': continue;
			
			//only long but %lu does int/long cuz %u...
			case 'l':
			case 'L': continue;

			//nothing
			case 'n': continue;
			
			//octal - also has to do unsigned short and int...
			case 'o': continue;
			
			//pointer (void*)
			case 'p': continue;

			case 's':
				char* str = va_arg(args, char*);
				while(*str){
					fmt_msg[fmt_num][i++] = *str;
				}
				fmt_msg[fmt_num++][i] = '\0';
				msg_pos += i;
				continue;
			//unsigned int/long
			case 'u': continue;

			//just assuming unsigned for now
			case 'x':
			case 'X':
				unsigned long lnum = va_arg(args, unsigned long);
				while(lnum > 9){
					uint32_t digit = lnum % 10;
					fmt_msg[fmt_num][i++] = digit + '0';
				}
				fmt_msg[fmt_num++][i] = '\0';
				msg_pos += i;
				continue;
			default:
				continue;
			}
		}
		msg[msg_pos++] = *format;
	}
*/
