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
#include "readData.h"
#include "define.h"
#include "size.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int ReadData(int command, char *idata,int rep,char *reg,char *result){

	FILE *stream;
	char *data;
	int totalsize=0,size=0,count=0;
	switch(command){
		case 0://Read from file
			stream = fopen(idata,"r");
			if(stream==NULL){
				error(errno);
				return -1;   
			}
			if(reg==NULL){
				size = fread(result,sizeof(char),IMPORT_DATA_LEN,stream);
				if(rep==YES){
					DeleteNewline(result,size);
				}
				return size;
			}
			else{
				data = malloc(sizeof(char)*IMPORT_DATA_LEN);
				size = fread(data,sizeof(char),IMPORT_DATA_LEN,stream);
			}
			if(rep==YES){
				DeleteNewline(data,size);
			}

			DeleteTag(data,reg,result);

			free(data);
			fclose(stream);
			break;
		case 1://Read from string
			size = (int)strlen(idata);
			if(rep==YES){
				DeleteNewline(idata,size);
			}

			if(reg!=NULL){
				DeleteTag(idata,reg,result);
			}
			else{
				strcpy(result,idata);
			}
			break;
	}

	return size;
}
void print(char *data){
	printf("read data:%s\n",data);
}
void error(int err){
	printf("deleteTag error message:%s\n",strerror(err));
}
