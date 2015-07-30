#include <regex.h>
#define SIZE 7340032//7M
//#define SIZE 7168//7k

int DeleteTag(const char *data,char *ofile);
int DeleteNewline(char *data,int size);
void error(int err);
void print(char *data);
int compile_regex (regex_t *r, const char *regex_text);
int DeleteByRegex (regex_t *r, const char *to_match,char *ofile);
