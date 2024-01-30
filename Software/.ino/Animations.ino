/*

#define MAX_COMMETS_AMOUNT 5

uint32_t commets_fall_timer;
uint32_t mlrgfdv_timer;
int8_t active_commets_amount = 1;

bool grow_fall[MAX_COMMETS_AMOUNT];
uint8_t commet_length[MAX_COMMETS_AMOUNT];
uint8_t commet_x_axis[MAX_COMMETS_AMOUNT] = {5, 2, 3, 6, 0};
uint8_t commet_y_startup[MAX_COMMETS_AMOUNT] = {1, 3, 0, 2, 4};
uint8_t grow_count[MAX_COMMETS_AMOUNT];
uint8_t commet_result_length[MAX_COMMETS_AMOUNT] = {4, 3, 5, 4, 3};
bool commet_burnt[MAX_COMMETS_AMOUNT];
uint8_t stepdowns_amount[MAX_COMMETS_AMOUNT];
int8_t commet_ids_active[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
uint8_t the_least_item = 255;
int8_t xs_busy[MAX_COMMETS_AMOUNT] = {0, 6, 3, 2, 5};

void commets()
{
  if (millis() - commets_fall_timer >= 150)
  {
    commets_fall_timer = millis();

    for (uint8_t commet_id = 0; commet_id < 5; commet_id++)
    {
      for (int8_t id = 0; id < 5; id++)
      {
        Serial.println(xs_busy[id]);
      }
      Serial.println();
      //create new ->
      if (commet_burnt[commet_id] && active_commets_amount < 5)
      {
        mlrgfdv_timer = millis();
        for (int id = 0; id < 7; id++)
        {
          if (commet_ids_active[id] == -1)
          {
            the_least_item = id;
            break;
          }
        }
        the_least_item = 0;
        active_commets_amount++;
        commet_burnt[commet_id] = false;
        commet_x_axis[commet_id] = random(8);
        bool is_dublicate = false;
        while (true)
        {
          is_dublicate = false;
          for (int8_t id = 0; id < 5; id++)
          {
            if (xs_busy[id] == commet_x_axis[commet_id])
            {
              is_dublicate = true;
              break;
            }
          }
          if (!is_dublicate)
          {
            break;
          }
          if (is_dublicate)
          {
            commet_x_axis[commet_id] = random(8);
          }
        }
        commet_y_startup[commet_id] = random(5);

        switch (commet_y_startup[commet_id])
        {
          case 4:
            commet_result_length[commet_id] = random(2, 4);
            break;
          case 3:
            commet_result_length[commet_id] = random(2, 5);
            break;
          case 2:
            commet_result_length[commet_id] = random(3, 6);
            break;
          default:
            commet_result_length[commet_id] = random(3, 7);
            break;
        }
        commet_result_length[commet_id] = random(3, 5);
        stepdowns_amount[commet_id] = 0;
        grow_fall[commet_id] = false;
        grow_count[commet_id] = 0;
        xs_busy[commet_id] = commet_x_axis[commet_id];
      }

      //<- create new
      //falling ->
      if (grow_fall[commet_id])
      {
        for (uint8_t y = 8; y > 0; y--)
        {
          if (y - 1 <= 0)
          {
            matrix_container[0][commet_x_axis[commet_id]] = 0;
          }
          else
          {
            matrix_container[y - 1][commet_x_axis[commet_id]] = matrix_container[y - 2][commet_x_axis[commet_id]];

            if (stepdowns_amount[commet_id] >= 7)
            {
              // + commet_y_startup[commet_id]
              stepdowns_amount[commet_id] = 0;
              commet_burnt[commet_id] = true;
              commet_ids_active[commet_id] = -1;
              active_commets_amount--;
              xs_busy[commet_id] = -1;
            }
          }
        }
        stepdowns_amount[commet_id]++;
      }
      //<- falling

      //draw_grow ->
      if (!grow_fall[commet_id])
      {
        //+ commet_y_startup[commet_id]
        matrix_container[grow_count[commet_id] + commet_y_startup[commet_id]][commet_x_axis[commet_id]] = 1;
      }
      //<- draw_grow

      //grow ->
      grow_count[commet_id]++;
      if (grow_count[commet_id] >= commet_result_length[commet_id])
      {
        grow_count[commet_id] = commet_result_length[commet_id];
        grow_fall[commet_id] = true;
      }
      else
      {
        grow_fall[commet_id] = false;
      }
      //<- grow
    }
  }
}

*/