
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

void ze_result(int success, int sc, char *s[], char *fname, int lnumber)
{
  for (int i = 0; i < sc - 1; i++)
  {
    for (int ii = 0; ii < i; ii++) printf("  "); // indent
    printf("%s\n", s[i]);
  }

  for (int ii = 0; ii < sc - 1; ii++) printf("  "); // indent
  if (success) ze_green();
  else ze_red();
  printf("%s", s[sc - 1]);
  if ( ! success) printf(" (FAILED)");
  printf("\n");
  ze_clear();
}

