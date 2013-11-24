
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
//#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define TEST_FUNCNAME_LEN 210

#define HEADER "\n\
int fail(int sc, char *s[], char *fname, int lnumber)\n\
{\n\
  return 0;\n\
}\n\
"
#define FOOTER "\n\
int main(int argc, char *argv[])\n\
{\n\
}\n\
\n\
"
  // TODO: deal with -l, -e and co

// USAGE:
// zest [dir]

// http://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister.html

//
// helper functions

int str_ends(char *s, char *end)
{
  size_t ls = strlen(s);
  size_t le = strlen(end);

  if (le > ls) return 0;

  return (strncmp(s + ls - le, end, le) == 0);
}

/*
//
// test function result struct

typedef struct result_s {
  char *title;
  //char *line;
  char *fname;
  int lnumber;
} result_s;

result_s *fail(char *title, char *fname, int lnumber)
{
  result_s *r = malloc(sizeof(result_s));
  r->title = strdup(title);
  //r->line = strdup(line);
  r->fname = strdup(fname);
  r->lnumber = lnumber;
  return r;
}

void free_result(result_s *r)
{
  free(r->title);
  //free(r->line);
  free(r->fname);
  free(r);
}
*/

//
// the stack

typedef struct level_s {
  struct level_s *parent;
  int indent;
  char type;
  char *title;
} level_s;

void push(level_s **stack, int indent, char type, char *title)
{
  level_s *l = malloc(sizeof(level_s));
  l->parent = *stack;
  l->indent = indent;
  l->type = type;
  l->title = strdup(title);
  *stack = l;
}

int depth(level_s **stack)
{
  level_s *top = *stack;

  if (top->parent == NULL) return 1;
  return 1 + depth(&(top->parent));
}

void free_level(level_s *l)
{
  free(l->title);
  free(l);
}

int pop(level_s **stack)
{
  if (*stack == NULL) return 1;
  //printf("pop: %p -> %p -> %p\n", stack, *stack, (*stack)->parent);
  level_s *t = *stack;
  *stack = t->parent;
  free_level(t);
  return 0;
}

void free_stack(level_s **stack)
{
  while( ! pop(stack)) {}
}

char *str_neuter(char *s)
{
  char *r = strdup(s);
  char *c = r;

  while(*c != '\0')
  {
    if (
      ! (
        (*c >= 48 && *c <= 57) ||   // 0 to 9
        (*c >= 97 && *c <= 122) ||  // a to z
        (*c >= 65 && *c <= 90)      // A to Z
      )
    ) *c = '_';
    ++c;
  }

  return r;
}

char **list_titles(level_s **stack)
{
  int d = depth(stack);
  level_s *top = *stack;

  char **result = malloc(d * TEST_FUNCNAME_LEN * sizeof(char));

  for (int i = d - 1; i >= 0; i--)
  {
    result[i] = strdup(top->title);
    top = top->parent;
  }

  return result;
}

char *list_titles_as_literal(level_s **stack)
{
  int d = depth(stack);

  char **titles = list_titles(stack);

  char *r = (char *)malloc((d + 1) * (4 + TEST_FUNCNAME_LEN) * sizeof(char));
  char *rr = r;

  strcpy(rr, "{ ");
  rr += 2;

  for (int i = 0; i < d; i++)
  {
    strcpy(rr, "\"");
    rr += 1;
    strcpy(rr, titles[i]);
    rr += strlen(titles[i]);
    free(titles[i]);
    strcpy(rr, "\"");
    rr += 1;
    if (i < d - 1) { strcpy(rr, ", "); rr += 2; }
  }

  strcpy(rr, " }");
  rr += 2;
  *rr = '\0';

  free(titles);

  return r;
}

char *compute_test_function_name(level_s **stack, int lnumber)
{
  int d = depth(stack);

  char **titles = list_titles(stack);

  char *r = (char *)malloc(d * TEST_FUNCNAME_LEN * sizeof(char));
  char *rr = r;

  strcpy(rr, "test__");
  rr += 6;

  for (int i = 0; i < d; i++)
  {
    char *n = str_neuter(titles[i]);
    strcpy(rr, n);
    rr += strlen(titles[i]);
    strcpy(rr, "__");
    rr += 2;
    free(n);
    free(titles[i]);
  }

  rr += sprintf(rr, "%d", lnumber);
  *rr = '\0';

  free(titles);

  return r;
}

//
// processing work

int extract_indent(char *line)
{
  for (int i = 0; i < strlen(line); i++)
  {
    if (*(line + i) == ' ') continue;
    if (*(line + i) == '\t') continue;
    return i;
  }
  return -1;
}

char *extract_head(char *line)
{
  char *stop = strpbrk(line, "     (");

  if (stop == NULL) return strdup(line);
  if (stop == line) return extract_head(line + 1);
  return strndup(line, stop - line);
}

char *extract_string(char *line)
{
  char *l = line;
  char *r = (char *)calloc(strlen(line), sizeof(char));
  char *rr = r;

  while (1)
  {
    if (*l == '\0') break;
    if (*l == '\\' && *(l + 1) == '"') ++l;
    else if (*l == '"') break;
    *(rr++) = *l;
    ++l;
  }

  if (*l == '"') return r;

  free(r);
  return NULL;
}

char *extract_title(char *line)
{
  char *start = strpbrk(line, "\"");
  if (start == NULL) return NULL;

  return extract_string(start + 1);
}

char *extract_condition(char *line)
{
  char *l = line;
  l = strpbrk(l, "e") + 7;
  int len = strlen(l) - 1;
  return strndup(l, len);
}

int process_lines(FILE *out, char *path)
{
  FILE *fp = fopen(path, "r");
  if (fp == NULL) return 0;

  level_s *stack = NULL;

  int lnumber = 0;
  char *line = NULL;
  size_t len = 0;

  while (getline(&line, &len, fp) != -1)
  {
    int indent = extract_indent(line);
    char *head = extract_head(line);
    char *title = extract_title(line);
    char stype = (stack != NULL) ? stack->type : 'X';

    if (strncmp(head, "describe", 8) == 0)
    {
      if (stype == 'i') pop(&stack);
      push(&stack, indent, 'd', title);
    }
    else if (strncmp(head, "context", 7) == 0)
    {
      if (stype == 'i') pop(&stack);
      push(&stack, indent, 'c', title);
    }
    else if (strncmp(head, "it", 2) == 0)
    {
      push(&stack, indent, 'i', title);
      char *fname = compute_test_function_name(&stack, lnumber);
      char *s = list_titles_as_literal(&stack);
      int sc = depth(&stack);
      fprintf(out, "int %s_sc = %i;\n", fname, sc);
      fprintf(out, "char *%s_s[] = %s;\n", fname, s);
      fprintf(out, "int %s()\n", fname);
      free(fname);
      free(s);
    }
    else if (strncmp(head, "ensure", 6) == 0)
    {
      char *con = extract_condition(line);
      char *fname = compute_test_function_name(&stack, lnumber);
      fprintf(
        out,
        "  int r = %s\n", con);
      fprintf(
        out,
        "  if ( ! r) return fail(%s_sc, %s_s, \"%s\", %d);\n",
        fname, fname, path, lnumber);
      free(con);
      free(fname);
    }
    else if (stype != 'i' && (head[0] == '{' || head[0] == '}'))
    {
      // nothing
    }
    else if (stype == 'i' && head[0] == '}' && indent == stack->indent)
    {
      pop(&stack);
      fprintf(out, "  return 1;\n");
      fprintf(out, "%s", line);
    }
    else
    {
      fprintf(out, "%s", line);
    }

    free(head);
    free(title);

    ++lnumber;
  }

  free(line);
  fclose(fp);

  free_stack(&stack);

  return 1;
}

void print_header(FILE *out, char *path)
{
  fprintf(out, HEADER);
}
void print_footer(FILE *out, char *path)
{
  fprintf(out, FOOTER);
}

int process(char *path)
{
  char *fname = (char *)calloc(strlen(path) + 3, sizeof(char));
  strcat(fname, "z_");
  strcat(fname, path);
  FILE *out = fopen(fname, "wb");

  if (out == NULL)
  {
    perror("couldn't open file for writing");
    return 0;
  }

  int r = 1;

  print_header(out, path);

  r = process_lines(out, path);

  print_footer(out, path);

  free(fname);
  fclose(out);

  return r;
}

int main(int argc, char *argv[])
{
  char *dir = ".";
  if (argc > 1) dir = argv[1];

  DIR *dp;
  struct dirent *ep;

  dp = opendir(dir);

  if (dp == NULL)
  {
    perror("couldn't open directory");
    return 1;
  }

  while ((ep = readdir(dp)) != NULL)
  {
    if ( ! str_ends(ep->d_name, "_spec.c")) continue;
    if (strncmp(ep->d_name, "z_", 2) == 0) continue;

    process(ep->d_name);
  }
  closedir(dp);

  return 0;
}

