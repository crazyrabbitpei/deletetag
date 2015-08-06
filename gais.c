#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include "readData.h"
#define FILELEN 50
#define REGLEN 100
int main(int argc, char *argv[]){
    //command:a.out -f/-s input_data output_file regular_exp
    int ch;
    char outfile[FILELEN];
    char reg[REGLEN];
    char *result;
    result =  malloc(sizeof(char)*SIZE);
    while((ch=getopt(argc,argv,"f:s:"))!=-1){
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
		printf("reg:%s\n",reg);
                ReadData(ch,optarg,outfile,YES,reg,result);
                //command input output deletenewline? delete_tag return_block
                break;
            case 's'://import by string
                ReadData(ch,optarg,outfile,YES,reg,result);
                break;
            default:
                puts("command:a.out -f/-s input_data output_file regular_exp");
        }
    }
    free(result);
    return 0;
}
