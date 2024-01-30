

/*#define MAX_COMMETS_AMOUNT 5

uint32_t commets_fall_timer;
uint32_t mlrgfdv_timer;


bool grow_fall[MAX_COMMETS_AMOUNT];
uint8_t commet_length[MAX_COMMETS_AMOUNT];
uint8_t commet_x_coordinates[MAX_COMMETS_AMOUNT] = {5, 2, 3, 6, 0};
uint8_t commet_y_startup[MAX_COMMETS_AMOUNT] = {1, 3, 0, 2, 4};
uint8_t grow_count[MAX_COMMETS_AMOUNT];
uint8_t commet_result_length[MAX_COMMETS_AMOUNT] = {4, 3, 5, 4, 3};
bool commet_burnt[MAX_COMMETS_AMOUNT];
uint8_t stepdowns_amount[MAX_COMMETS_AMOUNT];
int8_t commet_ids_active[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
uint8_t the_least_item = 255;
int8_t xs_busy[MAX_COMMETS_AMOUNT] = {0, 6, 3, 2, 5};

bool status[MAX_COMMETS_AMOUNT];
uint8_t start_point[MAX_COMMETS_AMOUNT];
uint8_t end_point[MAX_COMMETS_AMOUNT];
uint8_t x_point[MAX_COMMETS_AMOUNT];
uint8_t target_length[MAX_COMMETS_AMOUNT];
uint8_t real_length[MAX_COMMETS_AMOUNT];
uint8_t steps_counter[MAX_COMMETS_AMOUNT];
bool commet_burnt[MAX_COMMETS_AMOUNT];
uint8_t active_commets_amount;

void commets()
{
  if (millis() - commets_fall_timer >= 400)
  {
    commets_fall_timer = millis();

    for (uint8_t commet_id = 0; commet_id < 1; commet_id++)
    {
      //create new ->
      if (active_commets_amount == 0 || (commet_burnt && active_commets_amount < MAX_COMMETS_AMOUNT && 1 == 2))
      {
        active_commets_amount++;
        start_point[commet_id] = 0;
        end_point[commet_id] = 2;
        x_point[commet_id] = 5;
        target_length[commet_id] = end_point[commet_id] - start_point[commet_id] + 1;
        status[commet_id] = 0;
        real_length[commet_id] = 0;
      }
      //<- create new

      //draw ->
      for (int8_t y = 0; y < real_length[commet_id]; y++)
      {
        matrix_container[start_point[commet_id]][x_point[commet_id]] = 1;
        if (start_point[commet_id] + y < target_length[commet_id])
        {
          matrix_container[start_point[commet_id] + y][x_point[commet_id]] = 1;
        }
        else
        {
          status[commet_id] = 1;
          real_length[commet_id] = target_length[commet_id];
        }
      }
      if (!status[commet_id])
      {
        real_length[commet_id]++;
      }
      else
      {
        real_length[commet_id] = target_length[commet_id];
      }
      Serial.println(real_length[commet_id]);
      //<- draw
    }
  }
}
*/