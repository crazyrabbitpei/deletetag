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
    int i=0,j=0;
    char filename[300];
    FILE *stream;
    result = malloc(sizeof(char)*IMPORT_DATA_LEN);
    idata = malloc(sizeof(char)*IMPORT_DATA_LEN);
    while((ch=getopt(argc,argv,"f:t"))!=-1){
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
                //size = ReadData(READFILE,optarg,YES,filter,result,strlen(idata);
                /*read from string*/
                //stream = fopen(optarg,"r");
                //fread(idata,sizeof(char),IMPORT_DATA_LEN,stream);
                //strcpy(idata,"<div class='test'>hello</div><title>rrrr<title><!--qqqq-->aaaa");
                strcpy(idata,"< img class='test' href='www.cs.eee' id='2'><!--hello-->test<!-- haha -->test2< div class='sada'>qqqq< /div>< script >functoin< /script >hello~~<img href='sdadas'>");
                //strcpy(idata,"hello");
                size = ReadData(READDATA,idata,YES,filter,result,strlen(idata));
                /*Usage:ReadData(READFILE/READDATA,file/string,YES/NO,filter,result)
                  element 3 means delete newline(YES or NO)
filter:0(NULL)->do not delete tag
"default" or "" -> delete all tag
"html","div"...->delete certain tag
*/
                printf("result:%s\n",result);
                break;
            case 't':
                for(i=10;i<=12;i++){
                //for(i=0;i<=500000;i++){
                    strcpy(filename,"");
                    //sprintf(filename,"../ettoday500000/%d.htm",i);
                    sprintf(filename,"/data/news/yahoo/yahoo_data2013-2015/yahoo/html/201303/201303%d_html",i);
                    stream = fopen(filename,"r");
                    if(stream){
                        idata = malloc(sizeof(char)*IMPORT_DATA_LEN);
                        fread(idata,sizeof(char),IMPORT_DATA_LEN,stream);
                        //printf("filename:%s size:%d\n",filename,(int)strlen(idata));
                        result = malloc(sizeof(char)*strlen(idata));
                        size = ReadData(READDATA,idata,YES,filter,result,strlen(idata));
                        printf("[%d]size:%d\n(%s)\n",i,size,result);

                    }
                    else{
                        printf("open error\n");
                    }
                    fclose(stream);
                }
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
