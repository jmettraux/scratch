
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

int process(char *path)
{
  FILE *fp = fopen(path, "r");
  if (fp == NULL) return 0;

  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, fp) != -1)
  {
    line[strlen(line) - 1] = '\0';
    printf("line: >%s<\n", line);
  }

  free(line);
  fclose(fp);

  return 1;
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

