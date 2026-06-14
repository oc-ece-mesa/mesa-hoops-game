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

float player_x = 56;
float player_y = 60;

float hoop_x = 40;
float hoop_y = -8;

int score = 0;
bool got_hoop = false;
bool game_over = false;

void setup() {
  u8g2.begin();
  pinMode(STICK_LEFT, INPUT_PULLUP);
  pinMode(STICK_RIGHT, INPUT_PULLUP);
  randomSeed(analogRead(10));
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
 
      // Move hoop
      hoop_y += 0.25;

      // Check if player is in hoop
      if (player_x + 8 >= hoop_x - 16
      && player_x + 8 <= hoop_x + 16
      && player_y - 8 >= hoop_y - 8
      && player_y - 8 <= hoop_y + 8
      && !got_hoop) {
        got_hoop = true;
        score++;
      }

      // Reset hoop & check for game over
      if (hoop_y > 64) {
        if (got_hoop) {
          hoop_y = -8;
          hoop_x = random(0, 96);
          got_hoop = false;
        }
        else {
          game_over = true;
        }
      }
    }
    else {
      u8g2.drawStr(40, 32, "GAME OVER");
    }

    // Draw player
    u8g2.setFont(u8g2_font_unifont_t_animals);
    u8g2.drawGlyph(player_x, player_y, 41);

    // Draw hoop
    u8g2.drawEllipse(hoop_x, hoop_y, 16, 8);

    // Draw score counter
    u8g2.setFont(u8g2_font_5x8_tr);
    char score_text[8];
    itoa(score, score_text, 10);
    u8g2.drawStr(100, 8, score_text);

    // Battery indicator
    u8g2.drawFrame(0, 0, 10, 5);
    u8g2.drawBox(0, 0, int(analogRead(VOLTAGE)*0.0174 - 8.33), 5);
    u8g2.drawPixel(10, 3);

  } while ( u8g2.nextPage() );
}
