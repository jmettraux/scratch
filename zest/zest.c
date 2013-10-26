
#include <stdio.h>
//#include <sys/types.h>
#include <dirent.h>
#include <string.h>

// USAGE:
// zest [dir]

// http://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister.html

int ends_with(char *s, char *end)
{
  size_t ls = strlen(s);
  size_t le = strlen(end);

  if (le > ls) return 0;

  char *ss = s + ls - le;

  return (strncmp(ss, end, le) == 0);
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
    if ( ! ends_with(ep->d_name, "_spec.c")) continue;
    printf("file: %s\n", ep->d_name);
  }
  closedir(dp);

  return 0;
}
