#include <regex.h>
#define SIZE 5242880

int DeleteTag(const char *data,char *output);
void error(int err);
void print(char *data);
int compile_regex (regex_t *r, const char *regex_text);
int match_regex (regex_t *r, const char *to_match,char *ofile);
