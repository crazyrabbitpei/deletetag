#include "readData.h"
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include <regex.h>
#define TAGLEN 50
int DeleteTag(const char *data,char *ofile,char *reg,char *result){
    regex_t r;
    const char *regex_text;
    const char *find_text;
    char tag[TAGLEN];
    int status;
    //find_text = "<div><a href='http://fun.ltn.com.tw/?day=4' data-desc='自由FUN送台 週四愛料理\n' class='weeklink weektit'>自由FUN送台 週四愛料理\n</a></div>";
    find_text = "1234";
    if(strcmp(reg,"")==0){
        //regex_text = "<[^>]*>";
        regex_text = "123";
        status = NORMAL;
    }
    else{
        strcpy(tag,reg);
        sprintf(tag,"</*%s[^>]*>",reg);
        regex_text = tag;
        status = CUS;
    }
    compile_regex(&r, regex_text);
    DeleteByRegex(&r, find_text,ofile,status,result);
    //DeleteByRegex(&r, data,ofile,status,result);
    regfree (&r);
}

int DeleteNewline(char *data,int size){
    char *p = data;
    int i=0;
    while(i<size){
        //printf("%d:[%c]->[%c]\n",i,*p,*(p+1));
        if(*p=='\n'){
            //puts("newline");
            *p = ' ';
        }
        else if(*p=='\\'&&(*(p+1)=='r'||*(p+1)=='n')){
            //puts("sp newline");
                *p = ' ';
        }
        p++;
        i++;
    }
    return 0;
}
