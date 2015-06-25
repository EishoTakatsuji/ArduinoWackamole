
#include <Wire.h>
int cols[] = {6, 7, 8}; //10
int  rows[] = {10, 11, 12}; //9
byte  buttonStates[] = {0,0,0,0,0,0,0,0,0};

void setup() {
  Wire.begin();
  for (int i = 0; i < 3; i++) {
    pinMode(rows[i], OUTPUT);
  }
  Serial.begin(9600);
}



void loop() {
 


  
  int i = 0;
  for (int r = 0; r < 3; r++) {
    digitalWrite(rows[r], HIGH);
    for (int c = 0; c < 3; c++) {
      pinMode(cols[c], OUTPUT);
      pinMode(cols[c], INPUT);
      //Serial.print(digitalRead(cols[c]));
      buttonStates[i] = (byte) digitalRead(cols[c]);
      i ++;
    }
    digitalWrite(rows[r], LOW);
    //Serial.println();
  }

  //Serial.println();
            // sends one byte


  //send the data to the other arduino
  //initialization number
  byte init = 9;
  Wire.beginTransmission(4);
  Wire.write(init);
  Wire.endTransmission();
  
  //send each of the buttons states, stored in the button state array
  for(int k = 0; k < 9; k ++){
      Wire.beginTransmission(4);
      Wire.write(buttonStates[k]);
      Wire.endTransmission();
  }


}
