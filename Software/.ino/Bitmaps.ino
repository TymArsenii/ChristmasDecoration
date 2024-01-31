uint32_t bitmaps_invert_timer;
uint32_t bitmaps_change_timer;

uint8_t bitmap_id;
bool inv;

#define BITMAPS_CHANGE_FREQUENCY 3000
#define BITMAPS_INVERT_FREQUENCY 300
#define BITMAPS_AMOUNT 4

uint8_t heart[10][10] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
uint8_t heart_inv[10][10] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

uint8_t smile[10][10] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

uint8_t cube[10][10] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 0},
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

uint8_t house[10][10] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 0},
    {0, 1, 1, 0, 1, 1, 0, 0, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void bitmaps()
{
  if (millis() - bitmaps_change_timer >= BITMAPS_CHANGE_FREQUENCY * time_multiplyer)
  {
    bitmaps_change_timer = millis();
    bitmap_id++;
    if (bitmap_id > BITMAPS_AMOUNT)
    {
      bitmap_id = 1;
    }
  }
  if (millis() - bitmaps_invert_timer >= BITMAPS_INVERT_FREQUENCY)
  {
    bitmaps_invert_timer = millis();
    inv = !inv;
  }
  //bitmap_id = 1;
  switch (bitmap_id)
  {
    case 1:
      for (uint8_t x = 1; x <= 8; x++)
      {
        for (uint8_t y = 1; y <= 8; y++)
        {
          if (inv)
          {
            matrix_container[x][y] = heart_inv[y][x];
          }
          else
          {
            matrix_container[x][y] = heart[y][x];
          }
          time_multiplyer = 2;
        }
      }
      break;
    case 2:
      for (uint8_t x = 1; x <= 8; x++)
      {
        for (uint8_t y = 1; y <= 8; y++)
        {
          matrix_container[x][y] = smile[y][x];
        }
      }
      time_multiplyer = 1;
      break;
    case 3:
      for (uint8_t x = 1; x <= 8; x++)
      {
        for (uint8_t y = 1; y <= 8; y++)
        {
          matrix_container[x][y] = cube[y][x];
        }
      }
      time_multiplyer = 1;
      break;
    case 4:
      for (uint8_t x = 1; x <= 8; x++)
      {
        for (uint8_t y = 1; y <= 8; y++)
        {
          matrix_container[x][y] = house[y][x];
        }
      }
      time_multiplyer = 1;
      break;
  }
}