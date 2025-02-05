#include <stdio.h>
#include <stdint.h>
const uint8_t LED = 13;

#define LED_PIN  PIN7
#define MASK(num) (1<<(num))

void switch_on_led()
{
  PORTB |= MASK(LED_PIN);
}

void switch_off_led()
{
  PORTB &= ~MASK(LED_PIN);
}

void init_led()
{
 DDRB |= MASK(LED_PIN);// setup as output direction
 PORTB &= ~MASK(LED_PIN) ; // disable initially
}
void setup()
{
  Serial.begin(9600);
}
int main()
{
  init_led();
  init(); // must be called for delay function
  setup();
  while(1)
  {
    
    switch_off_led();
    Serial.println((PORTB & MASK(LED_PIN)), BIN);
    delay(1000);//do nothing
    switch_on_led();
    Serial.println((PORTB & MASK(LED_PIN)), BIN);
    delay(1000);
  }
  return 0;

}