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
#include "main.h"

int ReadData(int command,char *ifile, char *ofile);

int main(int argc, char *argv[]){
    //a.out -d/-r/-c(delete tag and store/store origin data/delete tag and convert to gais record) inputdata_file output
    int ch;
    printf("argc:%d\nargv:%s\n",argc,argv[1]);
    while((ch=getopt(argc,argv,"d:r:c:"))!=-1){
        switch(ch){
            case 'd':
                puts("delete html tag");
                printf("optarg:%s,%s\n",optarg,argv[argc-1]);
                ReadData(ch,optarg,argv[argc-1]);
                break;
            case 'r':
                puts("read origin data");
                break;
            case 'c':
                puts("convert to gais record");
                break;
            default:
                puts("command:a.out -d/-r/-c input_data output_file");
        }
    }

    return 0;
}
int ReadData(int comman, char *ifile,char *ofile){
    FILE *stream;
    char data[SIZE];
    int size=0;
    stream = fopen(ifile,"r");
    if(stream==NULL){
        error(errno);
        return -1;   
    }
    //fseek(stream,SEEK_END,SEEK_SET);
    //size = ftell(stream);
    size = fread(data,sizeof(char),SIZE,stream);
    //print(data);
    DeleteNewline(data,size);
    DeleteTag(data,ofile);
    //fwrite(data,sizeof(char),SIZE,output);
    //fseek(stream,SIZE,SEEK_SET);

    fclose(stream);
    return 0;
}
void print(char *data){
    printf("read data:%s\n",data);
}
void error(int err){
    printf("error message:%s\n",strerror(err));
}
