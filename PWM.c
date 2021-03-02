//******************************************************************************
// Library to PWM mode developed under 16F877 data sheet
// Developed by Nivaldo T. Schiefler Jr.  Dr eng.
// Build under XC8 compiler
// Created on 24/08/2018, 16:37 
// Updates: 

//******************************************************************************

#include <xc.h>
#include "config.h"
//******************************************************************************
int Prescale_TMR2;
long freq_1,freq_2; 
//******************************************************************************
int define_prescale(void)
{
 int pre_scale;
    if  (freq_1<= 1500)
        pre_scale = 16;
    else if ((freq_1< 6000) && (freq_1< 10000))
        pre_scale = 4;
    else
        pre_scale = 1;
 return pre_scale;
}
//******************************************************************************
void init_PWM1(long freq)
{
   unsigned int temp; 
   freq_1 = freq;
   Prescale_TMR2 = define_prescale();
   // CCP1 -> RC2   
   // CCP1CON - > ? ? CCPxX CCPxY CCPxM3 CCPxM2 CCPxM1 CCPxM0
   // PWM Period = [(PR2) + 1] * 4 * TOSC * (TMR2 Prescale Value)  
   // CCPxM3:CCPxM0: CCPx Mode Select bits  
   //11xx = PWM mode
 
   CCP1CON = 0b00001100;  //11xx = PWM mode
   temp = (unsigned int)(((_XTAL_FREQ)/(4.0*freq*Prescale_TMR2)) - 1.0);
   if (temp > 255)
        PR2 = 255; 
   else
        PR2 = (char)temp;
   CCP1M3 = 1;
   CCP1M2 = 1;
   //T2CKPS1:T2CKPS0: Timer2 Clock Prescale Select bits
   //00 = Prescaler is 1
   //01 = Prescaler is 4
   //1x = Prescaler is 16
   if (Prescale_TMR2 == 1)
      { 
        T2CKPS0 = 0;
        T2CKPS1 = 0;
      }  
    else if( Prescale_TMR2 == 4)
      {
        T2CKPS0 = 1;
        T2CKPS1 = 0;
      }  
   else //if(Prescale_TMR2 == 16)
      { 
       T2CKPS0 = 1;
       T2CKPS1 = 1;
      } 
    TRISC2 = 0;
    //TMR2ON: Timer2 On bit
    //1 = Timer2 is on
    //0 = Timer2 is off
    TMR2ON = 1;
}
//******************************************************************************
void PWM1_set_duty(unsigned int duty_cycle_porcentagem)
{
  // CCP1CON ? ? CCP1X CCP1Y CCP1M3 CCP1M2 CCP1M1 CCP1M0
  //Pwm duty cicle = (CCPR2L:CCP1CON<5:4>) * TOSC * TMR2 (pre scaler)
 unsigned int duty;
 
 if(duty_cycle_porcentagem > 100)
     duty = (unsigned int)((_XTAL_FREQ)/(freq_1*Prescale_TMR2));
 else
     duty = (unsigned int)(((float)duty_cycle_porcentagem*1023.0/100.0/1023.0)*((_XTAL_FREQ)/(freq_1*Prescale_TMR2)));
   
     CCP1X =  (duty & 0x02); // 10
     CCP1Y =  (duty & 1);   // 01
     CCPR1L = (duty >> 2); // LSB
     
     
}
//******************************************************************************
void end_PWM1(void)
{
 //  0000 = Capture/Compare/PWM disabled (resets CCPx module)
   CCP1CON = 0; // Turn CCP module off 
   TRISC2  = 0;
   RC2 = 0;  
}
//******************************************************************************
void init_PWM2(long freq2)
{
    unsigned int temp; 
   freq_2 = freq2;
   Prescale_TMR2 = define_prescale();
   // CCP2 -> RC1   
   // CCP2CON - > ? ? CCPxX CCPxY CCPxM3 CCPxM2 CCPxM1 CCPxM0
   // PWM Period = [(PR2) + 1] * 4 * TOSC * (TMR2 Prescale Value)  
   // CCPxM3:CCPxM0: CCPx Mode Select bits  
   //11xx = PWM mode
 
   CCP2CON = 0b00001100;  //11xx = PWM mode
   temp = (unsigned int)(((_XTAL_FREQ)/(4.0*freq2*Prescale_TMR2)) - 1.0);
   if (temp > 255)
        PR2 = 255; 
   else
        PR2 = (char)temp;
   CCP2M3 = 1;
   CCP2M2 = 1;
   //T2CKPS1:T2CKPS0: Timer2 Clock Prescale Select bits
   //00 = Prescaler is 1
   //01 = Prescaler is 4
   //1x = Prescaler is 16
   if (Prescale_TMR2 == 1)
      { 
        T2CKPS0 = 0;
        T2CKPS1 = 0;
      }  
    else if( Prescale_TMR2 == 4)
      {
        T2CKPS0 = 1;
        T2CKPS1 = 0;
      }  
   else //if(Prescale_TMR2 == 16)
      { 
       T2CKPS0 = 1;
       T2CKPS1 = 1;
      } 
    TRISC1 = 0;
    //TMR2ON: Timer2 On bit
    //1 = Timer2 is on
    //0 = Timer2 is off
    TMR2ON = 1;
}
//******************************************************************************
void PWM2_set_duty(unsigned int duty_cycle_porcentagem)
{
 // CCP2CON ? ? CCP1X CCP1Y CCP1M3 CCP1M2 CCP1M1 CCP1M0
  //Pwm duty cicle = (CCPR2L:CCP1CON<5:4>) * TOSC * TMR2 (pre scaler)
 unsigned int duty;
 
 if(duty_cycle_porcentagem > 100)
     duty = (unsigned int)((_XTAL_FREQ)/(freq_2*Prescale_TMR2));
 else
     duty = (unsigned int)(((float)duty_cycle_porcentagem*1023.0/100.0/1023.0)*((_XTAL_FREQ)/(freq_2*Prescale_TMR2)));
   
     CCP2X =  (duty & 2); // 10
     CCP2Y =  (duty & 1);   // 01
     CCPR2L = (duty >> 2); // LSB
}
//******************************************************************************
void end_PWM2(void)
{
//  0000 = Capture/Compare/PWM disabled (resets CCPx module)
  CCP2CON = 0; // Turn CCP module off 
  TRISC1  = 0;
  RC1 = 0;  
}
//******************************************************************************


