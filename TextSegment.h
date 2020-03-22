/**
   Copyright @2020 by Alexzander Purwoko Widiantoro <purwoko908@gmail.com>
   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:
   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#include <Arduino.h>
#ifndef __TEXT_7_SEGMENT_DISPLAY__
#define __TEXT_7_SEGMENT_DISPLAY__

typedef bool _bits_;
// Defined constants for POSITION
/**
 *      - (a   , b   , c  , d   , e  ,  f , g   , dp}
 */
// numbers

_bits_ _n0[] = {LOW, LOW, LOW, LOW, LOW, LOW, HIGH, HIGH};
_bits_ _n1[] = {HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH, HIGH};
_bits_ _n2[] = {LOW, LOW, HIGH, LOW, LOW, HIGH, LOW, HIGH};
_bits_ _n3[] = {LOW, LOW, LOW, LOW, HIGH, HIGH, LOW, HIGH};
_bits_ _n4[] = {HIGH, LOW, LOW, HIGH, HIGH, LOW, LOW, HIGH};
_bits_ _n5[] = {LOW, HIGH, LOW, LOW, HIGH, LOW, LOW, HIGH};
_bits_ _n6[] = {LOW, HIGH, LOW, LOW, LOW, LOW, LOW, HIGH};
_bits_ _n7[] = {LOW, LOW, LOW, HIGH, HIGH, HIGH, HIGH, HIGH};
_bits_ _n8[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH};
_bits_ _n9[] = {LOW, LOW, LOW, LOW, HIGH, LOW, LOW, HIGH};

// Words
_bits_ _a[] = {LOW, LOW, LOW, HIGH, LOW, LOW, LOW, HIGH};
_bits_ _b[] = {HIGH, HIGH, LOW, LOW, LOW, LOW, LOW, HIGH};
_bits_ _c[] = {HIGH, HIGH, HIGH, LOW, LOW, HIGH, LOW, HIGH};
_bits_ _d[] = {HIGH, LOW, LOW, LOW, LOW, HIGH, LOW, HIGH};
_bits_ _e[] = {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW, HIGH};
_bits_ _f[] = {LOW, HIGH, HIGH, HIGH, LOW, LOW, LOW, HIGH};
_bits_ *_g = _n9;
_bits_ _h[] = {HIGH, HIGH, LOW, HIGH, LOW, LOW, LOW, HIGH};
_bits_ *_i = _n1;
_bits_ _j[] = {HIGH, LOW, LOW, LOW, HIGH, HIGH, HIGH, HIGH};
_bits_ _l[] = {HIGH, HIGH, HIGH, LOW, LOW, LOW, HIGH, HIGH};
_bits_ _n[] = {LOW, LOW, LOW, HIGH, LOW, LOW, HIGH, HIGH};
_bits_ *_o = _n0;
_bits_ _p[] = {LOW, LOW, HIGH, HIGH, LOW, LOW, LOW, HIGH};
_bits_ _q[] = {LOW, LOW, LOW, HIGH, HIGH, LOW, LOW, HIGH};
_bits_ _r[] = {LOW, HIGH, HIGH, HIGH, LOW, LOW, HIGH, HIGH};
_bits_ *s = _n5;
_bits_ _t[] = {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, HIGH};
_bits_ _u[] = {HIGH, LOW, LOW, LOW, LOW, LOW, HIGH, HIGH};
_bits_ _x[] = {HIGH, LOW, LOW, HIGH, LOW, LOW, LOW, HIGH};
_bits_ _y[] = {HIGH, LOW, LOW, LOW, HIGH, LOW, LOW, HIGH};
_bits_ *_k = _x;

_bits_ _empty[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
_bits_ _strips[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, HIGH};
#endif
