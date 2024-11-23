uint32_t snow_timer;

#define SNOW_RATE 150

void snow()
{
  if (millis()-snow_timer>=SNOW_RATE)
  {
    snow_timer=millis();
    for (uint8_t x=1; x <= 8; x++)
    {
      for (uint8_t y=8; y>=1; y--)
      {
        matrix_container[x][y]=matrix_container[x][y-1];
      }
    }

    for (uint8_t x=1; x<=8; x++)
    {
      uint8_t snowflake_chance=random(6);
      matrix_container[x][0]=snowflake_chance == 1 ? 1 : 0;
    }
  }
}
