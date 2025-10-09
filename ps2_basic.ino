const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;
int gaming = 0;
byte b = B00001000;
uint8_t buf[8] = { 0 };   //Keyboard report buffer
bool ps2Read[11];
uint8_t data_byte = 0;
bool ready = false;
bool shifted = false;

void setup() 
{
  pinMode (ledPin, OUTPUT);
  pinMode (2 , INPUT);
  pinMode (3 , INPUT);
  pinMode(13, OUTPUT);
  attachInterrupt (digitalPinToInterrupt (2), incr, FALLING) ;
  Serial.begin(9600);
}

void loop ( ) 
{
  digitalWrite(13, shifted);
  
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
      Serial.write(data_byte);

    }
  }
  */
}

void convert_char(int data)
{
  if (shifted)
  {
    buf[0] = 2;

    if (data == 56) buf[2] = 4;
    else if (data == 76) buf[2] = 5;
    else if (data == 132) buf[2] = 6;
    else if (data == 196) buf[2] = 7;
    else if (data == 36) buf[2] = 8;
    else if (data == 212) buf[2] = 9;
    else if (data == 44) buf[2] = 10;
    else if (data == 204) buf[2] = 11;
    else if (data == 194) buf[2] = 12;
    else if (data == 220) buf[2] = 13;
    else if (data == 66) buf[2] = 14;
    else if (data == 210) buf[2] = 15;
    else if (data == 92) buf[2] = 16;
    else if (data == 140) buf[2] = 17;
    else if (data == 34) buf[2] = 18;
    else if (data == 178) buf[2] = 19;
    else if (data == 168) buf[2] = 20;
    else if (data == 180) buf[2] = 21;
    else if (data == 216) buf[2] = 22;
    else if (data == 52) buf[2] = 23;
    else if (data == 60) buf[2] = 24;
    else if (data == 84) buf[2] = 25;
    else if (data == 184) buf[2] = 26;
    else if (data == 68) buf[2] = 27;
    else if (data == 172) buf[2] = 28;
    else if (data == 88) buf[2] = 29;
    else if (data == 148) buf[2] = 44;
    else if (data == 104) buf[2] = 30;
    else if (data == 120) buf[2] = 31;
    else if (data == 100) buf[2] = 32;
    else if (data == 164) buf[2] = 33;
    else if (data == 116) buf[2] = 34;
    else if (data == 108) buf[2] = 35;
    else if (data == 188) buf[2] = 36;
    else if (data == 124) buf[2] = 37;
    else if (data == 98) buf[2] = 38;
    else if (data == 162) buf[2] = 39;
    else if (data == 130) buf[2] = 54;
    else if (data == 146) buf[2] = 55;
    else if (data == 82) buf[2] = 56;
    else if (data == 74) buf[2] = 52;
    else if (data == 102) buf[2] = 42;
    else if (data == 90) buf[2] = 40;

    Serial.write(buf, 8); 
    releaseKey();
  }
  
  else
  {
    if (data == 56) buf[2] = 4;
    else if (data == 76) buf[2] = 5;
    else if (data == 132) buf[2] = 6;
    else if (data == 196) buf[2] = 7;
    else if (data == 36) buf[2] = 8;
    else if (data == 212) buf[2] = 9;
    else if (data == 44) buf[2] = 10;
    else if (data == 204) buf[2] = 11;
    else if (data == 194) buf[2] = 12;
    else if (data == 220) buf[2] = 13;
    else if (data == 66) buf[2] = 14;
    else if (data == 210) buf[2] = 15;
    else if (data == 92) buf[2] = 16;
    else if (data == 140) buf[2] = 17;
    else if (data == 34) buf[2] = 18;
    else if (data == 178) buf[2] = 19;
    else if (data == 168) buf[2] = 20;
    else if (data == 180) buf[2] = 21;
    else if (data == 216) buf[2] = 22;
    else if (data == 52) buf[2] = 23;
    else if (data == 60) buf[2] = 24;
    else if (data == 84) buf[2] = 25;
    else if (data == 184) buf[2] = 26;
    else if (data == 68) buf[2] = 27;
    else if (data == 172) buf[2] = 28;
    else if (data == 88) buf[2] = 29;
    else if (data == 148) buf[2] = 44;
    else if (data == 104) buf[2] = 30;
    else if (data == 120) buf[2] = 31;
    else if (data == 100) buf[2] = 32;
    else if (data == 164) buf[2] = 33;
    else if (data == 116) buf[2] = 34;
    else if (data == 108) buf[2] = 35;
    else if (data == 188) buf[2] = 36;
    else if (data == 124) buf[2] = 37;
    else if (data == 98) buf[2] = 38;
    else if (data == 162) buf[2] = 39;
    else if (data == 130) buf[2] = 54;
    else if (data == 146) buf[2] = 55;
    else if (data == 82) buf[2] = 56;
    else if (data == 74) buf[2] = 52;
    else if (data == 102) buf[2] = 42;
    else if (data == 90) buf[2] = 40;

    Serial.write(buf, 8); 
    releaseKey();
  }
  //90 -> enter
  //102 -> backspace
  //153 -> right shift
  //72 -> left shift

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
  //Serial.write(gaming);
  if (gaming == 11)
  {
    detachInterrupt(digitalPinToInterrupt (2));
    gaming = 0;
    data_byte = 0;
    data_byte = (ps2Read[1] << 7) + (ps2Read[2] << 6) + (ps2Read[3] << 5) + (ps2Read[4] << 4) + (ps2Read[5] << 3) + (ps2Read[6] << 2) + (ps2Read[7] << 1) + (ps2Read[8] << 0);
    if (ps2Read[0] == 0 & ps2Read[10] == 1)
    {
      //Serial.write(data_byte); 
      if (data_byte == 72 | data_byte == 154)
      {
        shifted = !ready;
      }

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

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Send Release key  
}