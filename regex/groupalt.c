
#include <stdio.h>
#include <regex.h>

int main()
{
  size_t groups = 2;
  regex_t rex;
  regcomp(&rex, "(i|zu|ll)", REG_EXTENDED);
  regmatch_t ms[groups];
  int r;
  char *s;

  s = "a";
  r = regexec(&rex, s, groups, ms, 0);
  printf("\"%s\" matches? %s\n", s, r ? "no" : "yes");

  s = "i";
  r = regexec(&rex, s, groups, ms, 0);
  printf("\"%s\" matches? %s\n", s, r ? "no" : "yes");

  s = "zu";
  r = regexec(&rex, s, groups, ms, 0);
  printf("\"%s\" matches? %s\n", s, r ? "no" : "yes");

  s = "ll";
  r = regexec(&rex, s, groups, ms, 0);
  printf("\"%s\" matches? %s\n", s, r ? "no" : "yes");

  s = "lln";
  r = regexec(&rex, s, groups, ms, 0);
  printf("\"%s\" matches? %s\n", s, r ? "no" : "yes");
}
