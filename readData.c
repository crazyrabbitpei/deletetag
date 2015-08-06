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
#include "readData.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int ReadData(int command, char *ifile,char *ofile,int rep,char *reg,char *result){

    FILE *stream;
    char data[SIZE];
    int totalsize=0,size=0,count=0;
    stream = fopen(ifile,"r");
    if(stream==NULL){
        error(errno);
        return -1;   
    }
    /*
    output = fopen(ofile,"w");
    if(output==NULL){
        error(errno);
        return -1;
    }
    */
    size = fread(data,sizeof(char),SIZE,stream);

    if(rep==YES){
        DeleteNewline(data,size);
    }
    DeleteTag(data,ofile,reg,result);
    fclose(stream);
    return 0;
}
void print(char *data){
    printf("read data:%s\n",data);
}
void error(int err){
    printf("error message:%s\n",strerror(err));
}
