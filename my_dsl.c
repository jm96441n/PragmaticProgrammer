#include <stdio.h>
#define ARG 1
#define NO_ARG 0
#define ARRAY_SIZE(A) (sizeof(A)/sizeof(A[0]))

void doSelectPen(int cmd, int arg) { printf("P %d\n", arg); }
void doPenUp(int cmd, int arg) { printf("U\n"); }
void doPenDown(int cmd, int arg) { printf("D\n"); }
void doPenDir(int cmd, int arg) { printf("%c %d\n", cmd, arg); }

typedef struct  {
  char cmd;
  int hasArg;
  void (*func)(int, int);
} Command;

static Command cmds[] = {
  { 'P', ARG, doSelectPen },
  { 'U', NO_ARG, doPenUp },
  { 'D', NO_ARG, doPenDown },
  { 'N', ARG, doPenDir },
  { 'E', ARG, doPenDir },
  { 'S', ARG, doPenDir },
  { 'W', ARG, doPenDir }
};

Command *findCommand(int);
int getArg(char *buff, int *result);

int main(int argc, char **argv) {
  char buff[100];
  
  while(fgets(buff, sizeof(buff), stdin)) {
    Command *cmd = findCommand(*buff);
    if (cmd) {
      int arg = 0;
      if(cmd->hasArg && !getArg(buff + 1, &arg)) {
        fprintf(stderr, "'%c' needs an argument\n", *buff);
        continue;
      }

      cmd->func(*buff, arg);
    }
  }
}

Command *findCommand(int cmd) {
  int i;

  for (i = 0; i < ARRAY_SIZE(cmds); ++i) {
    if(cmds[i].cmd == cmd) {
      return cmds + i;
    }
  }

  fprintf(stderr, "Unknown command '%c'\n", cmd);
  return 0;
}

int getArg(char *buff, int *result) {
  return sscanf(buff, "%d", result) == 1;
}
