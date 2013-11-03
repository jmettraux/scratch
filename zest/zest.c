
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
  char type;
  char *title;
} level_s;

void push(level_s **stack, char type, char *title)
{
  level_s *l = malloc(sizeof(level_s));
  l->parent = *stack;
  l->type = type;
  l->title = strndup(title, strlen(title));
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

char *compute_test_function_name(level_s **stack, int lnumber)
{
  int d = depth(stack);
  level_s *top = *stack;
  level_s *restack = (level_s *)malloc(d * sizeof(level_s));

  for (int i = d - 1; i >= 0; i--)
  {
    restack[i] = *top;
    top = top->parent;
  }

  char *r = (char *)malloc(d * 210 * sizeof(char));
  char *rr = r;

  strcpy(rr, "test__");
  rr += 6;

  for (int i = 0; i < d; i++)
  {
    char *n = str_neuter(restack[i].title);
    strcpy(rr, n);
    free(n);
    rr += strlen(restack[i].title);
    strcpy(rr, "__");
    rr += 2;
  }
  rr += sprintf(rr, "%d", lnumber);
  *rr = '\0';

  free(restack);

  //printf("r: >%s<\n", r);
  return r;
}

//
// processing work

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

int process_lines(char *path)
{
  FILE *fp = fopen(path, "r");
  if (fp == NULL) return 0;

  level_s *stack = NULL;

  int lnumber = 0;
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
      push(&stack, 'd', title);
    }
    else if (strncmp(head, "context", 7) == 0)
    {
      push(&stack, 'c', title);
    }
    else if (strncmp(head, "it", 2) == 0)
    {
      if (stack->type == 'i') pop(&stack);
      push(&stack, 'i', title);
      char *fname = compute_test_function_name(&stack, lnumber);
      printf("int %s()\n", fname);
      printf("STACK->TYPE: %c\n", stack->type);
      free(fname);
    }
    else
    {
      printf("%s", line);
    }

    free(head);
    free(title);

    ++lnumber;
  }

  free(line);
  fclose(fp);

  //puts("---");
  //printf("top: %p\n", stack);
  //level_s *top = stack;
  //while (1)
  //{
  //  if (top == NULL) break;
  //  printf("level: %c '%s'\n", top->type, top->title);
  //  top = top->parent;
  //}
  //puts("---");

  free_stack(&stack);

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
  //printf("dir: %s\n", dir);

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

