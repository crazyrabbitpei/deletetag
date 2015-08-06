#include<regex.h>
#define SIZE 7340032//7M
typedef enum{
    NO,
    YES
}flag;
typedef enum{
    NORMAL,
    CUS
}config_reg;
int ReadData(int command, char *ifile,char *ofile,int rep,char *reg,char *result);
//int ReadData(int command, char *ifile,char *ofile,int rep,char *reg);
int DeleteTag(const char *data,char *ofile,char *reg,char *result);
int DeleteNewline(char *data,int size);
void error(int err);
void print(char *data);

int compile_regex (regex_t *r, const char *regex_text);
int DeleteByRegex (regex_t *r, const char *to_match,char *ofile,int status,char *result);
