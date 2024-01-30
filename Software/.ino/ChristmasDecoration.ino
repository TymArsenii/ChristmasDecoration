#include <GyverMAX7219.h>
#include <RunningGFX.h>

MAX7219<1, 1, 8> matrix;
RunningGFX running(&matrix);

const char autor[] PROGMEM = "by Arsenii =)   ";
const char merry_christmas[] PROGMEM = "Merry Christmas!   ";
const char year_num[] PROGMEM = "!!!2024!!!   ";
const char new_year[] PROGMEM = "Happy New Year!   ";
const char matrx[] PROGMEM = "8x8 Martix!   ";
const char for_sell[] PROGMEM = "I'm $15 for sell =)   ";

uint32_t refresh_timer;

/*
uint8_t matrix_container[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
};
*/

/*
uint8_t matrix_container[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
};
*/
bool allow = false;

uint8_t matrix_container[9][9];
uint8_t matrix_arr_temp[9][9];

#define REFRESH_RATE 60  //Hz

void setup()
{
  matrix_container[1][2] = 2;
  matrix_container[3][1] = 4;
  matrix_container[5][4] = 2;
  matrix_container[7][1] = 5;

  Serial.begin(115200);
  matrix.begin();
  matrix.setBright(0);
  Serial.println(matrix_container[1][7]);
  delay(1000);

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
  if (1 == 1)
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
  test();
  /*
  if (allow)
  {
    while (1)
    {
      ;
    }
  }
  */
}

void arr_print(uint8_t array[9][9])
{
  for (byte y = 1; y <= 8; y++)
  {
    for (byte x = 1; x <= 8; x++)
    {
      Serial.print(array[x][y]);
      Serial.print(" ");
    }
    Serial.println();
  }
  Serial.println();
}
