#include "readData.h"
#include "define.h"
#include "size.h"
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include <regex.h>
#define GRABLEN 350
#define HREFLEN 350

/* The following is the size of a buffer to contain any error messages
   encountered when the regular expression is compiled. */

#define MAX_ERROR_MSG 0x1000


/* Compile the regular expression described by "regex_text" into
   "r". */
int compile_regex (regex_t *r, const char *regex_text)
{
    //int status = regcomp (r, regex_text, REG_EXTENDED|REG_NEWLINE);
    int status = regcomp (r, regex_text, REG_EXTENDED);
    if (status != 0) {
        char error_message[MAX_ERROR_MSG];
        regerror (status, r, error_message, MAX_ERROR_MSG);
        printf ("Regex error compiling '%s': %s\n",
                regex_text, error_message);
        return 1;

    }
    return 0;

}

/*
   Match the string in "to_match" against the compiled regular
   expression in "r".
   */

int DeleteByRegex (regex_t *r, const char *to_match,int status,char *result)
{
    int start;
    int finish,pfinish=0;
    int i,j;
    int nomatch;
    char temp[GRABLEN];

    /* "P" is a pointer into the string which points to the end of the
       previous match. */
    const char *p = to_match;
    /* "N_matches" is the maximum number of matches allowed. */
    const int n_matches = 100;
    /* "M" contains the matches found. */
    regmatch_t m[n_matches];

    strcpy(result,"");
    char *t,*tp;
    int cnt=0;
    int detect,bdetect;
    detect = bdetect=0;
    while (1) {
        nomatch = regexec (r, p, n_matches, m, 0);
        if (nomatch) {
            if(cnt==0){
                sprintf(result,"%s",p);
            }
            else{
                sprintf(result,"%s%s",result,p);
            }
            return cnt;
        }
        for (i = 0; i < n_matches; i++) {
            if (m[i].rm_so == -1) {
                break;
            }
            start = m[i].rm_so + (p - to_match);
            finish = m[i].rm_eo + (p - to_match);

            if (i == 0) {
                //printf ("$0 is ");

            }
            else {
                //printf ("$%d is ", i);

            }
            //printf("'%.*s' (bytes %d:%d)\n", (finish - start),to_match + start, start, finish);
            strncpy(temp,to_match + start,finish-start);
            getLink(temp,finish,start,result);
            //printf("get:[%.*s]\n",(start - pfinish),p);
            if(strlen(temp)==0){continue;}

            if(status==NORMAL){
                if(detect==0&&strstr(temp,"script")==0&&strstr(temp,"style")==0&&strstr(temp,"head")==0){
                    if(temp[0]=='\n'){
                        sprintf(result,"%s%.*s ",result,(start - pfinish),p);
                    }
                    else{
                        sprintf(result,"%s%.*s",result,(start - pfinish),p);
                    }

                }
                else if((t=strstr(temp,"script"))!=0||(t=strstr(temp,"style"))!=0||(t=strstr(temp,"head"))!=0){
                    if(*t=='h'){
                        bdetect=1;
                        //puts("-- in HEAD");
                    }
                    tp = t;
                    t--;
                    while(*t!='<'){
                        if(*t=='/'){
                            if(*tp=='h'){
                                bdetect=0;
                                //puts("-- out HEAD");
                            }
                            else{
                                detect=0;
                                //puts("--ignore stop");
                            }

                            break;
                        }
                        else if(*t!='/'&&*t!=' '){
                            break;
                        }
                        t--;
                    }
                    if(*t=='<'){
                        //puts("--ignore start");
                        if(bdetect==0){
                            if(temp[0]=='\n'){
                                sprintf(result,"%s%.*s ",result,(start - pfinish),p);
                            }
                            else{
                                sprintf(result,"%s%.*s",result,(start - pfinish),p);
                            }
                        }
                        detect=1;
                    }
                }
            }
            else if(status==CUS){
                if(temp[0]=='\n'){
                    sprintf(result,"%s%.*s ",result,(start - pfinish),p);
                }
                else{
                    sprintf(result,"%s%.*s",result,(start - pfinish),p);
                }
            }
            pfinish = finish;
        }

        p += m[0].rm_eo;
        cnt++;
    }

    return cnt;

}

int getLink(char *temp,int finish, int start, char *result)
{
    char *hp,*thp;
    char href[HREFLEN];
    int position,position_end,link_len,link_detect,nottag;
    position = position_end = link_len = link_detect = nottag = 0;
    if((hp=strstr(temp,"img"))!=0||(hp=strstr(temp,"iframe"))!=0||(hp=strstr(temp,"a"))!=0){
        thp = hp;
        thp--;
        while(*thp!='<'){
            if(*thp!=' '){
                nottag=1;
                break;
            }
            thp--;
        }
        if(nottag==1){return;}

        while(*hp!='>'){
            if(*hp=='s'&&*(hp+1)=='r'&&*(hp+2)=='c'){
                hp+=3;
                while(*hp!='\''||*hp!='\"'){
                    if(*hp!=' '&&*hp!='='){
                        break;
                    }
                    hp++;
                    position++;
                }
                if(*hp!='\''&&*hp!='\"'&&*hp!=' '&&*hp!='='){continue;}

                hp++;
                position++;
                if(*hp==' '){
                    while(*hp==' '){
                        hp++;
                        position++;
                    }
                }
                link_detect=1;
                break;
            }
            else if(*hp=='h'&&*(hp+1)=='r'&&*(hp+2)=='e'&&*(hp+3)=='f'){
                hp+=4;
                while(*hp!='\''||*hp!='\"'){
                    if(*hp!=' '&&*hp!='='){
                        break;
                    }
                    hp++;
                    position++;
                }
                if(*hp!='\''&&*hp!='\"'&&*hp!=' '&&*hp!='='){continue;}

                hp++;
                position++;
                if(*hp==' '){
                    while(*hp==' '){
                        hp++;
                        position++;
                    }
                }
                link_detect=2;
                break;
            }
            else{
                position++;
                hp++;
            }
        }
        if(link_detect>0){
            thp = hp;
            while(*thp!='>'&&*thp!=' '){
                if(*thp=='\''||*thp=='\"'||position_end>0){
                    position_end++;
                }
                else{
                    link_len++;
                }
                thp++;
            }
            strncpy(href,hp,(finish-start-position-position_end-2));
            href[link_len]='\0';
            if(link_detect==1){
                sprintf(result,"%s(src_link:%s)",result,href);
            }
            else if(link_detect==2){
                sprintf(result,"%s(href_link:%s)",result,href);
            }
        }
    }
}
