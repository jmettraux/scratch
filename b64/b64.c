
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static char sixfours[64] =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "abcdefghijklmnopqrstuvwxyz"
  "0123456789"
  "+/";

char *encode(char *s, ssize_t l)
{
  if (l < 0) l = strlen(s);

  char *r = calloc(2 * l, sizeof(char));
  size_t j = 0;

  for (size_t i = 0; i < l; )
  {
    char a = s[i++];
    char b = i < l ? s[i++] : 0;
    char c = i < l ? s[i++] : 0;

    int w = a >> 2;
    int x = ((0x03 & a) << 4) | (b >> 4);
    int y = ((0x0f & b) << 2) | (c >> 6);
    int z = 0x3f & c;

    r[j++] = sixfours[w];
    r[j++] = sixfours[x];
    r[j++] = b ? sixfours[y] : '=';
    r[j++] = c ? sixfours[z] : '=';
  }

  return r;
}

int main()
{
  char *lev =
    "Man is distinguished, not only by his reason, but by this singular "
    "passion from other animals, which is a lust of the mind, that by a "
    "perseverance of delight in the continued and indefatigable generation "
    "of knowledge, exceeds the short vehemence of any carnal pleasure.";
  //char *lev = "Man is";

  char *out =
    "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0"
    "aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1"
    "c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0"
    "aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdl"
    "LCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";
  //char *out = "TWFuIGlz";

  puts("");
  printf(">%s<\n", lev);
  puts("  --encode-->");
  printf(">%s<\n", encode(lev, -1));
  puts("  == ?");
  printf(">%s<\n", out);
  puts("");
}

