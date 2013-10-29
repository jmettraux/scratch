
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
//#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

// USAGE:
// zest [dir]

// http://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister.html

int str_ends(char *s, char *end)
{
  size_t ls = strlen(s);
  size_t le = strlen(end);

  if (le > ls) return 0;

  return (strncmp(s + ls - le, end, le) == 0);
}

int process_lines(char *path)
{
  FILE *fp = fopen(path, "r");
  if (fp == NULL) return 0;

  char *line = NULL;
  size_t len = 0;

  while (getline(&line, &len, fp) != -1)
  {
    char *l = (char *)strndup(line, strlen(line));
    char *head = strtok(l, " 	(");
    //printf("line:    >%s<\n", line);
    //printf("  head:  >%s<\n", head);

    if (strncmp(head, "describe", 8) == 0)
    {
      puts("D");
    }
    else if (strncmp(head, "context", 7) == 0)
    {
      puts("C");
    }
    else if (strncmp(head, "it", 2) == 0)
    {
      puts("I");
    }
    else
    {
      printf("%s", line);
    }

    free(l);
  }

  free(line);
  fclose(fp);

  return 1;
}

void print_header(char *path)
{
}
void print_footer(char *path)
{
  // deal with -l and -e
  puts("");
  puts("int main(int argc, char *argv[])");
  puts("{");
  puts("}");
}


int process(char *path)
{
  int r = 1;

  print_header(path);

  r = process_lines(path);

  print_footer(path);

  return r;
}

int main(int argc, char *argv[])
{
  char *dir = ".";
  if (argc > 1) dir = argv[1];
  printf("dir: %s\n", dir);

  DIR *dp;
  struct dirent *ep;

  dp = opendir(dir);

  if (dp == NULL)
  {
    perror("couldn't open directory");
    return 1;
  }

  while ((ep = readdir(dp)) != NULL)
  {
    if ( ! str_ends(ep->d_name, "_spec.c")) continue;
    process(ep->d_name);
  }
  closedir(dp);

  return 0;
}

