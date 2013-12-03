
  /*
   * zest header
   */

#include <stdio.h>

char *ze_last_context = NULL;

void ze_red() { printf("[31m"); }
void ze_green() { printf("[32m"); }
void ze_yellow() { printf("[33m"); }
void ze_white() { printf("[37m"); }
void ze_clear() { printf("[0m"); }

void ze_success(int sc, char *s[], char *fname, int lnumber)
{
  ze_green();
  printf("success at line: %s:%d\n", fname, lnumber);
  ze_clear();
  // TODO: change me, and use ze_last_context...
}

int ze_fail(int sc, char *s[], char *fname, int lnumber)
{
  ze_red();
  printf("failed at line: %s:%d\n", fname, lnumber);
  ze_clear();
  return 0;
}

