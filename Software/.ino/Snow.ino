uint32_t snow_timer;

#define SNOW_RATE 150

void snow()
{
  if (millis() - snow_timer >= SNOW_RATE)
  {
    snow_timer = millis();

    for (uint8_t y = 7; y > 0; y--)
    {
      for (uint8_t x = 0; x < 8; x++)
      {
        matrix_container[y][x] = matrix_container[y - 1][x];
      }
    }

    for (uint8_t x = 0; x < 8; x++)
    {
      uint8_t snowflake_chance = random(6);
      matrix_container[0][x] = snowflake_chance == 1 ? 1 : 0;
    }
  }
}