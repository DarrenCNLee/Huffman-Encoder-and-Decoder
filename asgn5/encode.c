#include "hamming.h"
#include <unistd.h>
#define OPTIONS "hi:o:"

int main(int argc,char **argv){
	while ((opt=getopt(argc,argv,OPTIONS))!=-1){
		switch(opt){
		case 'h':
		case 'i':

		}
	}
	while (fgetc() !=EOF){
		msg_low=lower

