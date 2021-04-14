#include<RoteryBase.h>
Direction UserIn, Translated, real,PID_out;
MotorSpeeds finalSpeeds;
translateXY translator;
MotorSpeeds ms;
Motor m1(7, 6, 5), m2(8, 25, 23), m4(45, 47, 49), m3(44, 35, 33);
UniversalEncoder Enc2(3, 4, 1), Enc1(2, 27, -1);

encoderFeedback efx(&Enc1), efy(&Enc2);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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
//  UserIn.fx = 100;
  UserIn.fr = 90;
}

void loop() {
//  Serial.println(Enc1.getReadings());
//  Translated.display();

  PID_xyr.compute();
//  real.display();
//  PID_out.display();
  OdometryHelper.compute();

  base.apply();


} 
