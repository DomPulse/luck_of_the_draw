const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;
int gaming = 0;
byte b = B00001000;
bool ps2Read[11];
uint8_t data_byte = 0;
bool ready = false;

void setup() 
{
  pinMode (ledPin, OUTPUT);
  pinMode (2 , INPUT);
  pinMode (3 , INPUT);
  attachInterrupt (digitalPinToInterrupt (2), incr, FALLING) ;
  Serial.begin(9600);
}

void loop ( ) 
{

  
  /*
  if (ps2Read[0] == 0 & ps2Read[9] == 1)
  {
    int s = 0;
    for (int i = 0; i < 11; i++)
    {
        s += ps2Read[i];
    }
    if (s%2 == 1)
    {
      data_byte = (ps2Read[1] << 7) + (ps2Read[2] << 6) + (ps2Read[3] << 5) + (ps2Read[4] << 4) + (ps2Read[5] << 3) + (ps2Read[6] << 2) + (ps2Read[7] << 1) + (ps2Read[8] << 0);
      Serial.print(gaming);
      Serial.print(" ");
      Serial.println(data_byte);

    }
  }
  */
}

void convert_char(int data)
{
  if (data == 56) Serial.println("A");
  else if (data == 76) Serial.println("B");
  else if (data == 132) Serial.println("C");
  else if (data == 196) Serial.println("D");
  else if (data == 36) Serial.println("E");
  else if (data == 212) Serial.println("F");
  else if (data == 44) Serial.println("G");
  else if (data == 204) Serial.println("H");
  else if (data == 194) Serial.println("I");
  else if (data == 220) Serial.println("J");
  else if (data == 66) Serial.println("K");
  else if (data == 210) Serial.println("L");
  else if (data == 92) Serial.println("M");
  else if (data == 140) Serial.println("N");
  else if (data == 34) Serial.println("O");
  else if (data == 178) Serial.println("P");
  else if (data == 168) Serial.println("Q");
  else if (data == 180) Serial.println("R");
  else if (data == 216) Serial.println("S");
  else if (data == 52) Serial.println("T");
  else if (data == 60) Serial.println("U");
  else if (data == 84) Serial.println("V");
  else if (data == 184) Serial.println("W");
  else if (data == 68) Serial.println("X");
  else if (data == 172) Serial.println("Y");
  else if (data == 88) Serial.println("Z"); 
  ready = false;
}

void unfuck()
{
  delay(30);
  attachInterrupt(digitalPinToInterrupt (2), incr, FALLING);
  gaming = 0;
  data_byte = 0;
}

void incr()
{
  ps2Read[gaming] = digitalRead(3);
  gaming++;
  //Serial.println(gaming);
  if (gaming == 11)
  {
    detachInterrupt(digitalPinToInterrupt (2));
    gaming = 0;
    data_byte = 0;
    data_byte = (ps2Read[1] << 7) + (ps2Read[2] << 6) + (ps2Read[3] << 5) + (ps2Read[4] << 4) + (ps2Read[5] << 3) + (ps2Read[6] << 2) + (ps2Read[7] << 1) + (ps2Read[8] << 0);
    if (ps2Read[0] == 0 & ps2Read[10] == 1)
    {
      //Serial.println(data_byte); 
      if (ready)
      {
        convert_char(data_byte);
      }

      if (data_byte == 15)
      {
        ready = true;
      }
      
      attachInterrupt(digitalPinToInterrupt (2), incr, FALLING) ;
    }
    else
    {
      unfuck();
    }
    
  }
}