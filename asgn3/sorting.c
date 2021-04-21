#include "bubble.h"
#include "shell.h"
#include "quick.h"
#include <stdio.h>
#include <inttypes.h>
#define OPTIONS "absqQrnp"

void print_bubble(void){
	printf("Bubble Sort\n");
	print(" elements," " moves" " compares");
	
	printf("%13"PRIu32);

int main(argc, **argv) {
	int opt=0;
	int64_t seed = 13371453, size = 100, elem=100;
	int bubble, shell, quick_stack,quick_queue;
	while ((opt = getopt(argc,arv,OPTIONS))!=-1){
		switch(opt){
		case 'a':
			if (!bubble){
				bubble=1;
			}
			if (!shell){
				shell=1;
			}
			if (!quick_stack){
				quick_stack=1;
			}
			if (!quick_queue){
				quick_queue=1;
			}
			break;
		case 'b':
			if(!bubble){
				bubble=1;
			}
			break;
		case 's':
			if (!shell){
				shell=1;
			}
			break;
		case 'q':
			if (!quick_stack){
				quick_stack=1;
			}
			break;
		case 'Q':
			if (!quick_queue){
				quick_queue=1;
			}
			break;
		case 'r':
			scanf("%" SCNd64, &seed);
			srandom(seed);
			break;
		case 'n':
			scanf("%" SCNd64, &size);
			break;
		case 'p':
			scanf("%" SCNd64, %elem);
			break;
		}
	}
	if (bubble){
		print_bubble();
	}
	if (shell){
		print_shell();
	}
	if (quick_stack){
		print_quick_stack();
	}
	if (quick_queue){
		print_quick_queue();
	}
	return 0;
}
