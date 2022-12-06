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
#define BRAKE_PEDAL A0 // the FSR and 10K pulldown are connected to A0
#define GAS_PEDAL A1
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
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  radio.begin();
  radio.openWritingPipe(pipeOut);
  radio.stopListening();
//  ResetData();
}
 
void loop() {
  // put your main code here, to run repeatedly:
  int brakeReading = analogRead(BRAKE_PEDAL);
  int gasReading = analogRead(GAS_PEDAL);
  
  if (brakeReading > 10){
      digitalWrite(5, HIGH);
      data.throttle = 0;
  }
  else{
    digitalWrite(5, LOW);

    if ((gasReading > 10 && gasReading <= 350))
      {
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);

      } else if (gasReading >350 && gasReading <=650) {
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
      } else if (gasReading > 650) {
        digitalWrite(4, HIGH);
        digitalWrite(3, HIGH);
      } else{
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
      }
    data.throttle = map(gasReading,0,1023,0,255);
  }
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

  // 9 to 0 -> left
  // 15 to 10 -> right

  if(turn_val<8){
    data.turn = (8-turn_val)*16;
  } else {
    data.turn = 128 + (16-turn_val)*16;
  }
  Serial.println(data.throttle);
  radio.write(&data,sizeof(Signal));
  delay(100);
}