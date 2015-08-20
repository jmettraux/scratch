
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <sys/types.h>
#include <limits.h>


int main()
{
  ssize_t s = -1;
  int i = (int)s;

  printf(".\n");
  printf("%zd %d\n", s, i);

  s = INT_MAX;
  i = (int)s;

  printf(".\n");
  printf("%zd %d\n", s, i);
  printf("%d %d\n", s, i);

  s = INT_MAX + 1;
  i = (int)s;

  printf(".\n");
  printf("%zd %d\n", s, i);
  printf("%d %d\n", s, i);

  //s = INT_MAX + 1;
  //i = (int)s;

  printf(".\n");
  printf("%lld %d\n", s, i);

  printf(".\n");
  printf("ssize_t > int ? %i\n", (s > i));
  printf("ssize_t == int ? %i\n", (s == i));

  printf(".\n");

  return 0;
}

