#define MAX_COMMETS_AMOUNT 5

uint32_t commets_fall_timer;
uint32_t mlrgfdv_timer;

uint8_t commets_amount[MAX_COMMETS_AMOUNT];
uint8_t commets_amount_least[MAX_COMMETS_AMOUNT];
uint8_t commets_amount_greatest[MAX_COMMETS_AMOUNT] = {100, 100, 100, 100, 100};

uint8_t min_y = 255;
int8_t count = -1;
int8_t z;
int8_t is_clear;
int8_t col_status[9];  // -1 - col is full; 0 - possible to add a second one; 1 - empty;
bool created_new;

void test()
{
  created_new = true;
  
  for (int8_t x = 1; x <= 8; x++)
  {
    for (int8_t y = 1; y <= 8; y++)
    {
      if (matrix_container[x][y] > 0 && y < 4)
      {
        if (y < 4)
        {
          col_status[x] = -1;
          break;
        }
        else if (y >= 4)
        {
          col_status[x] = 0;
        }
      }
      else
      {
        col_status[x] = 1;
      }
    }

    switch (col_status[x])
    {
      case -1:
        created_new = false;
        break;
      case 0:
        if (random(100) < 20)
        {
          matrix_container[x][random(1, 2)] = random(2, 3);
        }
        else
        {
          created_new = false;
        }
        break;
      case 1:
        matrix_container[x][random(1, 4)] = random(2, 5);
        break;
    }
  }

  for (int8_t x = 0; x < 9; x++)
  {
    for (int8_t y = 0; y < 9; y++)
    {
      matrix_arr_temp[x][y] = matrix_container[x][y];
    }
  }

  if (millis() - commets_fall_timer >= 300 || created_new)
  {
    created_new = false;
    commets_fall_timer = millis();
    for (int8_t x = 0; x < 9; x++)
    {
      for (int8_t y = 0; y < 9; y++)
      {
        matrix_container[x][y] = matrix_arr_temp[x][y];
      }
    }
    arr_print(matrix_container);

    //inspect ->
    min_y = 255;
    for (int8_t x = 1; x <= 8; x++)
    {
      //acting ->
      count = 0;
      for (int8_t y = 8; y >= 1; y--)
      {
        //Підрахунок робиться за умови позиції курсора у чітко визначеній позиції ... довжина поточного безперервного стовпця значень >0
        if (matrix_container[x][y] > 0)  //matrix_container[x][y+1]==0
        {
          //echo start count['.x.']['.y.']; ';
          //довжина >1
          if (matrix_container[x][y - 1] > 0 && matrix_container[x][y + 1] == 0)
          {
            count = 0;  //довжина поточного безперервного стовпця значень >0
            //поточна к-ть елементів >0
            z = y;
            do
            {
              count++;
              z--;
              //echo 'z='.z.'; ';
            } while (z >= 1 && matrix_container[x][z] > 0);
          }
          else if (matrix_container[x][y + 1] == 0 && matrix_container[x][y - 1] == 0)
          {
            count = 1;
          }
        }

        //Задати значення для наступного (нижче) елементу в стовпці
        if (1 == 1 && matrix_arr_temp[x][y] > 0)
        {
          matrix_arr_temp[x][y + 1] = matrix_arr_temp[x][y];
          //Визначення чи обнуляти верхнє значення
          //додатково перевіряти, щоб під час "росту" не обнуляти хвости інших
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
      }  //for (y...)
      //<- acting
    }

    //значення в рядку #9 завжди нулі
    for (int8_t x = 0; x <= 9; x++)
    {
      matrix_arr_temp[x][9] = 0;
    }

  }  //timer
}  // function
