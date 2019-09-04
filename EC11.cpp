#include<Arduino.h>

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;
//const byte pin2 = D2;
//const byte pin3 = D3;

//void ICACHE_RAM_ATTR ISRoutine ();

void ICACHE_RAM_ATTR handleInterrupt() {
  int MSB = digitalRead(D2); //MSB = most significant bit
  int LSB = digitalRead(D3); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(D2, INPUT_PULLUP); 
  pinMode(D3, INPUT_PULLUP);

  //digitalWrite(D2, HIGH); //turn pullup resistor on
  //digitalWrite(D3, HIGH); //turn pullup resistor on  

  attachInterrupt(digitalPinToInterrupt(D2), handleInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(D3), handleInterrupt, CHANGE);
}

void loop() {
    Serial.print("Encoder: ");
    Serial.println(encoderValue);
    delay(1000);
}