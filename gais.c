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
                stream = fopen(optarg,"r");
                fread(idata,sizeof(char),IMPORT_DATA_LEN,stream);
                //strcpy(idata,"<html><!-- commnent1 -->\n<head>\n<script><!-- comment2 -->\nfunction1\n</script>\n<style> style 1 </style><!-- comment3 -->\n</head>\n<body>\n<div>\ndiv1\n<script>\n function2 \n</script>\ndiv2\n<!-- comment 4 -->div3< img src='www.qq.com ' >link 1 end</div>< a href = 'href.com.tw' >\n<!--commemt5-->\n</body>\n<script>\nfunction3\n</script>\n<div>\ndiv 4< img  id='2' src = 'img.com.tw ' class = 'src_test' >\n</div><a class='href_2' href = \" a_link.com.tw \" id='2'>\n<iframe src=\"demo_iframe.htm\" width='200' height='200'></iframe></html>");
                size = ReadData(READDATA,idata,YES,filter,result,strlen(idata));
                /*Usage:ReadData(READFILE/READDATA,file/string,YES/NO,filter,result)
                  element 3 means delete newline(YES or NO)
filter:0(NULL)->do not delete tag
"default" or "" -> delete all tag
"html","div"...->delete certain tag
*/
                printf("%s\n",result);
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
