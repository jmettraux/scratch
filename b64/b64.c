
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char sixfours[64] =
  "abcdefghijklmnopqrstuvwxyz"
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "0123456789"
  "+/";

char *encode(char *s)
{
  size_t l = strlen(s);

  char *r = calloc(2 * l, sizeof(char));
  size_t j = 0;

  for (size_t i = 0; i < l; )
  {
    char a = s[i++]; char b = s[i++]; char c = s[i++];

    int w = 0; int x = 0; int y = 0; int z = 0;

    r[j++] = sixfours[w];
    r[j++] = sixfours[x];
    r[j++] = sixfours[y];
    r[j++] = sixfours[z];
  }

  return r;
}

int main()
{
  //char *lev =
  //  "Man is distinguished, not only by his reason, but by this singular "
  //  "passion from other animals, which is a lust of the mind, that by a "
  //  "perseverance of delight in the continued and indefatigable generation "
  //  "of knowledge, exceeds the short vehemence of any carnal pleasure.";
  char *lev = "Man is";

  //char *out =
  //  "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0"
  //  "aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1"
  //  "c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0"
  //  "aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdl"
  //  "LCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";
  char *out = "TWFuIGlz";

  puts("");
  printf(">%s<\n", lev);
  puts("  --encode-->");
  printf(">%s<\n", encode(lev));
  puts("  == ?");
  printf(">%s<\n", out);
  puts("");
}

