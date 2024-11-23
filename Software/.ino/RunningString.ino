uint32_t running_change_timer;
uint8_t running_id;
int running_time_amount=6;

void running_string()
{
  if (millis() - running_change_timer>=running_time_amount)
  {
    running_change_timer=millis();

    running_id++;
    if (running_id>5)
    {
      running_id=1;
    }
    // chr -- 8; ars -- 6; year -- 7; 10 -- sell 5 -- 8x8 matrix; 5 -- 2024;;; all in seconds;;;
    switch (running_id)
    {
      case 1:
        running_time_amount=6000;
      break;
      case 2:
        running_time_amount=7000;
      break;
      case 3:
        running_time_amount=5000;
      break;
      case 4:
        running_time_amount=7000;
      break;
      case 5:
        running_time_amount=5000;
      break;
      case 6:
        running_time_amount=8500;
      break;
    }
    switch (running_id)
    {
      case 1:
        running.setText_P(autor);  //merry_christmas; year_num; new_year; matrx; for_sell
      break;
      case 2:
        running.setText_P(merry_christmas);  //merry_christmas; year_num; new_year; matrx; for_sell
      break;
      case 3:
        running.setText_P(year_num);  //merry_christmas; year_num; new_year; matrx; for_sell
      break;
      case 4:
        running.setText_P(new_year);  //merry_christmas; year_num; new_year; matrx; for_sell
      break;
      case 5:
        running.setText_P(matrx);  //merry_christmas; year_num; new_year; matrx; for_sell
      break;
      case 6:
        running.setText_P(for_sell);  //merry_christmas; year_num; new_year; matrx; for_sell
      break;
    }
    running.setSpeed(15);
    running.start();
  }

  running.tick();
  
}
