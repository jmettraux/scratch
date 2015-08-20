
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <sys/types.h>
#include <limits.h>


int main()
{
  ssize_t s = -1;
  int i = (int)s;

  printf(".0\n");
  printf("%zd %d\n", s, i);

  s = INT_MAX;
  i = (int)s;

  printf(".1\n");
  printf("%zd %d\n", s, i);
  printf("%d %d\n", s, i);

  s = INT_MAX + 1;
  i = (int)s;

  printf(".2\n");
  printf("%zd %d\n", s, i);
  printf("%lld %d\n", s, i);

  s = (ssize_t)INT_MAX + 1; // <------------------------ YES !
  i = (int)s;

  printf(".3\n");
  printf("%lld %d\n", s, i);

  printf(".4\n");
  printf("ssize_t > int ? %i\n", (s > i));
  printf("ssize_t == int ? %i\n", (s == i));

  printf(".5\n");

  printf("SSIZE_MAX %lld\n", SSIZE_MAX);

  return 0;
}

