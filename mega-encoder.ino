
/*
input rotary encoder - output PORTA Arduino Mega2560
PIN number  PORT
2 PORTE (0x10)
3 PORTE (0x20)
4 PORTG (0x20)
5 PORTE (0x08)
6 PORTH (0x08)
7 PORTH (0x10)
8 PORTH (0x20)
9 PORTH (0x40)
10  PORTB (0x10)
11  PORTB (0x20)
12  PORTB (0x40)
13  PORTB (0x80)
22-29 PORTA (0x01-0x80)
30-37 PORTC (0x80-0x01)
38-45 PORTD (0x80-0x01)
*/



byte reading = B00000000;
//int lowest = 0;
byte lowest = B00000000;
//int highest = 255;
byte highest = B11111111;
//int changeamnt = 1; 
byte changeamnt = B00000001;

// Timing for polling the encoder
unsigned long currentTime;
unsigned long lastTime;


// Pin definitions
const int pinA = 12;
const int pinB = 11;

// Storing the readings

boolean encA;
boolean encB;
boolean lastA = false;

void setup() {
  DDRA = B11111111; //initialize port pins as output 22-29
  // set the two pins as inputs with internal pullups
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  // Set up the timing of the polling
  currentTime = millis();
  lastTime = currentTime; 
  // Start the serial monitor for debugging
  Serial.begin(115200);
  Serial3.begin(115200);
} 


void loop()
{
  // Read elapsed time
  currentTime = millis(); 
  // Check if it's time to read
  if(currentTime >= (lastTime + 5))
  {
    // read the two pins
    encA = digitalRead(pinA);
    encB = digitalRead(pinB);
    // check if A has gone from high to low
    if ((!encA) && (lastA))
    {
      // check if B is high 
      if (encB)
      {
        // clockwise
        if (reading + changeamnt <= highest)
        {
          reading = reading + changeamnt; 
        }
      }
      else
      {
        // anti-clockwise
        if (reading - changeamnt >= lowest)
        {
          reading = reading - changeamnt; 
        }
      }
      // Output reading for debugging
      PORTA = reading;
      Serial.println(reading);
      Serial3.println(reading);
    }
    // store reading of A and millis for next loop
    lastA = encA;
    lastTime = currentTime;

  }

}
