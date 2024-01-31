#define MAX_COMMETS_AMOUNT 5

uint32_t commets_fall_timer;
uint32_t mlrgfdv_timer;
uint32_t commets_create_timer;

uint8_t commets_amount[MAX_COMMETS_AMOUNT];
uint8_t commets_amount_least[MAX_COMMETS_AMOUNT];
uint8_t commets_amount_greatest[MAX_COMMETS_AMOUNT] = {100, 100, 100, 100, 100};

uint8_t min_y = 255;
int8_t count = -1;
int8_t z;
int8_t col_status[9];  // -1 - col is full; 0 - possible to add a second one; 1 - empty;

void commets()
{
  int speed = 150;
  if (millis() - commets_create_timer >= speed)
  {
    if (millis() - commets_fall_timer >= speed)
    {
      commets_fall_timer = millis();
      commets_create_timer = millis();
      for (int8_t x = 0; x <= 9; x++)
      {
        col_status[x] = 0;
        for (int8_t y = 0; y <= 9; y++)
        {
          if (matrix_arr_temp[x][y] == 0)
          {
            col_status[x]++;
          }
          else
          {
            break;
          }
        }

        //arr_print(matrix_arr_temp);
        if (col_status[x] < 4)
        {
          ;
        }
        else if (col_status[x] >= 3 && col_status[x + 1] > 5 && col_status[x - 1] > 5 && random(100) <= 20)
        {
          if (random(100) >= 35)
          {
            matrix_arr_temp[x][random(1, 2)] = random(3, 4);
          }
          else
          {
            matrix_arr_temp[x][random(1, 2)] = random(2, 3);
          }
        }
        else if (col_status[x] == 8 && col_status[x + 1] > 5 && col_status[x - 1] > 5)
        {
          if (random(100) >= 20)
          {
            matrix_arr_temp[x][random(1, 4)] = random(3, 5);
          }
          else
          {
            matrix_arr_temp[x][random(1, 4)] = random(2, 4);
          }
        }
      }  //for(x)

      count = 0;
      for (int8_t x = 0; x <= 9; x++)
      {
        for (int8_t y = 0; y <= 9; y++)
        {
          matrix_container[x][y] = matrix_arr_temp[x][y];
        }
      }
      arr_print(matrix_container);
      min_y = 255;
      for (int8_t x = 1; x <= 9; x++)
      {
        //acting ->
        count = 0;
        for (int8_t y = 10; y >= 1; y--)
        {
          //ÐÑÐ´ÑÐ°ÑÑÐ½Ð¾Ðº ÑÐ¾Ð±Ð¸ÑÑÑÑ Ð·Ð° ÑÐ¼Ð¾Ð²Ð¸ Ð¿Ð¾Ð·Ð¸ÑÑÑ ÐºÑÑÑÐ¾ÑÐ° Ñ ÑÑÑÐºÐ¾ Ð²Ð¸Ð·Ð½Ð°ÑÐµÐ½ÑÐ¹ Ð¿Ð¾Ð·Ð¸ÑÑÑ ... Ð´Ð¾Ð²Ð¶Ð¸Ð½Ð° Ð¿Ð¾ÑÐ¾ÑÐ½Ð¾Ð³Ð¾ Ð±ÐµÐ·Ð¿ÐµÑÐµÑÐ²Ð½Ð¾Ð³Ð¾ ÑÑÐ¾Ð²Ð¿ÑÑ Ð·Ð½Ð°ÑÐµÐ½Ñ >0
          if (matrix_arr_temp[x][y] > 0)  //matrix_arr_temp[x][y+1]==0
          {
            //echo start count['.x.']['.y.']; ';
            //Ð´Ð¾Ð²Ð¶Ð¸Ð½Ð° >1
            if (matrix_arr_temp[x][y - 1] > 0 && matrix_arr_temp[x][y + 1] == 0)
            {
              count = 0;  //Ð´Ð¾Ð²Ð¶Ð¸Ð½Ð° Ð¿Ð¾ÑÐ¾ÑÐ½Ð¾Ð³Ð¾ Ð±ÐµÐ·Ð¿ÐµÑÐµÑÐ²Ð½Ð¾Ð³Ð¾ ÑÑÐ¾Ð²Ð¿ÑÑ Ð·Ð½Ð°ÑÐµÐ½Ñ >0
              //Ð¿Ð¾ÑÐ¾ÑÐ½Ð° Ðº-ÑÑ ÐµÐ»ÐµÐ¼ÐµÐ½ÑÑÐ² >0
              z = y;
              do
              {
                count++;
                z--;
                //echo 'z='.z.'; ';
              } while (z >= 1 && matrix_arr_temp[x][z] > 0);
            }
            else if (matrix_arr_temp[x][y + 1] == 0 && matrix_arr_temp[x][y - 1] == 0)
            {
              count = 1;
            }
            //echo '<b>matrix_arr_temp[1][2]='.matrix_arr_temp[1][2].';</b> ';
          }

          //ÐÐ°Ð´Ð°ÑÐ¸ Ð·Ð½Ð°ÑÐµÐ½Ð½Ñ Ð´Ð»Ñ Ð½Ð°ÑÑÑÐ¿Ð½Ð¾Ð³Ð¾ (Ð½Ð¸Ð¶ÑÐµ) ÐµÐ»ÐµÐ¼ÐµÐ½ÑÑ Ð² ÑÑÐ¾Ð²Ð¿ÑÑ
          if (1 == 1 && matrix_arr_temp[x][y] > 0)
          {
            matrix_arr_temp[x][y + 1] = matrix_arr_temp[x][y];
            //ÐÐ¸Ð·Ð½Ð°ÑÐµÐ½Ð½Ñ ÑÐ¸ Ð¾Ð±Ð½ÑÐ»ÑÑÐ¸ Ð²ÐµÑÑÐ½Ñ Ð·Ð½Ð°ÑÐµÐ½Ð½Ñ
            //Ð´Ð¾Ð´Ð°ÑÐºÐ¾Ð²Ð¾ Ð¿ÐµÑÐµÐ²ÑÑÑÑÐ¸, ÑÐ¾Ð± Ð¿ÑÐ´ ÑÐ°Ñ "ÑÐ¾ÑÑÑ" Ð½Ðµ Ð¾Ð±Ð½ÑÐ»ÑÑÐ¸ ÑÐ²Ð¾ÑÑÐ¸ ÑÐ½ÑÐ¸Ñ
            if ((y == 8 && count > 0) || count >= matrix_arr_temp[x][y])
            {
              z = y - count + 1;

              if (z >= 1)
              {
                matrix_arr_temp[x][z] = 0;
              }
            }
          }
          //--
          count = -1;
        }  //for (y)
      }  //for(x)

      //Ð·Ð½Ð°ÑÐµÐ½Ð½Ñ Ð² ÑÑÐ´ÐºÑ #9 Ð·Ð°Ð²Ð¶Ð´Ð¸ Ð½ÑÐ»Ñ
      for (int8_t x = 0; x <= 9; x++)
      {
        matrix_arr_temp[x][9] = 0;
      }
    }  //timer
  }  //timer2
}  // function
