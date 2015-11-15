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
//#define PARTSIZE 5000
#define PARTSIZE 3340010 //3M
char *divideData(int size, char *data, char *result, char *delims, char *delime, int delims_len, int delime_len);

int ReadData(int command, char *idata,int rep,char *reg,char *result,size_t data_size, char *delims, char *delime){

	FILE *stream;
	char *data,*output,*part_output,*ptr,*ptr_temp,*rptr;
	int i=0;
	int delims_len,delime_len;
	int totalsize=0,size=0,count=0, part_size=0;
	switch(command){
		case 0://Read from file
			stream = fopen(idata,"r");
			if(stream==NULL){
				error(errno);
				return -1;   
			}
			if(reg==NULL){
				output = malloc(sizeof(char)*data_size);
				size = fread(output,sizeof(char),data_size,stream);
				if(rep==YES){
					size = DeleteNewline(output,result,size);
					//strcpy(result,output);
				}
				else{
					strcpy(result,output);
					size = data_size;
				}
				free(output);
				
				return size;
			}
			else{//want to delete html tag
				data = malloc(sizeof(char)*data_size);
				size = fread(data,sizeof(char),data_size,stream);
			}
			if(rep==YES){
				output = malloc(sizeof(char)*data_size);
				size = DeleteNewline(data,output,size);
				ptr = output;

				//if(data_size>PARTSIZE){
				if(delims!=NULL&&delime!=NULL){
					delims_len = strlen(delims);
					delime_len = strlen(delime);
					while(ptr!=NULL){
						part_output = malloc(sizeof(char)*size);
						if((ptr = divideData(size,ptr,part_output,delims,delime,delims_len,delime_len))!=NULL){
							//printf("%s\n",part_output);
							DeleteTag(part_output,reg,result);
							free(part_output);
						}
						i++;
					}
				}
				else{
					DeleteTag(output,reg,result);
				}
				free(output);
			}
			else{
				ptr = data;
				//if(data_size>PARTSIZE){
				if(delims!=NULL&&delime!=NULL){
					delims_len = strlen(delims);
					delime_len = strlen(delime);
					while(ptr!=NULL){
						part_output = malloc(sizeof(char)*data_size);
						if((ptr = divideData(size,ptr,part_output,delims,delime,delims_len,delime_len))!=NULL){
							//printf("%s\n",part_output);
							DeleteTag(part_output,reg,result);
							free(part_output);
						}
						i++;
					}
				}
				else{
					DeleteTag(data,reg,result);
				}
			}

			free(data);
			fclose(stream);
			break;
		case 1://Read from string
			size = data_size;
			printf("Origin:%d\n",size);
			if(reg==NULL){
				if(rep==YES){
					size = DeleteNewline(idata,result,size);
				}
				else{
					strcpy(result,idata);
					size = data_size;
				}
				return size;

			}
			else{
				if(rep==YES){
					output = malloc(sizeof(char)*data_size);
					size = DeleteNewline(idata,output,size);
					printf("DeleteNewline:%d\n",size);
					printf("output size:%ld\n",strlen(output));
					ptr = output;
					//if(data_size>PARTSIZE){
					if(delims!=NULL&&delime!=NULL){
						delims_len = strlen(delims);
						delime_len = strlen(delime);
						rptr = result;
						i=0;
						while(ptr!=NULL){
							part_output = malloc(sizeof(char)*size);
							if((ptr = divideData(size,ptr,part_output,delims,delime,delims_len,delime_len))!=NULL){
								printf("i=%d\t",i);
								//printf("%s\n",part_output);
								//rptr = DeleteTag(part_output,reg,rptr);
								free(part_output);
							}
							i++;
						}
						printf("i=%d\n",i);
					}
					else{
						DeleteTag(output,reg,result);
					}
					free(output);
				}
				else{
					ptr = idata;
					//if(data_size>PARTSIZE){
					if(delims!=NULL&&delime!=NULL){
						delims_len = (int)strlen(delims);
						delime_len = (int)strlen(delime);
						rptr = result;
						i=0;
						while(ptr!=NULL){
							part_output = malloc(sizeof(char)*size);
							if((ptr = divideData(size,ptr,part_output,delims,delime,delims_len,delime_len))!=NULL){
								//printf("%s\n",part_output);
								//rptr = DeleteTag(part_output,reg,rptr);
								free(part_output);
								ptr=ptr_temp;
							}
							i++;
						}
						
					}
					else{
						DeleteTag(idata,reg,result);
					}
				}
				
			}
			
			break;
	}
	//size = (int)strlen(result);
	return size;
}
void print(char *data){
	printf("read data:%s\n",data);
}
void error(int err){
	printf("deleteTag error message:%s\n",strerror(err));
}

char *divideData(int size, char *data, char *result, char *delims, char *delime,int delims_len, int delime_len)
{
	int i=0,j,flag=0,cnt=0;
	char *start,*start_temp, *end,*temp;
	printf("data len:%ld\n",strlen(data));
	if(strlen(data)==0){
		return NULL;
	}
	start = strstr(data,delims);
	if(start==NULL){
		return start;
	}
	while(i<delims_len){
		start++;
		i++;
	}
	start_temp = start;
	//j=0;
	while(j<size){
		temp = start_temp;
		flag=0;
		//printf("cnt:%d,%c\n",cnt,*temp);
		i=0;
		while(i<delime_len){
			if(*temp!=delime[i]){
				flag=1;
				break;	
			}
			//wprintf("temp=%c,delim[%d]=%c\n",*temp,i,delime[i]);
			temp++;
			i++;
		}
		if(flag==0){
			break;
		}
		cnt++;
		start_temp++;
		j++;
	}
	
	//sprintf(result,"%.*s",cnt,start);
	strncpy(result,start,cnt);
	result[cnt]='\0';
	//printf("--\n%s\n",result);
	return start+cnt;
}
