#include "main.h"
#include<stdio.h>
#include<errno.h>

int DeleteTag(const char *data,char *ofile){
    regex_t r;
    const char *regex_text;
    const char *find_text;
    
    //regex_text = "\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*.\\w+([-.]\\w+)";
    //regex_text = "<script[\\d\\D]*?>[\\d\\D]*?</script>";
    regex_text = "<[^>]*>";
    //find_text = "<meta name='robots' content=\n'all'\n /><script>\nfunction end(){\nvar test;\n}\n</script>\n<script>function start(){}</script><a href='www.cs.ccu.edu.tw'>this hello is my email:peggy111333@yahoo.com.tw another email is willow111333@gmail.com</a>\n<div>hello@mail.com</div>\ntest123@mail.com";
    
    compile_regex(&r, regex_text);
    //match_regex(&r, find_text,ofile);
    DeleteByRegex(&r, data,ofile);
    regfree (&r);

    //fwrite(data,sizeof(char),SIZE,output);
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
        else if(*p=='\\'){
        //else if((*p=='\\'&&(*(p+1)=='n')||*(p+1)=='r')){
            //puts("sp newline");
            //if(*p=='\\'){
                *p = ' ';
            //}
            //p++;
            //i++;
            //*p = ' ';
        }
        p++;
        i++;
    }
    return 0;
}
