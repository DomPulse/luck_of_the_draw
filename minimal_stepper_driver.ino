char step_pin_mask = 0x01;
char dir_pin_mask = 0x02;
signed int net_steps = 0;
signed int goal_steps = 0;
char step_timer_preset = 0xf0;
int error_timer_preset = 0xffd0;
signed int error = 0;

void setup() {
  // put your setup code here, to run once:
  
  DDRB = 0xff; //sets all of the PORTB pins as being outputs
  TCCR1A = 0x00; //disconnects OC1A/B, maybe should use those instead of overflow?
  TCCR1B = 0x05; //as set up, this prescales the clock to 16MHz/1024, can do others so that's cool
  TCNT1 = error_timer_preset; //this is the actual value of the 16 bit timer, increments with prescale
  TIFR1 = 0x00; //these are the actual various flags you can set, overflow, A/B and then an external interrupt
  TIMSK1 = 0x02; //enables and disables the different possible interrupts, currently only the A is enabled

  TCCR0A = 0x00; //disconnects OC0A/B?
  TCCR0B = 0x04; //as set up, this prescales the clock to 16MHz/1024, can do others so that's cool
  TCNT0 = 0x00; //this is the actual value of the 8 bit timer
  TIFR0 = 0x00; //these are the actual various flags you can set, overflow, A/B and then an external interrupt
  TIMSK0 = 0x02; //enables and disables the different possible interrupts, currently only the A is enabled
  Serial.begin(9600);
}


ISR(TIMER0_COMPA_vect) //for some reasone TIMER0_OVF_vect did not work here
{

  if (abs(error) > 4);
  {
    PORTB = PORTB^step_pin_mask; //bitwise or to toggle selected pins
    //TCNT0 = step_timer_preset;
    net_steps += 1 - (PORTB&dir_pin_mask); //really convenitenly, dir_pin_mask being 2 means that if it the direction pin is high we do -1 + 2 = +1 giving the desired change to net steps :)
  }
  
  
}

ISR(TIMER1_COMPA_vect)
{
  error = goal_steps - net_steps;
  TCNT0 = error>>4;
  if (error < 0)
  {
    PORTB = PORTB|dir_pin_mask;
  }
  else
  {
    PORTB = PORTB&~dir_pin_mask;
  }
      
  TCNT1 = error_timer_preset; //presets to control the how often error is checked


}

void loop() 
{
  if (Serial.available() > 1) 
  {
    goal_steps = Serial.parseInt();
  }
}
