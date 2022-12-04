#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);
struct Signal{
  byte throttle;
  byte turn;
};
int throttle;
int turn;

Signal data;
void ResetData() 
{
  data.throttle = 0;

}

const uint64_t pipeIn = 0xE9E8F0F0E1LL;

void setup() {
  Serial.begin(9600);
//  ResetData();
  radio.begin();
  radio.openReadingPipe(1,pipeIn);
  radio.startListening();
//  pinMode(A1,OUTPUT);
}


void recvData()
{
  while (radio.available()) {
    radio.read(&data,sizeof(Signal));   
  }
}


void loop() {
  recvData();
  throttle = data.throttle;
  turn = data.turn;
  Serial.println("throttle: ");
  Serial.println(throttle);
  Serial.println("turn: ");
  Serial.println(turn);
//  analogWrite(A1,throttle);
  delay(50);
  
  
}
