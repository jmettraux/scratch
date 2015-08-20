
#include <time.h>

/*
void flon_stamp(fdja_value *o, const char *key)
{
  fdja_value *entry = fdja_v("{}");
  fdja_set(o, key, entry);

  struct timeval tv;
  struct tm *tm;
  char t[28];

  gettimeofday(&tv, NULL);

  tm = gmtime(&tv.tv_sec);
  strftime(t, 20, "%Y%m%d.%H%M%S.", tm);
  sprintf(t + 16, "%li", tv.tv_usec);

  fdja_set(entry, "u", fdja_s(t));

  tm = localtime(&tv.tv_sec);
  strftime(t, 20, "%Y%m%d.%H%M%S", tm);

  fdja_set(entry, "l", fdja_s(t));
}

long long flu_getms()
{
  struct timespec ts;
  int r = clock_gettime(CLOCK_REALTIME, &ts);

  return r == 0 ? ts.tv_sec * 1000 + ts.tv_nsec / 1000000 : 0;
}
*/

int main()
{
  struct tm;
  tm.tm_sec = 0;

  return 0;
}

