#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string_utils.h"
#include "proc_utils.h"
#include <stdbool.h>

void print_errno_to_standard_error(char* file, int line) {
  fprintf(stderr, ANSI_COLOR_RED "[ERROR] Called from:\n");
  fprintf(stderr, "file: %s | line: %d\n", file, line);
  fprintf(stderr, "errno %d: ", errno);
  char *err_str = strerror(errno);
  fprintf(stderr, "%s\n", err_str);
}

int sepparate_input_into_commands(char *input, char *commands[MAX_INPUT / 2 + 1]) {
  remove_line_breaks(input);
  int index = 0;
  char *piece;

  piece = strtok(input, ";");
  while (piece != NULL) {
    // fprintf(stdout, "Piece %s", piece);
    commands[index] = piece;
    index++;
    piece = strtok(NULL, ";");
  }

  commands[index] = NULL;
  return index;
}

void sepparate_command_into_args(char *command, proc_args *arg_struct) {
  remove_line_breaks(command);
  char *cmd_copy = (char *) malloc(sizeof(char*) * strlen(command));
  strcpy(cmd_copy, command);
  char *args[MAX_ARGS];
  int index = 0;
  char *piece;

  // fprintf(stdout, "%s\n", command);
  piece = strtok(command, " ");
  while (piece != NULL) {
    // fprintf(stdout, "%s\n", command);

    if (piece[0] == '\"') {
      do {
        strtok(NULL, " ");
      } while (piece[strlen(piece - 1)] != '\"');

      char string[MAX_ARG_SIZE];
      extract_strings_in_quotes(cmd_copy, string);
      strcpy(args[index], string);

      index++;
    }
    else {
      // strcpy(args[index], piece);
      args[index] = piece;
      index++;
    }
    // fprintf(stdout, "%s\n", piece);
    piece = strtok(NULL, " ");
  }

  arg_struct->proc_name = args[0];
  arg_struct->args = args;
  arg_struct->args[index] = NULL;

  free(cmd_copy);
}

void remove_line_breaks(char *str) {
  for (int i = 0; i < (int) strlen(str); i++) {
    if (str[i] == '\n' || str[i] == EOF) {
      str[i] = 0;
    }
  }
}

char* extract_strings_in_quotes(char *full_str, char *res) {
  int count = 0;
  // fprintf(stdout, "%s\n", full_str);

  for (int i = 0; i < (int) strlen(full_str); i++) {
    if (full_str[i] == '\"') {
      do {
        // printf("test\n");
        res[count] = full_str[i];
        // printf("test2\n");
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
