#include<RoteryBase.h>
#include<ArduinoJSON.h>
json myObj;
Direction UserIn, Translated, real, PID_out;
MotorSpeeds finalSpeeds;
//translateXY translator;
//MotorSpeeds ms;
Motor m1(7, 5, 6), m2(8, 23, 25), m4(45, 49, 47), m3(44, 33, 35);
//Motor m1(7, 6, 5), m2(8, 25, 23), m4(45, 47, 49), m3(44, 35, 33);
UniversalEncoder Enc2(3, 4, 1), Enc1(2, 27, -1);

encoderFeedback efx(&Enc1), efy(&Enc2);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(250000);
  Serial3.begin(250000);

  Serial3.setTimeout(5);
  Serial.setTimeout(5);
  feedback.setup();
  feedback.setDirections(&real);
  feedback.setEncoderXY(&efx, &efy);
  OdometryHelper.setDirections(&PID_out);
  OdometryHelper.setMotors(&finalSpeeds);

  base.setMotorSpeeds(&finalSpeeds);
  base.set(&m1, &m2, &m3, &m4);

  PID_xyr.set(&real, &PID_out, &UserIn);
  PID_xyr.setup();

//     UserIn.fy =-90;
//     UserIn.fx = -90;
}

void loop() {
  
  //  Serial.println(Enc1.getReadings());
  //  Translated.display();
  // prev_Time=micros();

  if (Serial.available())
    UserIn.input();
  if (false && Serial3.available()) {
  
    if (Serial3.available() > 30) {
      while (Serial3.available() > 0) {
        Serial3.read();
        UserIn.fx = 0;//you are not audible
      UserIn.fy = 0;
      UserIn.fr = 0;
      }
    }

    else {
      String st = Serial3.readStringUntil('\r');
      myObj = parseJSON(st);
      Serial.println("Available Buffer " + String(Serial3.available()));
      Serial.println(myObj.getString());
      Serial.println("X : " + String(myObj.getDoubleValue("x")));
      Serial.println("y : " + String(myObj.getDoubleValue("y")));
      Serial.println("r : " + String(myObj.getDoubleValue("r")));
      Serial.println("Something" + String(Serial3.available()));
      Serial.println(Serial3.readStringUntil('\r'));
      UserIn.fx = myObj.getDoubleValue("x");//you are not audible
      UserIn.fy = myObj.getDoubleValue("y");
      UserIn.fr = myObj.getDoubleValue("r");

      //      PID_xyr.set(&real, &PID_out, &UserIn);
    }
  }
//  real.display();

  PID_xyr.compute();
  //  real.display();
    //PID_out.display();
 //   Serial.println(mpu.getAngle());
  OdometryHelper.compute();

  base.apply();


}