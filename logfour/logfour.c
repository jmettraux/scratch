
#include <stdio.h>

typedef struct lo4_logger {
  FILE *stream;
  short level;
} lo4_logger;

void lo4_log(lo4_logger *l, char *msg);
void lo4_t(lo4_logger *l, char *format, ...); // trace
void lo4_d(lo4_logger *l, char *format, ...); // debug
void lo4_i(lo4_logger *l, char *format, ...); // info
void lo4_e(lo4_logger *l, char *format, ...); // error
void lo4_w(lo4_logger *l, char *format, ...); // warn
void lo4_reopen(lo4_logger *l);

int main()
{
}

