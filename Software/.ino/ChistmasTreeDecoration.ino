#include <EEPROM.h>

#include <EncButton.h>
Button btn=Button(3);

#include <GyverMAX7219.h>
#include <RunningGFX.h>

MAX7219<1, 1, 8> matrix;
RunningGFX running(&matrix);

#define EFFECTS_AMOUNT 5

const char autor[] PROGMEM="by Arsenii=)   ";
const char merry_christmas[] PROGMEM="Merry Christmas!   ";
const char year_num[] PROGMEM="!!2025!!   ";
const char new_year[] PROGMEM="Happy New Year!   ";
const char matrx[] PROGMEM="8x8 Matrix!   ";
const char for_sell[] PROGMEM="I'm $15 for sale=)   ";

uint32_t refresh_timer;
uint32_t change_timer;
uint32_t brightness_timer;
bool allow=false;
uint8_t time_multiplyer;
uint8_t matrix_container[10][9];
uint8_t matrix_arr_temp[10][10];

uint16_t change_time=0;
float phase=0.0;
uint32_t sine_timer;
uint32_t ball_timer;
int ball_x, ball_y;
int x_dir, y_dir;
uint8_t bitmap_id;

bool fav_effects_arr[EFFECTS_AMOUNT+1]={0, 1, 1, 1, 1, 1};

#define REFRESH_RATE 60  //Hz

struct
{
  int8_t brightness=1;
  bool auto_effect_change=true;
  uint8_t change=1;
} ee_data;

#define EEPROM_KEY 3

void setup()
{
  Serial.begin(115200);

  if (EEPROM.read(0)!=EEPROM_KEY)
  {
    for (int id = 1; id < 550; id++)
    {
      EEPROM.put(id, 0);
    }
    EEPROM.write(0, EEPROM_KEY);

    EEPROM.put(3, ee_data);
    Serial.println("Erase all");
  }
  EEPROM.get(3, ee_data);

  for (int i=1; i<=EFFECTS_AMOUNT; i++)
  {
    fav_effects_arr[i]=EEPROM.read(i+8);
  }
  


  btn.setHoldTimeout(500);
  btn.setClickTimeout(150);

  matrix.begin();
  matrix.setBright(ee_data.brightness);

  matrix_container[1][2]=2;
  matrix_container[3][1]=4;
  matrix_container[5][4]=2;
  matrix_container[8][1]=5;

  for (int8_t x=0; x<9; x++)
  {
    for (int8_t y=0; y<9; y++)
    {
      matrix_arr_temp[x][y]=matrix_container[x][y];
    }
  }

  randomSeed(analogRead(8)+analogRead(7)-analogRead(1)+__TIME__-__DATE__);
  if(ee_data.auto_effect_change)
  {
    //ee_data.change=1;
    Serial.println("mode check();");
    change_time=0;
    mode_change_check();
  }
}

void loop()
{
  static bool hold_flag=true;
  static bool select_effects=false;
  btn.tick();
  
  if(btn.releaseHoldStep()) hold_flag=!hold_flag;
  if(btn.hasClicks())
  {
    switch(btn.getClicks())
    {
      case 1:
        change_timer=millis();
        mode_change_check();
      break;
      case 2:
        ee_data.auto_effect_change=!ee_data.auto_effect_change;
        change_timer=millis();
        matrix.clear();
        matrix.update();
        delay(100);
        matrix.fill();
        matrix.update();
        delay(100);
      break;
      case 3:
        Serial.println("triple");
        select_effects=true;
      break;
      case 4:
      break;
      case 5:
      break;
    }
  }
  if(select_effects)
  {
    matrix.setRotation(3);
    uint8_t effect_id=1;
    bool update=true;
    while(true)
    {
      btn.tick();

      if(btn.click())
      {
        effect_id++;
        if(effect_id>EFFECTS_AMOUNT)
        {
          effect_id=1;
        }
        update=true;
      }
      if(btn.hold())
      {
        fav_effects_arr[effect_id]=!fav_effects_arr[effect_id];
        bool one_on=false;
        for(uint8_t id=1; id<=EFFECTS_AMOUNT; id++)
        {
          if(fav_effects_arr[id]) 
          {
            one_on=true;
            break;
          }
        }
        if(!one_on)
        {
          fav_effects_arr[effect_id]=1;

          matrix.dot(3, 7, 1);
          matrix.dot(3, 6, 1);
          matrix.dot(3, 5, 1);
          matrix.dot(4, 6, 1);
          matrix.dot(2, 6, 1);
          matrix.dot(4, 7, 1);
          matrix.dot(2, 7, 1);
          matrix.dot(4, 5, 1);
          matrix.dot(2, 5, 1);
          matrix.update();
          delay(100);
          matrix.dot(3, 7, 0);
          matrix.dot(3, 6, 0);
          matrix.dot(3, 5, 0);
          matrix.dot(4, 6, 0);
          matrix.dot(2, 6, 0);
          matrix.dot(4, 7, 0);
          matrix.dot(2, 7, 0);
          matrix.dot(4, 5, 0);
          matrix.dot(2, 5, 0);
          matrix.update();
          delay(100);
          matrix.dot(3, 7, 1);
          matrix.dot(3, 6, 1);
          matrix.dot(3, 5, 1);
          matrix.dot(4, 6, 1);
          matrix.dot(2, 6, 1);
          matrix.update();
        }
        else update=true;
      }
      if(btn.hasClicks())
      {
        if(btn.getClicks()==3) 
        {
          for (int id=1; id<=EFFECTS_AMOUNT; id++) 
          {
            EEPROM.write(id+8, fav_effects_arr[id]);
          }
          select_effects=false;
          mode_change_check();
          break;
        }
      }

      if(update)
      {
        update=false;

        matrix.clear();
        print_num(effect_id);
        if(fav_effects_arr[effect_id])
        {
          matrix.dot(3, 7, 1);
          matrix.dot(3, 6, 1);
          matrix.dot(3, 5, 1);
          matrix.dot(4, 6, 1);
          matrix.dot(2, 6, 1);
        }
        else 
        {
          matrix.dot(3, 7, 1);
          matrix.dot(3, 6, 1);
          matrix.dot(3, 5, 1);
        }
        matrix.update();
      }
    }
  }

  if(btn.holding())
  {
    if(millis()-brightness_timer>=250)
    {
      brightness_timer=millis();

      if(hold_flag)
      {
        ee_data.brightness++;
        if(ee_data.brightness>15) ee_data.brightness=15;
      }
      else if(!hold_flag)
      {
        ee_data.brightness--;
        if(ee_data.brightness<1) ee_data.brightness=1;
      }
      matrix.setRotation(3);
      matrix.clear();
      matrix.setBright(ee_data.brightness);
      print_num(ee_data.brightness);
      matrix.update();
      matrix.setRotation(0);
    }
  }
  else
  {    
    if(btn.timeout(2000))
    {
      EEPROM.put(3, ee_data);
      Serial.println("ee wrte");
    }

    if (millis()-change_timer>=change_time)
    {
      change_timer=millis();
      if(ee_data.auto_effect_change) 
      {
        mode_change_check();
      }
    }

    switch (ee_data.change)
    {
      case 1:
        matrix.setRotation(0);

        bitmaps();
        change_time=36000;
        time_multiplyer=1;
      break;
      case 2:
        matrix.setRotation(0);

        snow();
        change_time=30000;
        time_multiplyer=1;
      break;
      case 3:
        matrix.setRotation(0);

        circles();
        change_time=30000;
        time_multiplyer=1;
      break;
      case 4:
        matrix.setRotation(0);

        commets();
        time_multiplyer=1;
        change_time=30000;
      break;
      case 5:
        matrix.setRotation(1);

        sine_wave();
        change_time=30000;
        time_multiplyer=1;
      break;
      case 123:
        /*
        matrix.setRotation(0);

        bouncy_ball();
        change_time=15000;
        time_multiplyer=2;

        matrix.setRotation(2);

        running_string();
        change_time=30000;
        time_multiplyer=1;
        */
      break;
    }

    if (millis()-refresh_timer>=1000/REFRESH_RATE)
    {
      refresh_timer=millis();

      for (uint8_t y=1; y<=8; y++)
      {
        for (uint8_t x=1; x<=8; x++)
        {
          matrix.dot(8-x, 8-y, matrix_container[x][y] > 0 ? 1 : 0);
        }
      }
      matrix.update();
    }
  }
}

void mode_change_check()
{
  Serial.println();
  for(int8_t id=1; id<=EFFECTS_AMOUNT; id++)
  {
    Serial.print(fav_effects_arr[id]);

    if(id!=EFFECTS_AMOUNT) Serial.print(", ");
    else Serial.print(";");
  }
  Serial.println();

  for(int8_t iters=1; iters<=EFFECTS_AMOUNT; iters++)
  {
    ee_data.change++;
    if (ee_data.change>EFFECTS_AMOUNT)
    {
      ee_data.change=1;
    }

    if(fav_effects_arr[ee_data.change]==1) break;
  }

  switch(ee_data.change)
  {
    case 1:
      bitmap_id=random(1, 7);
    break;
    case 2:
    break;
    case 3:
    break;
    case 4:
    break;
    case 5:
    break;
    case 123:
      /*
      running.stop();

      for (uint8_t y=1; y<=8; y++)
      {
        for (uint8_t x=1; x<=8; x++)
        {
          matrix_container[x][y]=0;
        }
      }

      for (uint8_t y=1; y<=8; y++)
      {
        for (uint8_t x=1; x<=8; x++)
        {
          matrix_container[x][y]=0;
        }
      }
      */
    break;
  }
  if (ee_data.change>EFFECTS_AMOUNT)
  {
    ee_data.change=1;
  }
}

void arr_print(uint8_t array[9][9])
{
  for (byte y=0; y<=8; y++)
  {
    for (byte x=0; x<=8; x++)
    {
      Serial.print(array[x][y]);
      Serial.print(" ");
    }
    Serial.println();
  }
  Serial.println();
}
