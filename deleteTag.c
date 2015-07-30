#include "readData.h"
#include<stdio.h>
#include<string.h>
#include<errno.h>

int DeleteTag(const char *data,char *ofile){
    regex_t r;
    const char *regex_text;
    const char *find_text;
    //find_text = "<div><a href='http://fun.ltn.com.tw/?day=4' data-desc='自由FUN送台 週四愛料理\n' class='weeklink weektit'>自由FUN送台 週四愛料理\n</a></div>";

    regex_text = "<[^>]*>";
    compile_regex(&r, regex_text);
    DeleteByRegex(&r, data,ofile);
    //DeleteByRegex(&r, find_text,ofile);
    regfree (&r);
}

int DeleteNewline(char *data,int rep,int size){
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
