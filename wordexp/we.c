
#include <stdio.h>
#include <wordexp.h>

int main(int argc, char *argv[])
{
  char *a = argv[1];

  printf("a >%s<\n", a);

  wordexp_t we;
  wordexp(a, &we, 0);

  for (size_t i = 0; i < we.we_wordc; ++i)
  {
    puts(we.we_wordv[i]);
  }
}

