
#define _POSIX_C_SOURCE 200809L

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define N 10000000

static long long getms()
{
  struct timeval tv;
  int r = gettimeofday(&tv, NULL);
  return r == 0 ? tv.tv_sec * 1000 + tv.tv_usec / 1000 : 0;
}

int main()
{
  char *s = calloc(1024, sizeof(char));

  puts(". warmup");
  long long ms = getms();
  for (size_t i = 0; i < N; i++)
  {
    sprintf(s, "%zu %i %s", i, 1234, "nada");
  }
  printf("took %llims\n\n", getms() - ms);

  puts(". strcpy");
  ms = getms();
  for (size_t i = 0; i < N; i++)
  {
    strcpy(s, "1234567890abcdefghijklmnop");
  }
  printf("took %llims\n\n", getms() - ms);

  puts(". sprintf");
  ms = getms();
  for (size_t i = 0; i < N; i++)
  {
    sprintf(s, "%zu %i %s", i, 1234, "nada");
  }
  printf("took %llims\n\n", getms() - ms);

  puts(". sprintf without formatting");
  ms = getms();
  for (size_t i = 0; i < N; i++)
  {
    sprintf(s, "1234567890abcdefghijklmnop");
  }
  printf("took %llims\n\n", getms() - ms);

  puts(". sprintf with \"%s\"");
  ms = getms();
  for (size_t i = 0; i < N; i++)
  {
    sprintf(s, "%s", "1234567890abcdefghijklmnop");
  }
  printf("took %llims\n\n", getms() - ms);

  puts(". sprintf with \"-%s-\"");
  ms = getms();
  for (size_t i = 0; i < N; i++)
  {
    sprintf(s, "-%s-", "1234567890abcdefghijklmnop");
  }
  printf("took %llims\n\n", getms() - ms);

  return 0;
}

