#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include "readData.h"
#include "size.h"
#define FILELEN 50
#define REGLEN 100
int main(int argc, char *argv[]){
	//command:a.out -f/-s input_data output_file regular_exp
	int ch,size,lan=0;
	char outfile[FILELEN];
	char reg[REGLEN];
	char *result;
	int check=0;
	result =  malloc(sizeof(char)*IMPORT_DATA_LEN);
	while((ch=getopt(argc,argv,"f:s:t:"))!=-1){
		check=1;
		switch(ch){
			case 'f'://import by file
				if(argc>=4){//outfile name
					strcpy(outfile,argv[3]);
					if(argc==5){//read regular expression
						strcpy(reg,argv[4]);
					}
					else{
						strcpy(reg,"default");
					}
				}
				else{
					strcpy(outfile,"outfile.rec");
					strcpy(reg,"default");
				}
				size = ReadData(0,optarg,YES,"",result);
				//command,inputdata/file,delete new line or not,regular expression,result
				//element 3 means delete newline(YES or NO)
				//reg:0(NULL)->do not delete tag
				//    "default" or "" -> delete all tag
				//    "html","div"...->delete certain tag
				
				//command input output deletenewline? delete_tag return_block
				printf("%s\n",result);
				break;
			case 's'://import by string
				break;
			case 't':
				break;
			default:
					puts("command:a.out -f/-s input_data output_file regular_exp");
		}
	}
	if(check==0){
		puts("command:a.out -f input_data output_file regular_exp");
		exit(1);
	}
	free(result);
	return 0;
}
