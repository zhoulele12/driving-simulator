#include <SparkFun_TB6612.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//#include <avr/wdt.h>
//#include "DeviceDriverSet_xxx0.h"
//#include "ApplicationFunctionSet_xxx0.cpp"
#define PIN_Motor_PWMA 5
#define PIN_Motor_PWMB 6
#define PIN_Motor_BIN_1 8
#define PIN_Motor_AIN_1 7
#define PIN_Motor_STBY 3
//DeviceDriverSet_Motor AppMotor;
//Application_xxx Application_SmartRobotCarxxx0;

//RF24 radio(9,10);
struct Signal{
  byte throttle;
  byte turn;
};
int throttle;
int turn;

Signal data;

const uint64_t pipeIn = 0xE9E8F0F0E1LL;

void setup() {
  Serial.begin(9600);
//  radio.begin();
//  radio.openReadingPipe(1,pipeIn);
//  radio.startListening();
//  AppMotor.DeviceDriverSet_Motor_Init();
  pinMode(PIN_Motor_PWMA, OUTPUT);
  pinMode(PIN_Motor_PWMB, OUTPUT);
  pinMode(PIN_Motor_AIN_1, OUTPUT);
  pinMode(PIN_Motor_BIN_1, OUTPUT);
  pinMode(PIN_Motor_STBY, OUTPUT);
  pinMode(A1,OUTPUT);
//  pinMode(10, OUTPUT);


//  delay(2000);

}


//void recvData()
//{
//  while (radio.available()) {
//    radio.read(&data,sizeof(Signal));   
//  }
//}


void loop() {
//  recvData();
//  throttle = data.throttle;
//  turn = data.turn;
  uint8_t throttle = analogRead(A1);
  Serial.println("throttle: ");
  Serial.println(throttle);
//  Serial.println("turn: ");
//  Serial.println(turn);
  
//  Application_SmartRobotCarxxx0.Motion_Control = 0;


//  ApplicationFunctionSet_SmartRobotCarMotionControl(Application_SmartRobotCarxxx0.Motion_Control /*direction*/, throttle-100 /*speed*/);
  uint8_t velocity = throttle;
//  digitalWrite(PIN_Motor_STBY, HIGH);
//  digitalWrite(PIN_Motor_AIN_1, HIGH);
//  analogWrite(PIN_Motor_PWMA, velocity);
//  digitalWrite(PIN_Motor_BIN_1, HIGH);
//  analogWrite(PIN_Motor_PWMB, velocity);
  
//  delay(50);
  
}






//void DeviceDriverSet_Motor::DeviceDriverSet_Motor_control(boolean direction_A, uint8_t speed_A, //A组电机参数
//                                                          boolean direction_B, uint8_t speed_B, //B组电机参数
//                                                          boolean controlED                     //AB使能允许 true
//                                                          )                                     //电机控制
//{
//
//  if (controlED == control_enable) //使能允许？
//  {
//    digitalWrite(PIN_Motor_STBY, HIGH);
//    { //A...Right
//
//      switch (direction_A) //方向控制
//      {
//      case direction_just:
//        digitalWrite(PIN_Motor_AIN_1, HIGH);
//        analogWrite(PIN_Motor_PWMA, speed_A);
//        break;
//      case direction_back:
//
//        digitalWrite(PIN_Motor_AIN_1, LOW);
//        analogWrite(PIN_Motor_PWMA, speed_A);
//        break;
//      case direction_void:
//        analogWrite(PIN_Motor_PWMA, 0);
//        digitalWrite(PIN_Motor_STBY, LOW);
//        break;
//      default:
//        analogWrite(PIN_Motor_PWMA, 0);
//        digitalWrite(PIN_Motor_STBY, LOW);
//        break;
//      }
//    }
//
//    { //B...Left
//      switch (direction_B)
//      {
//      case direction_just:
//        digitalWrite(PIN_Motor_BIN_1, HIGH);
//
//        analogWrite(PIN_Motor_PWMB, speed_B);
//        break;
//      case direction_back:
//        digitalWrite(PIN_Motor_BIN_1, LOW);
//        analogWrite(PIN_Motor_PWMB, speed_B);
//        break;
//      case direction_void:
//        analogWrite(PIN_Motor_PWMB, 0);
//        digitalWrite(PIN_Motor_STBY, LOW);
//        break;
//      default:
//        analogWrite(PIN_Motor_PWMB, 0);
//        digitalWrite(PIN_Motor_STBY, LOW);
//        break;
//      }
//    }
//  }
//  else
//  {
//    digitalWrite(PIN_Motor_STBY, LOW);
//    return;
//  }
//}
