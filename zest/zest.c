
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
//#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

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

//
// the stack

typedef struct level_s {
  struct level_s *parent;
  char *type;
  char *title;
} level_s;

void push(level_s **stack, char *type, char *title)
{
  level_s *l = malloc(sizeof(level_s));
  l->parent = *stack;
  l->type = strndup(type, strlen(type));
  l->title = strndup(title, strlen(title));
  *stack = l;
}

level_s *pop(level_s **stack)
{
  level_s *t = *stack;
  *stack = t->parent;
  return t;
}

//void free_level(level_s *l)
//{
//  free(l->type);
//  free(l->title);
//  free(l);
//}
//void free_stack(level_s **stack)
//{
//  if (stack == NULL) return;
//  level_s *parent = (*stack)->parent;
//  free_level(*stack);
//  free_stack(&parent);
//}

//
// processing work

char *extract_head(char *line)
{
  char *stop = strpbrk(line, "     (");

  if (stop == NULL) return strdup(line);
  if (stop == line) return extract_head(line + 1);
  return strndup(line, stop - line);
}

char *extract_title(char *line)
{
  char *start = strpbrk(line, "\"");
  if (start == NULL) return NULL;
  char *end = strpbrk(start + 1, "\"");
  if (end == NULL) return NULL;
  return strndup(start + 1, end - start - 1);
}

int process_lines(char *path)
{
  FILE *fp = fopen(path, "r");
  if (fp == NULL) return 0;

  level_s *stack = NULL;

  char *line = NULL;
  size_t len = 0;

  while (getline(&line, &len, fp) != -1)
  {
    char *head = extract_head(line);
    char *title = extract_title(line);
    //printf("line:    >%s<\n", line);
    //printf("  head:   >%s<\n", head);
    //printf("  title:  >%s<\n", title);

    if (strncmp(head, "describe", 8) == 0)
    {
      printf("D >%s<\n", title);
      //push(&stack, head, line);
    }
    else if (strncmp(head, "context", 7) == 0)
    {
      printf("C >%s<\n", title);
      //push(&stack, head, line);
    }
    else if (strncmp(head, "it", 2) == 0)
    {
      printf("I >%s<\n", title);
      //push(&stack, head, line);
    }
    else
    {
      printf("%s", line);
    }

    free(head);
    free(title);
  }

  free(line);
  fclose(fp);

  puts("---");
  printf("top: %p\n", stack);
  level_s *top = stack;
  while (1)
  {
    if (top == NULL) break;
    printf("level: %s '%s'\n", top->type, top->title);
    top = top->parent;
  }
  puts("---");

  //free_stack(&stack);

  return 1;
}

void print_header(char *path)
{
}
void print_footer(char *path)
{
  // deal with -l and -e
  puts("");
  puts("int main(int argc, char *argv[])");
  puts("{");
  puts("}");
}


int process(char *path)
{
  int r = 1;

  print_header(path);

  r = process_lines(path);

  print_footer(path);

  return r;
}

int main(int argc, char *argv[])
{
  char *dir = ".";
  if (argc > 1) dir = argv[1];
  printf("dir: %s\n", dir);

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
    process(ep->d_name);
  }
  closedir(dp);

  return 0;
}

