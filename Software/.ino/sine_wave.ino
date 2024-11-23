void sine_wave()
{
  if(millis()-sine_timer>=100)
  {
    sine_timer=millis();

    phase+=0.3;
  
    for (int x=0; x<8; x++)
    {
      float rad=((x/7.0)*2*M_PI)+phase;
      int y=(int)(4*sin(rad)+4);

      for (int i=0; i<=7; i++)
      {
        matrix_container[i+1][x+1]=0;
      }
      matrix_container[y+1][x+1]=1;
    }
  }
}
