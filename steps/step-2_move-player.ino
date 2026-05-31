#include <U8g2lib.h>
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

#define STICK_UP 1
#define STICK_LEFT 2
#define STICK_RIGHT 3
#define STICK_DOWN 4
#define STICK_BTN 5
#define MESA_BTN 19
#define A_BTN 20
#define B_BTN 24
#define VOLTAGE 8

float player_x = 56;
float player_y = 60;

bool game_over = false;

void setup() {
  u8g2.begin();
  pinMode(STICK_LEFT, INPUT_PULLUP);
  pinMode(STICK_RIGHT, INPUT_PULLUP);
}

void loop() {
  u8g2.firstPage();
  do {
    if (!game_over) {
      // Move player
      if (!digitalRead(STICK_LEFT) && player_x > 0) {
        player_x -= 0.3;
      }
      if (!digitalRead(STICK_RIGHT) && player_x < 112) {
        player_x += 0.3;
      }
    }
 
    // Draw player
    u8g2.setFont(u8g2_font_unifont_t_animals);
    u8g2.drawGlyph(player_x, player_y, 41);

  } while ( u8g2.nextPage() );
}
