#include "readData.h"
#include "define.h"
#include "size.h"
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include <regex.h>
#define TAGLEN 50
int DeleteTag(const char *data,char *reg,char *result){
	regex_t r;
	const char *regex_text;
	const char *find_text;
	char tag[TAGLEN];
	int status;
	//find_text = "<div><a href='http://fun.ltn.com.tw/?day=4' data-desc='自由FUN送台 週四愛料理\n' class='weeklink weektit'>自由FUN送台 週四愛料理\n</a></div>";
	if(strcmp(reg,"default")==0||strcmp(reg,"")==0){
		regex_text = "<[^>]*>";
		status = NORMAL;
	}
	else{
		strcpy(tag,reg);
		sprintf(tag,"</*%s[^>]*>",reg);
		regex_text = tag;
		status = CUS;
	}

	compile_regex(&r, regex_text);
	DeleteByRegex(&r, data,status,result);
	regfree (&r);
}

int DeleteNewline(char *data,int size){
	char *p = data;
	int line=0;
	int i=0;
	while(i<size){
		//printf("%d:[%c]->[%c]\n",i,*p,*(p+1));
		//if(*p=='\n'||*p=='\r'){
		if(*p>=1&&*p<=31){
			//puts("newline");
			if(line!=1){
				*p = ' ';
			}
			line=1;
		}
		else if(*p=='\\'&&(*(p+1)=='r'||*(p+1)=='n')){
			//puts("sp newline");
			if(line!=1){
				*p = ' ';
			}
			line=1;
		}
		else{
			line=0;
		}
		p++;
		i++;
	}
	return 0;
}
