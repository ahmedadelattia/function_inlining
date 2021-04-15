#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <regex.h>

/*
void parsefile(char* filename){
  FILE *fp;
  char str[100];
  regex_t regex;
  regmatch_t m[50];
  int regExErr1 = regcomp(&regex, "[sub]", REG_EXTENDED|REG_NEWLINE);
  if( regExErr1 ) {
    return;
  }
  fp=fopen(filename,  "r");
  if (fp == NULL){
        printf("Could not open file %s",filename);
        return;
    }
    int i = 0;
    while (fgets(str, 100, fp) != NULL){
        regExErr1 = regexec(&regex, str, 10, m, 0);
        if( regExErr1 != 0 ){
            continue;}

            printf("entering loop at index %i\n", i);
            int start = m[i].rm_so;
            int finish = m[i].rm_eo;
            char result[(finish - start)];
            i++;
    }
    fclose(fp);
    return;
}
*/
int main(int argc, char *argv[]){
FILE *fp;
char *str;
regex_t regex;
regmatch_t m[50];
int regExErr1 = regcomp(&regex, "[sub]", REG_EXTENDED|REG_NEWLINE);
if( regExErr1 ) {
  return;
}
fp=fopen(argv[1],  "r");
if (fp == NULL){
      printf("Could not open file");
      return;
  }
  int i = 0;
  while (fgets(str, 100, fp) != NULL){
      regExErr1 = regexec(&regex, str, 10, m, 0);
      if( regExErr1 != 0 ){
          continue;}

          printf("entering loop at index %i\n", i);
          int start = m[i].rm_so;
          int finish = m[i].rm_eo;
          char result[(finish - start)];
          strcpy(result, strstr(("%.*s\n", (finish - start), str + start), "<"));
          printf("function, %s", result);
          i++;
  }
  fclose(fp);
  return;
}
