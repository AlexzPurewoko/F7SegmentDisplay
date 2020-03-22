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


#include "TextSegment.h"
#include <Arduino.h>
#include <Shift8RegisterOut.h>
#ifndef __F7_4SEGMENT_DISPLAY__
#define __F7_4SEGMENT_DISPLAY__

typedef struct __disps_ {
  _bits_ *pointToDisp;
  bool hasDotted;
  bool isDisplayOff;
} DisplayPoint;
class F7SegmentDisplay {
  public:
    F7SegmentDisplay(Shift8RegisterOut *shift){
      this -> _shift = shift;
      begin();
    }
    void begin();
    
    // Show all the characters on defined memory locations
    // but, its limited up to 4 characters to displays.
    void showAll(_bits_ **chrs);
    
    // Show all the characters on defined memory locations
    // With the form of DisplayPoint struct's
    // and its limited up to 4 characters to displays.
    void showAll(DisplayPoint *dPoints, int dispSizes = 4);
    
    // Shows all the defined up to 4 characters.
    // With the animation displayed.
    void animationWords4(_bits_ **displayWords, int sizeWords = 4);
    
    // Shows all the charactes no limited (the memory limits)
    // With animation From left and duration between characters.
    void animateFromLeft4(_bits_ **displays, int countWords, int durationBetweenWords = 512);
  private:
    Shift8RegisterOut *_shift;
    short _ids = 0x2a;
    void xshw(int numDisp, _bits_ *chars, bool hasDotted = false);
    void clears();
    void apply();
};

void F7SegmentDisplay::begin() {
  _shift -> reservePin(0, 12, _ids);
}

void F7SegmentDisplay::showAll(_bits_ **chrs) {
  for (int nx = 0; nx < 4; nx++) {
    xshw(nx + 1, chrs[nx], false);
  }
}

void F7SegmentDisplay::showAll(DisplayPoint *dPoints, int dispSizes /* = 4 */) {
  if (dispSizes > 4) return;
  for (int nx = 0; nx < dispSizes; nx++) {
    DisplayPoint *point = &dPoints[nx];
    if (!(point -> isDisplayOff))
      xshw(nx + 1, point -> pointToDisp, point -> hasDotted);
  }
}
void F7SegmentDisplay::animationWords4(_bits_ **displayWords, int sizeWords /* = 4 */) {
  if (sizeWords > 4) return;
  int delayBetweenWords = 1000;
  delay (1500);

  // slide left
  for (int x = 0; x < sizeWords; x++) {
    clears();
    for (int de = 0; de < delayBetweenWords; de++) {
      int steps = x + 1;
      for (int y = steps; y > 0 ; y--) {
        xshw(sizeWords - y + 1, displayWords[steps - y]);
      }
      delayMicroseconds(de);
    }
  }

  // lets we force display the words (all)
  clears();
  delay(delayBetweenWords / 2);
  for (int de = 0; de < delayBetweenWords; de++) {
    for (int x = 0; x < sizeWords; x++) {
      xshw(x + 1, displayWords[x]);
    }
    delayMicroseconds(de);
  }

  // fade out for slide left (decrease the number [gone])

  for (int x = sizeWords; x >= 0; x--) {
    clears();
    int steps = x + 1;
    int startsDisplay = x;
    for (int de = 0; de < delayBetweenWords; de++) {
      int startsElement = sizeWords - x;
      for (int y = 1; y <= startsDisplay && startsElement != sizeWords; y++) {
        xshw(y, displayWords[startsElement++]);
      }
      delayMicroseconds(de);
    }
  }
}

void F7SegmentDisplay::animateFromLeft4(_bits_ **displays, int countWords, int durationBetweenWords /* = 512 */) {
  durationBetweenWords *= 2;
  int startStrips = 1;
  int endStrips = 4;
  int startWordArrs = -1;
  int endWordArrs = -1;
  int startDisplayWords = 0;
  int endDisplayWords = 0;

  bool isReversed = false;
  while (true) {
    clears();
    for (int d = 0; d < durationBetweenWords; d++) {
      if (startStrips > 0 && endStrips <= 4) {
        for (int x = startStrips; x <= endStrips; x++) {
          xshw(x, _strips);
        }
      }

      if (startWordArrs >= 0 && endWordArrs < countWords && startDisplayWords > 0 && endDisplayWords <= 4) {
        for (int x = startDisplayWords, y = startWordArrs; x <= endDisplayWords && y <= endWordArrs; x++, y++) {
          xshw(x, displays[y]);
        }
      }
      //delayMicroseconds(1);
    }

    endWordArrs = (endWordArrs < countWords - 1) ? endWordArrs + 1 : endWordArrs;
    if (!isReversed) {
      endStrips = (endStrips == 0 ) ? 0 : endStrips - 1;
      startStrips = (endStrips == 0) ? 0 : startStrips;
      startWordArrs = (startDisplayWords != 1) ? 0 : startWordArrs + 1;
      startDisplayWords = endStrips + 1;
      endDisplayWords = startDisplayWords + (endWordArrs - startWordArrs);

      isReversed = (((endWordArrs + 1) - (startWordArrs + 1)) < 4 && endWordArrs + 1 == countWords) ;
    } else {
      if (endDisplayWords - 1 < 1) break;
      startDisplayWords = 1;
      startWordArrs = (startWordArrs < countWords - 1) ? startWordArrs + 1 : startWordArrs;
      endStrips = 4;
      startStrips = (endWordArrs - startWordArrs) + 2;
      endDisplayWords = startStrips - 1;
    }

  }
}
void F7SegmentDisplay::xshw(int numDisp, _bits_ *chars, bool hasDotted /* = false */) {
  // clear all displays...
  for (int cx = 0; cx < 4; cx++) {
    _shift -> set(8 + cx, LOW, _ids);
  }
  _shift -> set(7 + numDisp, HIGH, _ids);

  //copy all bits from chars to IC's
  for (int nx = 0; nx < 8; nx++) {
    _shift -> set(nx, chars[nx], _ids);
  }
  _shift -> set(7, !hasDotted, _ids);
  apply();
}

void F7SegmentDisplay::clears() {
  for (int cx = 0; cx < 4; cx++) {
    _shift -> set(8 + cx, LOW, _ids);
  }
  for (int nx = 0; nx < 8; nx++) {
    _shift -> set(nx, HIGH, _ids);
  }
  apply();
}

void F7SegmentDisplay::apply() {
  _shift -> flush();
}
#endif
