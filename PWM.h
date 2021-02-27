//******************************************************************************
// Library to PWM mode developed under 16F877 data sheet
// Developed by Nivaldo T. Schiefler Jr.  Dr eng.
// Build under XC8 compiler
// Created on 24/08/2018, 16:37 
// Updates: 

//******************************************************************************

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

int define_prescale(void);
void inicia_PWM1(long freq);
void PWM1_set_duty(unsigned int duty_cycle_porcentagem);
void fim_PWM1(void);

void inicia_PWM2(long freq);
void PWM2_set_duty(unsigned int duty_cycle_porcentagem);
void fim_PWM2(void);
#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

