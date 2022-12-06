#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeOut = 0xE9E8F0F0E1LL;

RF24 radio(7,8);

struct Signal{
  byte throttle;
 byte turn;
};

Signal data;
#define acc0 A2
#define acc1 A3
#define acc2 A4
#define acc3 A5

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
  int bit1 = analogRead(acc0);
  int bit2 = analogRead(acc1);
  int bit3 = analogRead(acc2);
  int bit4 = analogRead(acc3);
  int turn_val= 0;
  if (bit1 > 500){
    turn_val = turn_val + 1;
  }
  if (bit2 >500){
    turn_val = turn_val + 2;
  }
  if (bit3 >500){
    turn_val = turn_val + 4;
  }
  if (bit4 > 500){
    turn_val = turn_val + 8;
  }
  // Serial.println(turn_val);
//  Serial.println("bit1");
//  Serial.println(bit1);
//  Serial.println("bit2");
//  Serial.println(bit2);
//  Serial.println("bit3");
//  Serial.println(bit3);
//  Serial.println("bit4");
//  Serial.println(bit4);
  // 9 to 0 -> left
  // 15 to 10 -> right
//  if(turn_val<8){
//    data.throttle = (8-turn_val)*10;
//  } else {
//    data.throttle = 80 + (16-turn_val)*20;
//  }
  if(turn_val<8){
    data.throttle = (8-turn_val)*10;
  } else {
    data.throttle = 80 + (16-turn_val)*20;
  }
  
//  int bxValue = analogRead(joyBX);
//  int byValue = analogRead(joyBY);

//  data.throttle = map(bxValue,0,1023,0,255);
//  data.turn = map(byValue,0,1023,0,255);

  data.turn = 128;
  Serial.println(data.throttle);
  radio.write(&data,sizeof(Signal));
  delay(100);
}
