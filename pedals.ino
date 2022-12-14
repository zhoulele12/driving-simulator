/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-force-sensor
 */

#define BRAKE_PEDAL A0 // the FSR and 10K pulldown are connected to A0
#define GAS_PEDAL A1
#define first A2
#define second A3
#define third A4
#define fourth A5
void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  int brakeReading = analogRead(BRAKE_PEDAL);
  int gasReading = analogRead(GAS_PEDAL);
  int bit1 = analogRead(first);
  int bit2 = analogRead(second);
  int bit3 = analogRead(third);
  int bit4 = analogRead(fourth);
  int turn_val= 0;

  // Serial.print("Brake reading = ");
  // Serial.print(brakeReading); // print the raw analog reading
  // Serial.print("\n");
  // Serial.print("Gas reading = ");
  // Serial.print(gasReading); // print the raw analog reading
  // Serial.print("\n");
  if (bit1 > 500){
    turn_val = turn_val + 1;
  }
  if (bit2 >500){
    turn_val = turn_val + 2;
  }
  if (bit3 >500){
    turn_val = turn_val +4;
  }
  if (bit4 > 500){
    turn_val = turn_val + 8;
  }
if (brakeReading > 10)
{
  digitalWrite(5, HIGH);

}
else{
  digitalWrite(5, LOW);
}
 if ((gasReading > 10 && gasReading <= 350))
  {
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    // digitalWrite(5, HIGH);
  }
  // else if ((gasReading > 10 && gasReading <= 350))
  // {
  //   digitalWrite(3, HIGH);
  //   digitalWrite(4, LOW);
  //   // digitalWrite(5, LOW);
  // }
  else if (gasReading >350 && gasReading <=650)
  {
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    Serial.println("true");
    Serial.println(gasReading);
    // digitalWrite(5, HIGH);
  }
  // else if (gasReading >350 && gasReading <=650)
  // {
  //   digitalWrite(3, LOW);
  //   digitalWrite(4, HIGH);
  //   // digitalWrite(5, LOW);
  // }
  else if (gasReading > 650)
  {
    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
    // digitalWrite(5, HIGH);
  }
  // else if (gasReading > 650 && brakeReading == 0)
  // {
  //   digitalWrite(4, HIGH);
  //   digitalWrite(3, HIGH);
  //   // digitalWrite(5, LOW);
  // }
  // else if (brakeReading >0){
  //   digitalWrite(4, LOW);
  //   digitalWrite(3, LOW);
  //   // digitalWrite(5, HIGH);
  // }
  else{
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    // digitalWrite(5, LOW);

  }


  // if ((gasReading > 10 && gasReading <= 350) && brakeReading >0)
  // {
  //   digitalWrite(3, HIGH);
  //   digitalWrite(4, LOW);
  //   digitalWrite(5, HIGH);
  // }
  // else if ((gasReading > 10 && gasReading <= 350) && brakeReading == 0)
  // {
  //   digitalWrite(3, HIGH);
  //   digitalWrite(4, LOW);
  //   digitalWrite(5, LOW);
  // }
  // else if (gasReading >350 && gasReading <=650 && brakeReading > 0)
  // {
  //   digitalWrite(3, LOW);
  //   digitalWrite(4, HIGH);
  //   digitalWrite(5, HIGH);
  // }
  // else if (gasReading >350 && gasReading <=650 && brakeReading == 0)
  // {
  //   digitalWrite(3, LOW);
  //   digitalWrite(4, HIGH);
  //   digitalWrite(5, LOW);
  // }
  // else if (gasReading > 650 && brakeReading > 0)
  // {
  //   digitalWrite(4, HIGH);
  //   digitalWrite(3, HIGH);
  //   digitalWrite(5, HIGH);
  // }
  // else if (gasReading > 650 && brakeReading == 0)
  // {
  //   digitalWrite(4, HIGH);
  //   digitalWrite(3, HIGH);
  //   digitalWrite(5, LOW);
  // }
  // else if (brakeReading >0){
  //   digitalWrite(4, LOW);
  //   digitalWrite(3, LOW);
  //   digitalWrite(5, HIGH);
  // }
  // else{
  //   digitalWrite(4, LOW);
  //   digitalWrite(3, LOW);
  //   digitalWrite(5, LOW);

  // }
  // Serial.print(turn_val);
  // Serial.print("\n");
 
  // if (analogReading < 10)       // from 0 to 9
  //   Serial.println(" -> no pressure");
  // else if (analogReading < 200) // from 10 to 199
  //   Serial.println(" -> light touch");
  // else if (analogReading < 500) // from 200 to 499
  //   Serial.println(" -> light squeeze");
  // else if (analogReading < 800) // from 500 to 799
  //   Serial.println(" -> medium squeeze");
  // else // from 800 to 1023
  //   Serial.println(" -> big squeeze");

  delay(100);
}
