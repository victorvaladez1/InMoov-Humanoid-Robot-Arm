#include <Servo.h>
#define numOfValsRec 5
#define digitsPerValRec 1

Servo servoThumb;
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;

int valRec[numOfValsRec];
//$00000
int stringLength = numOfValsRec * digitsPerValRec + 1; //$00000
int counter = 0;
bool counterStart = false;
String receivedString;



void setup() {
  Serial.begin(9600);
  servoThumb.attach(8);
  servoIndex.attach(9);
  servoMiddle.attach(10);
  servoRing.attach(11);
  servoPinky.attach(12);

}

void receiveData() {
  while (Serial.available())
  {
    char c = Serial.read();
    if (c == '$') {
      counterStart = true;
    }
    if (counterStart) {
      if (counter < stringLength) {
        receivedString = String(receivedString + c);
        counter++;
      }
      if (counter >= stringLength) {
        //$00000
        for (int i = 0; i < numOfValsRec; i++)
        {
          int num = (i * digitsPerValRec) + 1;
          valRec[i] = receivedString.substring(num, num + digitsPerValRec).toInt();
        }
        receivedString = "";
        counter = 0;
        counterStart = false;

      }
    }
  }
}

void loop() {
  receiveData();
  if(valRec[0] == 0){servoThumb.write(180);}else{servoThumb.write(1);}
  if(valRec[1] == 0){servoIndex.write(180);}else{servoIndex.write(1);}
  if(valRec[2] == 0){servoMiddle.write(180);}else{servoMiddle.write(1);}
  if(valRec[3] == 0){servoRing.write(180);}else{servoRing.write(1);}
  if(valRec[4] == 0){servoPinky.write(180);}else{servoPinky.write(1);}
}
