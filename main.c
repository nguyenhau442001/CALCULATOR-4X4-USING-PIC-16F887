#include <lcd4chan.c>
#include <stdlib.h> 
const unsigned char maquetcot[4]={0xfe,0xfd,0xfb,0xf7};
unsigned int8 mp=0, cal=0, pc=0,pt=0,pn=0,pch=0;
float kq,sh1=0, sh2=0;
unsigned char string1[50];


unsigned int quet_mt_phim()
{
     signed int8 maphim, hang, cot;
     maphim = hang = 0xff;
     for(cot=0; cot<4; cot++)
     {
     output_d(maquetcot[cot]);
     if(!input(pin_c0))      { hang=0; break;}
     else if(!input(pin_c1)) { hang=1; break;}
     else if(!input(pin_c2)) { hang=2; break;}
     else if(!input(pin_c3)) { hang=3; break;}
     }
     if(hang!=0xff) maphim= cot*4 + hang;
     return(maphim);
}

unsigned int key_4x4()
{
     unsigned int8 mpt1, mpt2;
     mpt1 = quet_mt_phim();
     if(mpt1!=0xff)
     {
           delay_ms(10);
           mpt1= quet_mt_phim();
           do{ mpt2= quet_mt_phim();}
           while (mpt2==mpt1);
     }
     return(mpt1);
}     


void so_0()
{ 
   if(mp==7)
     { 
       delay_us(1);
       if(mp==7)
       {
          lcd_putchar("0");
          if(cal==0)  sh1=sh1*10;
          else        sh2=sh2*10;
       }
     }
}

void so_1()
{ 
   if(mp==2)
     {
       delay_us(1);
       if(mp==2)
       {
          lcd_putchar("1");
          if(cal==0)  sh1=sh1*10+1;
          else        sh2=sh2*10+1;
       }
     }
}

void so_2()
{
   if(mp==6)
     { 
       delay_us(1);
       if(mp==6)
       {
          lcd_putchar("2");
          if(cal==0)  sh1=sh1*10+2;
          else        sh2=sh2*10+2;
       }
     }
}

void so_3()
{
   if(mp==10)
     { 
       delay_us(1);
       if(mp==10)
       {
          lcd_putchar("3");
          if(cal==0)  sh1=sh1*10+3;
          else        sh2=sh2*10+3;
       }
     }
}

void so_4()
{
   if(mp==1)
     { 
       delay_us(1);
       if(mp==1)
       {
         lcd_putchar("4");
         if(cal==0)  sh1=sh1*10+4;
         else        sh2=sh2*10+4;
       }
     }
}

void so_5()
{   
   if(mp==5)
     { 
       delay_us(1);
       if(mp==5)
       {
       lcd_putchar("5");
       if(cal==0)  sh1=sh1*10+5;
       else        sh2=sh2*10+5;
       }
     }
}

void so_6()
{  
   if(mp==9)
     { 
       delay_us(1);
       if(mp==9)
       {
       lcd_putchar("6");
       if(cal==0)  sh1=sh1*10+6;
       else        sh2=sh2*10+6;
       }
     }
}

void so_7()
{  
   if(mp==0)
     { 
       delay_us(1);
       if(mp==0)
       {
       lcd_putchar("7");
       if(cal==0)  sh1=sh1*10+7;
       else        sh2=sh2*10+7;
       }
     }
}

void so_8()
{
   if(mp==4)
     { 
       delay_us(1);
       if(mp==4)
       {
       lcd_putchar("8");
       if(cal==0)  sh1=sh1*10+8;
       else        sh2=sh2*10+8;
       }
     }
}

void so_9()
{  
   if(mp==8)
     {  
       delay_us(1);
       if(mp==8)
       {
       lcd_putchar("9");
       if(cal==0)  sh1=sh1*10+9;
       else        sh2=sh2*10+9;
       }
     }
}

void phepcong()
{
    if(mp==15)
    {
       delay_us(1);
       if(mp==15)
         {
            lcd_putchar("+") ; pc=1; pt=pn=pch=0;
            cal=1;
         }
    }
}

void pheptru()
{
    if(mp==14)
    {
       delay_us(1);
       if(mp==14)
         {
            lcd_putchar("-") ; pt=1 ; pc=pn=pch=0;
            cal=1;
         }
    }
}

void phepnhan()
{
    if(mp==13)
    {
       delay_us(1);
       if(mp==13)
         {
            lcd_putchar("x") ; pn=1; pc=pt=pch=0;
            cal=1;
         }
    }
}

void phepchia()
{
    if(mp==12)
    {
       delay_us(1);
       if(mp==12)
         {
            lcd_putchar(0xfd) ; pch=1; pc=pt=pn=0;
            cal=1;
         }
    }
}

void dau_bang()
{
  if(mp==11)
    {
    if(cal==1)
    {    
         LCD_Gotoxy(1,0);
         if(pc==1)      {   kq = sh1+sh2 ; sprintf(string1,"%f",kq); lcd_putstring(string1);}
         else if(pt==1) {   
                            kq = sh1-sh2 ;
                            sprintf(string1,"%f",kq); lcd_putstring(string1);}
         else if(pn==1) {   kq = sh1*sh2 ; sprintf(string1,"%f",kq); lcd_putstring(string1);}
         else if(pch==1)  
               {
                      if(sh2==0) { lcd_putchar("Error") ;} 
                      else { kq = (sh1*1.00)/(sh2*1.00) ;sprintf(string1,"%f",kq); lcd_putstring(string1);}      
               }  
         cal=pc=pt=pn=pch=0; sh1=sh2=0 ,kq =0;
    }
    }
}

void ON()
{
   if(mp==3)
     {  
        delay_ms(2);
        if(mp==3) {LCD_Clear(); cal=pc=pt=pn=pch=0; sh1=sh2=0 ; }
     }
}
      
void main()
{       
                set_tris_b(0x00);
                LCD_Init();  delay_ms(10); LCD_Gotoxy(0,0);
                while(true)
                {     
                mp= key_4x4();
                if(mp!=0xff)
                  {    
                       ON();
                       so_0();
                       so_1();
                       so_2();
                       so_3();
                       so_4();
                       so_5();
                       so_6();
                       so_7();
                       so_8();
                       so_9();  
                       phepcong();
                       pheptru();
                       phepnhan();
                       phepchia();
                       dau_bang();
                  }
                }
}