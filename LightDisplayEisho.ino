#include <Wire.h>

int digitsSince9 = 0;

int lightpins[] = {10, 11, 12, 7, 8, 9, 4, 5, 6};
boolean light[] = {true, false, true, false, true, false, true, false, true};

void setup()
{
  for(int i = 0; i < 9; i++){
    pinMode(lightpins[i], OUTPUT);
  }
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop()
{
  for(int i = 0; i < 9; i ++){
    digitalWrite(lightpins[i], light[i]);
  }
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(0 < Wire.available()) // loop through all but the last
  {
    int x = Wire.read();
    if ( x== 9){
      digitsSince9 = 0;
     // Serial.println(); 
    }else{
      if(digitsSince9 >= 0 && digitsSince9 < 9){
        if (x ==0) {
          light[digitsSince9] = false;
        }
        else {
          light[digitsSince9] = true;
        }
      }
      digitsSince9 ++;
    }
    Serial.print(x);// receive byte as a character    // print the character
  }
         // print the integer
}
