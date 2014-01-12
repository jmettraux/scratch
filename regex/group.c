
#include <stdlib.h>
#include <stdio.h>
#include <regex.h>

int main()
{
  regex_t exp;
  regmatch_t ms[2];

  regcomp(&exp, " [=f!]{3} ", REG_EXTENDED);

  int i;
  int r;
  char *s;

  s = "toto === nada";
  r = regexec(&exp, s, 2, ms, 0);
  printf("\"%s\" match ? %s\n", s, (r == 0 ? "yes" : "no"));

  for (i = 0; ; i++)
  {
    if (ms[i].rm_so < 0) break;

    printf("ms[%d]: so:%d, eo:%d\n", i, ms[i].rm_so, ms[i].rm_eo);
    printf(">%s< (%d)\n", s + ms[i].rm_so, ms[i].rm_eo);
  }

  regfree(&exp);
}

