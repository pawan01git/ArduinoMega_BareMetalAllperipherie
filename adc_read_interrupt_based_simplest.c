#include<stdio.h>
#include<stdint.h>

#define MASK(num) (1<<(num))
uint16_t adcValue = 0;


// ADC0 PF0
void init_adc()
{
  DDRF  &= ~MASK(0);//PF0 make A0 as input
  ADMUX |= MASK(REFS0);//AVCC as reference +5V
  ADMUX &= ~MASK(REFS1);
  DIDR0 |= MASK(ADC0D);// no digital signal
  ADMUX &= (~MASK(MUX0)) & (~MASK(MUX1)) & (~MASK(MUX2)) & (~MASK(MUX3)) & (~MASK(MUX4));// select ADC0 as single ended input
  ADCSRB &= ~MASK(MUX5);
  ADCSRA |= MASK(ADEN);// enable ADC
  ADCSRA |= MASK(ADSC);// start conversion
  ADCSRA |= MASK(ADIF);// clear interrupt flag
  ADCSRA |= MASK(ADIE);// enable ADC interrupt
  ADCSRA |= MASK(ADATE);//auto trigger enable
  ADCSRA |= MASK(ADPS0) | MASK(ADPS1) | MASK(ADPS2);// clock division 128
  sei();//enable interrupt
}
ISR(ADC_vect)
{
  uint8_t lsb =ADCL;
  uint8_t msb =ADCH;
  adcValue = (msb<<8) | (lsb);
}
void init_uart()
{
  Serial.begin(9600);
}
int main()
{
  init();
  init_uart();
  init_adc();
  while(1)
  {
    delay(1000);
    Serial.println(adcValue);
  }
  return 0;
}