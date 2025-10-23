char red_led_mask = 0x01;
char blu_led_mask = 0x02;

void setup() {
  // put your setup code here, to run once:
  
  DDRB = 0xff; //sets all of the PORTB pins as being outputs
  TCCR1A = 0x00; //disconnects OC1A/B, maybe should use those instead of overflow?
  TCCR1B = 0x05; //as set up, this prescales the clock to 16MHz/1024, can do others so that's cool
  TCNT1 = 0x0000; //this is the actual value of the 16 bit timer, it increments every clock cylce?
  TIFR1 = 0x00; //these are the actual various flags you can set, overflow, A/B and then an external interrupt
  TIMSK1 = 0x01; //enables and disables the different possible interrupts, currently only the overflow is enabled

  TCCR0A = 0x00; //disconnects OC1A/B, maybe should use those instead of overflow?
  TCCR0B = 0x05; //as set up, this prescales the clock to 16MHz/1024, can do others so that's cool
  TCNT0 = 0x00; //this is the actual value of the 16 bit timer, it increments every clock cylce?
  TIFR0 = 0x00; //these are the actual various flags you can set, overflow, A/B and then an external interrupt
  TIMSK0 = 0x02; //enables and disables the different possible interrupts, currently only the overflow is enabled
}


ISR(TIMER0_COMPA_vect)
{

  PORTB = PORTB^red_led_mask; //bitwise or to toggle selected pins
  
}

ISR(TIMER1_OVF_vect)
{

  PORTB = PORTB^blu_led_mask; //bitwise or to toggle selected pins
  TCNT1 = 0xe000; //presets to control the blink rate, set higher, will blink more rapidly
  //hint to help me later, I can set this timer value to tune how close it is to overflowing
  //that is more or less what we want to control motor speed just saying
  //then i would just need one more control bit to make sure the motor didn't move if it was below a threshhold
}

void loop() {
  //Serial.println(TCNT1);
}
