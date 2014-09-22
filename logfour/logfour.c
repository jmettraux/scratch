
#include <stdio.h>

typedef char *lo4_shaper(char *key, char *value);

char *lo4_default_shaper(char *key, char *value);
  // stamper?
  // filter?
  // ...

typedef struct lo4_logger {
  FILE *stream;
  short level;
  lo4_shaper *shaper;
} lo4_logger;

lo4_logger *lo4_logger_malloc(FILE *stream, short level, lo4_shaper *shaper)
{
  // ...
}
void lo4_logger_free(lo4_logger *l)
{
  // ...
}

void lo4_log(lo4_logger *l, char *msg);
void lo4_t(lo4_logger *l, char *format, ...); // trace
void lo4_d(lo4_logger *l, char *format, ...); // debug
void lo4_i(lo4_logger *l, char *format, ...); // info
void lo4_e(lo4_logger *l, char *format, ...); // error
void lo4_w(lo4_logger *l, char *format, ...); // warn
void lo4_reopen(lo4_logger *l);

int main()
{
  // ...
}

// a single file
  // path to it, so we can re-open it
// a single logger

// --log-level 4
// --log-level info
// --log-file /var/log/flon/flon.log
// --log-format "{date} {pid} {level} {author} {msg}"

// syslog?

