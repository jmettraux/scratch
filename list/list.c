
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

#include <time.h>
#include <stdio.h>
#include <stdint.h>

#define L (long unsigned)1000000
  // ~ max on the stack for my GNU/Linux

// to use clock_gettime, had to
//
//   CFLAGS= -g -Wall -O3 -D_POSIX_C_SOURCE=199309L -lrt
//
double now()
{
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  return ts.tv_sec + ts.tv_nsec * 1e-9;
}

int main(int argc, char *argv[])
{
  //
  // array

//  char *toto = "toto";
//  char *array[] = { "ab", "cd" };
//
//  printf("%s\n", toto);
//  printf("%s\n", array[0]);
//  printf("%s\n", array[1]);
//
//  char *a2[2];
//  a2[0] = array[0];
//  a2[1] = array[1];
//
//  printf("%s\n", a2[0]);
//  printf("%s\n", a2[1]);

  char *toto = "toto";
  printf("%lu\n", SIZE_MAX);
  printf("%s\n", toto);
  //return 0;

  for (int ii = 0; ii < 3; ii++)
  {
    double start = now();

    char *array[L];
    for (size_t i = 0; i < L; i++)
    {
      //if (i % 10000 == 0) printf("%lu\n", i);
      array[i] = toto;
    }

    double delta = now() - start;
    printf("%fs\n", delta);
  }

  printf("%lu\n", L - 1);
  //printf("<%s>\n", array[L - 1]);
}

