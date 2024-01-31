#include <GyverMAX7219.h>
#include <RunningGFX.h>

MAX7219<1, 1, 8> matrix;
RunningGFX running(&matrix);

const char autor[] PROGMEM = "by Arsenii =)   ";
const char merry_christmas[] PROGMEM = "Merry Christmas!   ";
const char year_num[] PROGMEM = "!!!2024!!!   ";
const char new_year[] PROGMEM = "Happy New Year!   ";
const char matrx[] PROGMEM = "8x8 Matrix!   ";
const char for_sell[] PROGMEM = "I'm $15 for sale =)   ";

uint32_t refresh_timer;
uint32_t change_timer;
bool allow = false;
uint8_t time_multiplyer;
uint8_t matrix_container[10][9];
uint8_t matrix_arr_temp[10][10];
uint8_t change = 1;
uint16_t change_time;

#define REFRESH_RATE 60  //Hz

void setup()
{
  Serial.begin(115200);
  matrix.begin();
  matrix.setBright(1);

  matrix_container[1][2] = 2;
  matrix_container[3][1] = 4;
  matrix_container[5][4] = 2;
  matrix_container[8][1] = 5;

  for (int8_t x = 0; x < 9; x++)
  {
    for (int8_t y = 0; y < 9; y++)
    {
      matrix_arr_temp[x][y] = matrix_container[x][y];
    }
  }
}

void loop()
{
  if (change != 4)
  {
    if (millis() - refresh_timer >= 1000 / REFRESH_RATE)
    {
      refresh_timer = millis();

      for (uint8_t y = 1; y <= 8; y++)
      {
        for (uint8_t x = 1; x <= 8; x++)
        {
          matrix.dot(8 - x, 8 - y, matrix_container[x][y] > 0 ? 1 : 0);
        }
      }
      matrix.update();
    }
  }

  switch (change)
  {
    case 1:
      matrix.setRotation(0);

      bitmaps();
      change_time = 18000;
      time_multiplyer = 1;
      break;
    case 2:
      matrix.setRotation(0);

      snow();
      change_time = 9000;
      time_multiplyer = 1;
      break;
    case 3:
      matrix.setRotation(0);

      circles();
      change_time = 9000;
      time_multiplyer = 1;
      break;
    case 4:
      matrix.setRotation(2);

      running_string();
      change_time = 38500;
      time_multiplyer = 1;
      break;
    case 5:
      matrix.setRotation(0);

      commets();
      time_multiplyer = 2;
      change_time = 15000;
      break;
  }

  if (millis() - change_timer >= change_time * time_multiplyer)
  {
    change_timer = millis();
    change++;
    if (change > 5)
    {
      change = 1;
    }
    if (change == 5)
    {
      running.stop();
    }
  }
}

void arr_print(uint8_t array[9][9])
{
  for (byte y = 0; y <= 8; y++)
  {
    for (byte x = 0; x <= 8; x++)
    {
      Serial.print(array[x][y]);
      Serial.print(" ");
    }
    Serial.println();
  }
  Serial.println();
}
