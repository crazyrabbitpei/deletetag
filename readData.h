#include<regex.h>

int ReadData(int command, char *ifile,int rep,char *reg,char *result);
//int ReadData(int command, char *ifile,int rep,char *reg);
int DeleteTag(const char *data,char *reg,char *result);
int DeleteNewline(char *data,char *output, int size);
void error(int err);
void print(char *data);

int compile_regex (regex_t *r, const char *regex_text);
int DeleteByRegex (regex_t *r, const char *to_match,int status,char *result);
