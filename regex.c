#include "readData.h"
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include <regex.h>

extern FILE *output;
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

int DeleteByRegex (regex_t *r, const char *to_match,char *ofile)
{
    long int start;
    long int finish,pfinish=0;
    int i,detect=0;
    int nomatch;
    char temp[30];
    /* "P" is a pointer into the string which points to the end of the
       previous match. */
    const char *p = to_match;
    /* "N_matches" is the maximum number of matches allowed. */
    const int n_matches = 100;
    /* "M" contains the matches found. */
    regmatch_t m[n_matches];

    while (1) {
        nomatch = regexec (r, p, n_matches, m, 0);
        if (nomatch) {
            if(detect==0){  
                fprintf(output,"%s",p);
            }
            fclose(output);
            return nomatch;
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
            strncpy(temp,to_match + start,10);

            if(detect==0&&strstr(temp,"<script")==0&&strstr(temp,"<style")==0&&strstr(temp,"<head")==0){
                if(temp[0]=='\n'){
                    fprintf(output,"%.*s ",(start - pfinish),p);
                }
                else{
                    fprintf(output,"%.*s",(start - pfinish),p);
                }
            }
            else{
                detect = 1;
            }
            if(strstr(temp,"</script>")!=0||strstr(temp,"</style>")!=0||strstr(temp,"</head>")!=0){
                detect = 0;
            }
            pfinish = finish;

        }

        p += m[0].rm_eo;
    }

    return 0;

}

