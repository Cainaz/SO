#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define clear() printf("\033[H\033[J")
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int lsh_cd(char **args);
int lsh_ajuda(char **args);
int lsh_sair(char **args);
void init();

void init(){
  clear();
    printf("\n\n\t          -BEM VINDO-");
    printf("\n\n\n*******************"
        "***********************\n\n");
  printf("            ▐▓█▀▀▀▀▀▀▀▀▀█▓▌░▄▄▄▄▄░\n");
  printf("            ▐▓█░░▀░░▀▄░░█▓▌░█▄▄▄█░\n");
  printf("            ▐▓█░░▄░░▄▀░░█▓▌░█▄▄▄█░\n");
  printf("            ▐▓█▄▄▄▄▄▄▄▄▄█▓▌░█████░\n");
  printf("            ░░░░▄▄███▄▄░░░░░█████░\n");
  printf("\n\n User: %s ""\n ",getenv("USER"));
  sleep(1);
}

char *builtin_str[] = {
  "cd",
  "ajuda",
  "sair"
};

int (*builtin_func[]) (char **) = {
  &lsh_cd,
  &lsh_ajuda,
  &lsh_sair
};

int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: Argumento para \"cd\" esperado \n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

int lsh_ajuda(char **args)
{
  int i;
  printf("LSH do Cainã\n");
  printf("Digite nome de programas e argumentos, e aperte enter.\n");
  printf("Estes são os programas que estão programados:\n");

  for (i = 0; i < lsh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  printf("Use o comando man para informacoes em outros programas.\n");
  return 1;
}

int lsh_sair(char **args)
{
  return 0;
}

int lsh_launch(char **args)
{
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
  } else {
    // Parent process
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int lsh_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < lsh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return lsh_launch(args);
}

#define LSH_RL_BUFSIZE 1024

char *lsh_read_line(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "lsh: Erro de alocação\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    if (c == EOF) {
      exit(EXIT_SUCCESS);
    } else if (c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: Erro de alocação\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char **lsh_split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) {
    fprintf(stderr, "lsh: Erro de alocação\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
		free(tokens_backup);
        fprintf(stderr, "lsh: Erro de alocacao\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

void print_dir(void){
  char cwd [1024];
  getcwd(cwd,sizeof(cwd));
  printf(ANSI_COLOR_CYAN"\n ㄲ%s:" ANSI_COLOR_GREEN " %s"ANSI_COLOR_RESET,getenv("USER"), cwd);
}

void lsh_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    print_dir();
    printf("ㅎ ");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);

    free(line);
    free(args);
  } while (status);
}

int main(int argc, char **argv)
{
  init();
  lsh_loop();

  return EXIT_SUCCESS;
}

