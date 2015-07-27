#include "main.h"
#include<stdio.h>
#include<errno.h>

int DeleteTag(char *data,char *ofile){
    regex_t r;
    const char *regex_text;
    const char *find_text;
    
    //regex_text = "\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*.\\w+([-.]\\w+)";
    //regex_text = "<[^>]*>|<script[\\d\\D]*?>[\\d\\D]*?</script>";
    regex_text = "<[^>]*>|\n";
    //find_text = "<script>12235</script>\n<script>function start(){}</script><a href='www.cs.ccu.edu.tw'>this hello is my email:peggy111333@yahoo.com.tw another email is willow111333@gmail.com</a>\n<div>hello@mail.com</div>\ntest123@mail.com";
    
    compile_regex(&r, regex_text);
    match_regex(&r, data,ofile);
    regfree (&r);

    //fwrite(data,sizeof(char),SIZE,output);
}
