
  /*
   * zest header
   */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *ze_last_context = NULL;

void ze_red() { printf("[31m"); }
void ze_green() { printf("[32m"); }
void ze_yellow() { printf("[33m"); }
void ze_white() { printf("[37m"); }
void ze_clear() { printf("[0m"); }

void ze_result(int success, int sc, char *s[], char *fname, int lnumber)
{
  if (ze_last_context == NULL) ze_last_context = malloc(7 * 80 * sizeof(char));

  char *context = s[sc - 2];

  if (strcmp(ze_last_context, context) != 0)
  {
    for (int i = 0; i < sc - 1; i++)
    {
      for (int ii = 0; ii < i; ii++) printf("  "); // indent
      printf("%s\n", s[i]);
    }
  }

  for (int ii = 0; ii < sc - 1; ii++) printf("  "); // indent
  if (success) ze_green();
  else ze_red();
  printf("%s", s[sc - 1]);
  if ( ! success) printf(" (FAILED)");
  printf("\n");
  ze_clear();

  strcpy(ze_last_context, context);
  ze_last_context[strlen(context)] = '\0';
    // avoiding strdup and the posix_source requirement...
}

void ze_free()
{
  printf("\nTODO: print 'Failures:' summary\n");
  if (ze_last_context != NULL) free(ze_last_context);
}

