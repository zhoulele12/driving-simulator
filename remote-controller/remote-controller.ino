#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeOut = 0xE9E8F0F0E1LL;

RF24 radio(7,8);

struct Signal{
  byte throttle;
};

Signal data;

#define joyBX A2
#define joyBY A3

void ResetData() 
{
  data.throttle = 0;

}
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipeOut);
  radio.stopListening();
//  ResetData();
  
}
 
void loop() {
  // put your main code here, to run repeatedly:
  int bxValue = analogRead(joyBX);
  int byValue = analogRead(joyBY);

  data.throttle = map(bxValue,0,1023,0,90);
  
  Serial.println(data.throttle);
  radio.write(&data,sizeof(Signal));
  delay(100);
}
