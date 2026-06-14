#include <U8g2lib.h>
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

#define STICK_UP 1
#define STICK_LEFT 2
#define STICK_RIGHT 3
#define STICK_DOWN 4
#define STICK_BTN 5
#define A_BTN 20
#define B_BTN 24
#define C_BTN 19
#define VOLTAGE 8

void setup() {
  u8g2.begin();
}

void loop() {

}
