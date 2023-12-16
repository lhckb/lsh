#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "proc_utils.h"
#include "string_utils.h"
#include <stdio.h>
#include <stdlib.h>

void call_exec_seq(proc_args processes[], int comm_count) {
  for (int i = 0; i < comm_count; i++) {
    pid_t pid = fork();

    if (pid > 0) {
      wait(NULL);
    }
    else if (pid == 0) {
      if (execvp(processes[i].proc_name, processes[i].args) == -1) {
        print_errno_to_standard_error(__FILE__, __LINE__);
        exit(EXIT_FAILURE);
      }
      exit(EXIT_SUCCESS);
    }
    else {
      print_errno_to_standard_error(__FILE__, __LINE__);
    }
  }
}

// TODO: Evaluate if this is really parallel
void call_exec_par(proc_args processes[], int comm_count) {
  for (int i = 0; i < comm_count; i++) {
    pid_t pid = fork();

    if (pid == 0) {
      if (execvp(processes[i].proc_name, processes[i].args) == -1) {
        print_errno_to_standard_error(__FILE__, __LINE__);
        exit(EXIT_FAILURE);
      }
      exit(EXIT_SUCCESS);
    }
    else if (pid < 0) {
      print_errno_to_standard_error(__FILE__, __LINE__);
    }

    wait(NULL);
  }
}
