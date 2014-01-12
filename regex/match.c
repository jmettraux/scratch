
#include <stdlib.h>
#include <stdio.h>
#include <regex.h>

int main()
{
  regex_t exp;
  regcomp(&exp, " [=f!]{3} ", REG_EXTENDED | REG_NOSUB);

  int r;
  char *s;

  s = "toto === nada";
  r = regexec(&exp, s, 0, NULL, 0);
  printf("\"%s\" match ? %s\n", s, (r == 0 ? "yes" : "no"));

  s = "toto ?== nada";
  r = regexec(&exp, s, 0, NULL, 0);
  printf("\"%s\" match ? %s\n", s, (r == 0 ? "yes" : "no"));

  regfree(&exp);
}

