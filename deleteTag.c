#include "readData.h"
#include "define.h"
#include "size.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include <regex.h>
#define TAGLEN 50
char *DeleteTag(const char *data,char *reg,char *result){
	regex_t r;
	const char *regex_text;
	const char *find_text;
    char *ptr;
	char tag[TAGLEN];
	int status;
    int match=0;
	if(strcmp(reg,"default")==0||strcmp(reg,"")==0){
		regex_text = "<(\\-)*[^>]*>";
		//regex_text = "<[^>][\\-]*>";
		status = NORMAL;
	}
	else{
		strcpy(tag,reg);
		sprintf(tag,"</*%s[^>]*>",reg);
		regex_text = tag;
		status = CUS;
	}
    
	compile_regex(&r, regex_text);
    
	//match = GetByRegex(&r, data,status,result);
	//ptr = DeleteByRegex(&r, data,status,result);
    
	regfree (&r);

    //printf("match:%d\n",match);
    return ptr;
}

int DeleteNewline(char *data,char *output,int size){
	char *p = data;
	int word=0;
	int line=0;
	int i=0,cnt=0;
	while(i<size){
		//printf("%d:[%c]->[%c]\n",i,*p,*(p+1));
		//if(*p=='\n'||*p=='\r'){
		if(*p>=1&&*p<=31){
			//puts("newline");
			if(line!=1){
				*p = ' ';
				output[word++]= *p;
				line = 1;
                cnt++;
			}
			else{
				//*p = 'a';
			}
		}
		else if(*p=='\\'&&(*(p+1)=='r'||*(p+1)=='n')){
			//puts("sp newline");
			if(line!=1){
				*p = ' ';
				output[word++]= *p;
				line = 1;
                cnt++;
			}
			else{
				//*p = 'a';
			}
		}
		else{
			output[word++]= *p;
			line=0;
            cnt++;
		}

		p++;
		i++;
	}
    output[cnt++] = '\0';
	//printf("----\n%s\n----\n",output);
	return cnt;
}
