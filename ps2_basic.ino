const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;
int gaming = 0;
byte b = B00001000;
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
    if (data == 56) Serial.write("A");
    else if (data == 76) Serial.write("B");
    else if (data == 132) Serial.write("C");
    else if (data == 196) Serial.write("D");
    else if (data == 36) Serial.write("E");
    else if (data == 212) Serial.write("F");
    else if (data == 44) Serial.write("G");
    else if (data == 204) Serial.write("H");
    else if (data == 194) Serial.write("I");
    else if (data == 220) Serial.write("J");
    else if (data == 66) Serial.write("K");
    else if (data == 210) Serial.write("L");
    else if (data == 92) Serial.write("M");
    else if (data == 140) Serial.write("N");
    else if (data == 34) Serial.write("O");
    else if (data == 178) Serial.write("P");
    else if (data == 168) Serial.write("Q");
    else if (data == 180) Serial.write("R");
    else if (data == 216) Serial.write("S");
    else if (data == 52) Serial.write("T");
    else if (data == 60) Serial.write("U");
    else if (data == 84) Serial.write("V");
    else if (data == 184) Serial.write("W");
    else if (data == 68) Serial.write("X");
    else if (data == 172) Serial.write("Y");
    else if (data == 88) Serial.write("Z"); 
    else if (data == 148) Serial.write(" "); 
    else if (data == 104) Serial.write("!");
    else if (data == 120) Serial.write("@");
    else if (data == 100) Serial.write("#");
    else if (data == 164) Serial.write("$");
    else if (data == 116) Serial.write("%"); 
    else if (data == 108) Serial.write("^");
    else if (data == 188) Serial.write("&");
    else if (data == 124) Serial.write("*");
    else if (data == 98) Serial.write("("); 
    else if (data == 162) Serial.write(")"); 
    else if (data == 130) Serial.write("<"); 
    else if (data == 146) Serial.write(">"); 
    else if (data == 82) Serial.write("?"); 
    else if (data == 74) Serial.write('"'); 
    else if (data == 102) Serial.write(0xC);
    else if (data == 90) Serial.write("\n");
    else Serial.println(data); 
  }
  
  else
  {
    if (data == 56) Serial.write("a");
    else if (data == 76) Serial.write("b");
    else if (data == 132) Serial.write("c");
    else if (data == 196) Serial.write("d");
    else if (data == 36) Serial.write("e");
    else if (data == 212) Serial.write("f");
    else if (data == 44) Serial.write("g");
    else if (data == 204) Serial.write("h");
    else if (data == 194) Serial.write("i");
    else if (data == 220) Serial.write("j");
    else if (data == 66) Serial.write("k");
    else if (data == 210) Serial.write("l");
    else if (data == 92) Serial.write("m");
    else if (data == 140) Serial.write("n");
    else if (data == 34) Serial.write("o");
    else if (data == 178) Serial.write("p");
    else if (data == 168) Serial.write("q");
    else if (data == 180) Serial.write("r");
    else if (data == 216) Serial.write("s");
    else if (data == 52) Serial.write("t");
    else if (data == 60) Serial.write("u");
    else if (data == 84) Serial.write("v");
    else if (data == 184) Serial.write("w");
    else if (data == 68) Serial.write("x");
    else if (data == 172) Serial.write("y");
    else if (data == 88) Serial.write("z"); 
    else if (data == 148) Serial.write(" "); 
    else if (data == 104) Serial.write("1");
    else if (data == 120) Serial.write("2");
    else if (data == 100) Serial.write("3");
    else if (data == 164) Serial.write("4");
    else if (data == 116) Serial.write("5"); 
    else if (data == 108) Serial.write("6");
    else if (data == 188) Serial.write("7");
    else if (data == 124) Serial.write("8");
    else if (data == 98) Serial.write("9"); 
    else if (data == 162) Serial.write("0"); 
    else if (data == 130) Serial.write(","); 
    else if (data == 146) Serial.write("."); 
    else if (data == 82) Serial.write("/"); 
    else if (data == 74) Serial.write("'");
    else if (data == 102) Serial.write(0xC);
    else if (data == 90) Serial.write("\n");
    else Serial.println(data); 
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