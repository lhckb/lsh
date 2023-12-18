#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* extract_strings_in_quotes(char *full_str, char *res) {
  int count = 0;

  for (int i = 0; i < (int) strlen(full_str); i++) {
    if (full_str[i] == '\"') {
      do {
        res[count] = full_str[i];
        count++;
        i++;
      } while (full_str[i] != '\"');
      res[count++] = '\"';
      res[count] = '\0';
      return res;
    }
  }

  return NULL;
}

int main(void) {
  char *test = "git commit -m \"add files using lsh (now supports string arguments\"";

  char res[1000];
  extract_strings_in_quotes(test, res);

  fprintf(stdout, "%s\n", res);
  fprintf(stdout, "%s\n", test);
}