
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>

#include "flu64.h"


unsigned char *md(const char *s)
{
  MD5_CTX c;
  MD5_Init(&c);

  MD5_Update(&c, s, strlen(s));

  unsigned char *d = calloc(16, sizeof(unsigned char));
  MD5_Final(d, &c);

  return d;
}

int main()
{
  unsigned char *d = md("toto");
  printf(">%s<\n", d);
  printf(">%s<\n", flu64_encode((char *)d, -1));

  MD5((unsigned char *)"toto", 4, d);
  printf(">%s<\n", d);
  printf(">%s<\n", flu64_encode((char *)d, -1));
}

