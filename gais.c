/*-------Preprocessing--------*/
//1.detect html tag, convert it to gais record(maintain "id", "view count", "link cout/reference count" and "like count" ...)
//2.function
/*
    -main
    -for test
    -read data
    -delete html tag
    -get detail(upload date,author,size,link...)
    -convert to gais reocrd

*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include "readData.h"
#define FILELEN 50
#define REGLEN 100
int main(int argc, char *argv[]){
    //a.out -d/-r/-c(delete tag and store/store origin data/delete tag and convert to gais record) inputdata_file output
    int ch;
    char outfile[FILELEN];
    char reg[REGLEN];
    char *result;
    result =  malloc(sizeof(char)*SIZE);
    while((ch=getopt(argc,argv,"f:r:c:"))!=-1){
        switch(ch){
            case 'f'://import by file
                if(argc>=4){
                    strcpy(outfile,argv[3]);

                }
                else{
                    strcpy(outfile,"outfile.rec");
                    strcpy(reg,"");
                }
                
                if(argc==5){
                    strcpy(reg,argv[4]);
                }
                else{
                    strcpy(reg,"");
                }
                ReadData(ch,optarg,outfile,YES,reg,result);
                //command input output deletenewline? delete_tag return_block
                //printf("%s",result);
                break;
            case 's'://import by string
                ReadData(ch,optarg,outfile,YES,reg,result);
                break;
            case 'c':
                break;
            default:
                puts("command:a.out -f/-r/-c input_data output_file regular_exp");
        }
    }
    free(result);
    return 0;
}
