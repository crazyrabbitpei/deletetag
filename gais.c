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
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include "readData.h"

int main(int argc, char *argv[]){
    //a.out -d/-r/-c(delete tag and store/store origin data/delete tag and convert to gais record) inputdata_file output
    int ch;
    while((ch=getopt(argc,argv,"d:r:c:"))!=-1){
        switch(ch){
            case 'd':
                ReadData(ch,optarg,argv[3],NO);
                break;
            case 'r':
                break;
            case 'c':
                break;
            default:
                puts("command:a.out -d/-r/-c input_data output_file");
        }
    }
    return 0;
}
