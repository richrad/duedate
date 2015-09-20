#include "LedControl-MAX7219-MAX7221/LedControl-MAX7219-MAX7221.h"

int dataPin = A5;
int loadPin = A4;
int clockPin = A3;

int dueDate = 1445922000;
int theTime = Time.now();

int numberOfMAX72Chips = 1;
int intensity = 1;

int rows[8] = {0, 0, 0, 0, 0, 0, 0, 0};

LedControl lc = LedControl(dataPin, clockPin, loadPin, numberOfMAX72Chips);

void drawMatrixPen() {
  lc.setRow(0, 0, rows[0]);
  lc.setRow(0, 1, rows[1]);
  lc.setRow(0, 2, rows[2]);
  lc.setRow(0, 3, rows[3]);
  lc.setRow(0, 4, rows[4]);
  lc.setRow(0, 5, rows[5]);
  lc.setRow(0, 6, rows[6]);
  lc.setRow(0, 7, rows[7]);
}

void setRowsForTime() {
    int remaining = dueDate - theTime;
    int days = remaining / ((60 * 60) * 24);
    
    int fullbars = days / 8;
    int dots = days % 8;
    
    for (int i=0; i < 8; i++) {
        if (fullbars > 0) {
            rows[i] = 0xff;
            fullbars--;
        } else if (fullbars == 0) {
            for (int ib = 0; ib < dots; ib++) {
                int dot = 1 << ib;
                rows[i] |= dot;
            }
            fullbars--;
        }
    }
}

void setup() {
    lc.shutdown(0,false);
    lc.setIntensity(0,intensity);
    lc.clearDisplay(0);
}

void loop() {
    theTime = Time.now();
    setRowsForTime();
    drawMatrixPen();
}
