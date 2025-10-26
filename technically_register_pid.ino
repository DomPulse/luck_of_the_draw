char step_pin_mask = 0x01;
char dir_pin_mask = 0x02;
signed int net_steps = 0;
unsigned char goal_pos = 0;
char step_timer_preset = 0xf6;
int error_timer_preset = 0xfb00;
signed int error = 0;

char ADC_Enable_Mask = 0x80;
char ADC_Start_Convert_Mask = 0x40;
char ADC_Interrupt_Flag_Mask = 0x10;
char ADSCRA_Scale_Init = 0x07;

void setup() {
  // put your setup code here, to run once:
  
  DDRB = 0xff; //sets all of the PORTB pins as being outputs
  TCCR1A = 0x00; //disconnects OC1A/B, maybe should use those instead of overflow?
  TCCR1B = 0x05; //as set up, this prescales the clock to 16MHz/1024, can do others so that's cool
  TCNT1 = error_timer_preset; //this is the actual value of the 16 bit timer, increments with prescale
  TIFR1 = 0x00; //these are the actual various flags you can set, overflow, A/B and then an external interrupt
  TIMSK1 = 0x02; //enables and disables the different possible interrupts, currently only the A is enabled

  TCCR0A = 0x00; //disconnects OC0A/B?
  TCCR0B = 0x03; //as set up, this prescales the clock to 16MHz/1024, can do others so that's cool
  TCNT0 = 0x00; //this is the actual value of the 8 bit timer
  TIFR0 = 0x00; //these are the actual various flags you can set, overflow, A/B and then an external interrupt
  TIMSK0 = 0x02; //enables and disables the different possible interrupts, currently only the A is enabled
  
  ADCSRA = ADSCRA_Scale_Init; //Prescales clock to 16MHz/128 = 125KHz
  ADMUX = 0x65; //Sets to use the internal reference and analog pin 5, makes reading high first for 8 bit precision on the analog read
  
  Serial.begin(9600);
}


ISR(TIMER0_COMPA_vect) //for some reasone TIMER0_OVF_vect did not work here
{

  if (abs(error) > 11)
  {
    PORTB = PORTB^step_pin_mask; //bitwise or to toggle selected pins
  }
  
  
  //net_steps += 1 - (PORTB&dir_pin_mask); //really convenitenly, dir_pin_mask being 2 means that if it the direction pin is high we do -1 + 2 = +1 giving the desired change to net steps :)
  TCNT0 = step_timer_preset - 0xff + abs(error);
}

ISR(TIMER1_COMPA_vect)
{
  ADCSRA = ADCSRA|ADC_Enable_Mask;
  ADCSRA = ADCSRA|ADC_Start_Convert_Mask;

  
  while ((~ADCSRA)&ADC_Interrupt_Flag_Mask); //this can surely be greatly improved by setting some additional interrupt to trigger when ready

  error = goal_pos - ADCH;
  
  
  ADCSRA = ADSCRA_Scale_Init;

  if (error < 0)
  {
    PORTB = PORTB|dir_pin_mask;
  }
  else
  {
    PORTB = PORTB&~dir_pin_mask;
  }
      
  TCNT1 = error_timer_preset; //presets to control the how often error is checked
  TCNT0 = 0xfe;


}

void loop() 
{
  if (Serial.available() > 1) 
  {
    goal_pos = Serial.parseInt();
  }
  delay(100);
  Serial.print(goal_pos, BIN);
  Serial.print(" ");
  Serial.print(ADCH, BIN);
  Serial.print(" ");
  Serial.println(abs(error), BIN);
}