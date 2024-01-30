<?
function ms_view($arr)
{
   $st='';
   //--
   for($y = 0; $y<=9; $y++)
   {
     for($x = 0; $x<=9; $x++)
     {
       //$st.=$arr[$x][$y].' ';
       //$st.=($arr[$x][$y]>0?'*':'<span style="color:#fff">*</span>').' ';
       if($y!=0 && $y!=9 && $x!=0 && $x!=9)
       {
          $st.=($arr[$x][$y]==0?$arr[$x][$y]:'<span style="color:red">'.$arr[$x][$y].'</span>').'&nbsp;  ';
       }
       else
       {
         $st.='<span style="color:#ababab">'.$arr[$x][$y].'</span>'.'&nbsp;  ';
       }

     }
     $st.='<br />';
   }
   //$st.='<div>----------</div>';
   //--
   //return '<br /><div style="padding:20px 0 0 0; display:inline-block; border:1px solid #aaa;">'.$st.'</div>';
   return '<div style="padding:0 0 30px 0;">'.$st.'</div>';
}


//--
$log_view=0;

//Заповнити масив нулями
for ($x=0; $x<=9; $x++)
{
   for ($y=0; $y<=9; $y++)
   {
      $ms[$x][$y]=0;
   }
}
//--
/*
$ms[1][1]=3;
$ms[2][1]=3; $ms[2][2]=3;
$ms[3][1]=2; $ms[3][2]=2; $ms[3][3]=0; $ms[3][4]=2;$ms[3][5]=2; $ms[3][6]=0; $ms[3][7]=2;
//$ms[3][1]=2; $ms[3][2]=2; $ms[3][3]=0; $ms[3][4]=2; $ms[3][5]=2;$ms[3][6]=0;
//--
$ms[4][1]=4;
$ms[5][1]=0; $ms[5][2]=0; $ms[5][3]=0; $ms[5][4]=4;
//--
$ms[6][1]=3; $ms[6][2]=3; $ms[6][3]=3;  $ms[6][5]=3;
$ms[7][1]=4; $ms[7][2]=4; $ms[7][3]=4;  $ms[7][4]=4; $ms[7][6]=2;
*/

$ms[1][2] = 2;
$ms[3][1] = 4;
$ms[5][4] = 2;
$ms[7][1] = 5;
//--
//echo '<pre>'.print_r($ms, true).'</pre>';
//echo ms_view($ms);
//echo '<div style="padding:0 0 20px 0;">----------</div>';

$ms2=$ms;
for($repeats = 1; $repeats<=12; $repeats++)
{
  for ($x = 1; $x <= 8; $x++)
  {
    $col_status[$x] = 0;
    for ($y = 1; $y <= 8; $y++)
    {
      if ($ms[$x][$y] == 0)
      {
        $col_status[$x]++;
      }
      else
      {
        break;
      }
    }
    $allow_to_create = true;
    if($col_status[$x+1]<4)
    {
      $allow_to_create = false;
    }
    if($col_status[$x-1]<4)
    {
      $allow_to_create = false;
    }
    echo 'status'.'['.$x.']: '.$col_status[$x].'<span style="color: red;">&nbsp; | &nbsp; </span>';

    //arr_print($ms);
    $is_created = false;
    if($col_status[$x]<4)
    {
      ;
    }
    else if($col_status[$x]>=4/* && $col_status[$x+1]>3 && $col_status[$x-1]>3*/)
    {
      $ms[$x][rand(1, 2)] = rand(2, 3);
      $is_created = true;
    }
    else if($col_status[$x]==8/* && $col_status[$x+1]>3 && $col_status[$x-1]>3*/)
    {
      $ms[$x][rand(1, 4)] = rand(2, 5);
      $is_created = true;
    }
  }  //for(x)


  $cnt=0;
  //$ms2=$ms;
  for ($commet_id = 1; $commet_id <= 4; $commet_id++)
  {
    echo '<div style="padding:20px 0 0px 0;">----------------------------opened</div>';

     $ms=$ms2;
     echo ms_view($ms);

     //inspect ->

     $min_y=10000;
     for ($x = 1; $x <= 8; $x++)
     {
        if ($log_view>0) {echo '<br />x='.$x.'; ';}

        //acting ->
        $cnt=0;
        if ($log_view>0) {echo '$cnt['.$x.']='.$cnt.'; ';}
        for ($y = 8; $y >= 1; $y--)
        {
           if ($log_view>0) {echo 'y='.$y.'; ';}
           //Підрахунок робиться за умови позиції курсора у чітко визначеній позиції ... довжина поточного безперервного стовпця значень >0
           if ($ms[$x][$y]>0) //$ms[$x][$y+1]==0
           {
              if ($log_view>0) {echo '<br>';}
              //echo start $cnt['.$x.']['.$y.']; ';
              //довжина >1
              if ($ms[$x][$y-1]>0 && $ms[$x][$y+1]==0)
              {
                 $cnt=0; //довжина поточного безперервного стовпця значень >0
                 //поточна к-ть елементів >0
                 $z=$y;
                 do
                 {
                    $cnt++;
                    $z--;
                    //echo 'z='.$z.'; ';
                 } while ($z>=1 && $ms[$x][$z]>0);
              }
              elseif ($ms[$x][$y+1]==0 && $ms[$x][$y-1]==0)
              {
                 $cnt=1;
              }
              elseif ($log_view>0)
              {
                 echo 'ms['.$x.']['.$y.']='.$ms[$x][$y].'; ';
                 echo 'ms['.$x.']['.($y-1).']='.$ms[$x][$y-1].'; ';
                 echo 'ms['.$x.']['.($y+1).']='.$ms[$x][$y+1].'; ';
              }
              //--
              if ($cnt>0 && $log_view>0)
              {
                 echo '<b>$cnt['.$x.']['.$y.']='.$cnt.';</b> ';
                 echo '<b>$ms2['.$x.']['.$y.']='.$ms2[$x][$y].';</b> ';
              }
              //echo '<b>$ms[1][2]='.$ms[1][2].';</b> ';
           }

           //Задати значення для наступного (нижче) елементу в стовпці
           if (1==1 && $ms2[$x][$y]>0)
           {
              $ms2[$x][$y+1] = $ms2[$x][$y];
              //Визначення чи обнуляти верхнє значення
              //додатково перевіряти, щоб під час "росту" не обнуляти хвости інших
              if (($y==8 && $cnt>0) || $cnt>=$ms2[$x][$y])
              {
                 $z=$y-$cnt+1;
                 if ($log_view>0) {echo '$z='.$z.'; $ms2['.$x.']['.$z.'] <b>set to 0</b>; ';}
                 if ($z>=1) {$ms2[$x][$z]=0;}
              }
           }
           //--

           $cnt=-1;
        } //for ($y)
        //<- acting
     } //for(x)

     //значення в рядку #9 завжди нулі
     for($x=0; $x<=9; $x++)
     {
        $ms2[$x][9]=0;
     }

     echo '<div style="padding:20px 0 0px 0;">---------------closed</div>';
  } // for(commet_id)
  echo '****************************************';
  echo '****************************************';
  echo '****************************************';
}

?>
