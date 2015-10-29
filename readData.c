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
	char *data,*output;

	int totalsize=0,size=0,count=0;
	switch(command){
		case 0://Read from file
			stream = fopen(idata,"r");
			if(stream==NULL){
				error(errno);
				return -1;   
			}
			if(reg==NULL){
				output = malloc(sizeof(char)*IMPORT_DATA_LEN);
				size = fread(output,sizeof(char),IMPORT_DATA_LEN,stream);
				if(rep==YES){
					DeleteNewline(output,result,size);
					//strcpy(result,output);
				}
				else{
					strcpy(result,output);
				}
				free(output);
				
				size = (int)strlen(result);
				return size;
			}
			else{//want to delete html tag
				data = malloc(sizeof(char)*IMPORT_DATA_LEN);
				size = fread(data,sizeof(char),IMPORT_DATA_LEN,stream);
			}
			if(rep==YES){
				output = malloc(sizeof(char)*IMPORT_DATA_LEN);
				DeleteNewline(data,output,size);
				DeleteTag(output,reg,result);
				free(output);
			}
			else{
				DeleteTag(data,reg,result);
			}

			free(data);
			fclose(stream);
			break;
		case 1://Read from string
			size = (int)strlen(idata);
			if(reg==NULL){
				if(rep==YES){
					DeleteNewline(idata,result,size);
					size = (int)strlen(result);
				}
				else{
					strcpy(result,idata);
					size = (int)strlen(idata);
				}
				return size;

			}
			else{
				if(rep==YES){
					output = malloc(sizeof(char)*IMPORT_DATA_LEN);
					DeleteNewline(idata,output,size);
					DeleteTag(output,reg,result);
					
					free(output);
				}
				else{
					DeleteTag(idata,reg,result);
				}
				
			}
			
			break;
	}
	size = (int)strlen(result);
	return size;
}
void print(char *data){
	printf("read data:%s\n",data);
}
void error(int err){
	printf("deleteTag error message:%s\n",strerror(err));
}
