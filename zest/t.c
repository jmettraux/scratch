
#include <stdio.h>
#include <wordexp.h>

int main(int argc, char *argv[])
{
  //for (int i = 0; i < argc; i++)
  //{
  //  printf("%d - %s\n", i, argv[i]);
  //}

  wordexp_t we;

  wordexp("../mnemo/*.c ~/surf", &we, 0);
  for (int i = 0; i < we.we_wordc; i++)
  {
    printf("%d - %s\n", i, we.we_wordv[i]);
  }
  wordfree(&we);
}

