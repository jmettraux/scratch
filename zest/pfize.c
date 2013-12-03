
//
// Copyright (c) 2013, John Mettraux, jmettraux@gmail.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// Made in Japan.
//

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *escape(char *line)
{
  line[strlen(line) - 1] = '\0';
  char *l = malloc(9 * 80 * sizeof(char));
  char *ll = l;
  int len = strlen(line);
  for (int i = 0; i < len; i++)
  {
    char c = line[i];
    if (c == '"' || c == '%' || c == '\\') *(ll++) = '\\';
    *(ll++) = c;
  }
  *(ll++) = '\0';
  return l;
}

int main(int argc, char *argv[])
{
  FILE *in = fopen(argv[1], "r");
  char *line = NULL;
  size_t len = 0;

  printf("void print_header(FILE *out)\n");
  printf("{\n");

  while (getline(&line, &len, in) != -1)
  {
    char *l = escape(line);
    printf("  fputs(\"%s\\n\", out);\n", l);
    free(l);
  }

  free(line);
  fclose(in);

  printf("}\n");
}

