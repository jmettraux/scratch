
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

//#define xstr(s) str(s)
//#define str(s) #s

#define _TOKENPASTE(x, y) x ## y
#define TOKENPASTE(x, y) _TOKENPASTE(x, y)


#ifndef ZEST_H
#define ZEST_H

  #define TEST_NAME TOKENPASTE(test_, __LINE__)

  #define describe(T) zest_push_describe(T);
  #define context(T) zest_push_context(T);
  #define end zest_pop();
  #define it(T) zest_flag_test(__LINE__, __FILE__); void TEST_NAME()

  #define ensure(s) zest_ensure(s)

#endif // ZEST_H

