#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include "readData.h"
#include "define.h"
#include "size.h"
#define FILELEN 50
#define REGLEN 100
int main(int argc, char *argv[]){
	//command:a.out -f input_file output_file filterular_exp
	int ch,size,lan=0;
	char outfile[FILELEN];
	char filter[REGLEN];
	char *result,*idata;
	int check=0;
	FILE *stream;
	result = malloc(sizeof(char)*IMPORT_DATA_LEN);
	idata = malloc(sizeof(char)*IMPORT_DATA_LEN);
	while((ch=getopt(argc,argv,"f:"))!=-1){
		check=1;
		switch(ch){
			case 'f'://import by file
				if(argc>=4){//outfile name
					strcpy(outfile,argv[3]);
					if(argc==5){//read filterular expression
						strcpy(filter,argv[4]);
					}
					else{
						strcpy(filter,"default");
					}
				}
				else{
					strcpy(outfile,"outfile.rec");
					strcpy(filter,"default");
				}
				/*read from file*/
				//size = ReadData(READFILE,optarg,YES,filter,result);
				/*read from string*/
				stream = fopen(optarg,"r");
				fread(idata,sizeof(char),IMPORT_DATA_LEN,stream);
				size = ReadData(READDATA,idata,YES,filter,result);
				/*Usage:ReadData(READFILE/READDATA,file/string,YES/NO,filter,result)
				element 3 means delete newline(YES or NO)
				filter:0(NULL)->do not delete tag
				    "default" or "" -> delete all tag
				    "html","div"...->delete certain tag
				*/
				printf("%s\n",result);
				break;
			default:
					puts("command:a.out -f input_data");
		}
	}
	if(check==0){
		puts("command:a.out -f input_data");
		exit(1);
	}
	free(result);
	return 0;
}
