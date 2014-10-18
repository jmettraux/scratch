
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <regex.h>

#define N 5

regex_t rex;

void match(char *s)
{
  regmatch_t ms[N];

  int r = regexec(&rex, s, N, ms, 0);

  printf("*** s \"%s\" matches? %s\n", s, r ? "no" : "yes");

  for (size_t i = 1; i < N; ++i)
  {
    printf("  %zu: >%s<\n", i, strndup(s + ms[i].rm_so, ms[i].rm_eo - ms[i].rm_so));
  }
}

int main()
{
  regcomp(
    &rex,
    " ("
      "(c|i|zu)(!?={1,3})" "|"
      "([=!~\\^\\$]={2,3}[fF]?)"
    ") ",
    REG_EXTENDED);

  match(" === ");
  match(" i== ");
  match(" i=== ");
  match(" ===f ");
  match(" ===F ");
  match(" !==F ");
  match(" zu!== ");
  match(" zu!= ");
  match(" zu== ");
}

