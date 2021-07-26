#include<translator.h>

translateXY t;
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
}
double x, y, r;
String a;
void loop() {
  if (Serial.available()) {
    a = Serial.readStringUntil(',');
    x = a.toDouble();

    a = Serial.readStringUntil(',');
    y = a.toDouble();

    a = Serial.readStringUntil(',');
    r = a.toDouble();

    t.setXY(x, y);
    Serial.println(r);
    t.setCurrentAngle(r);
    t.compute();
    //    Serial.print("OX: "+String(x));
    //    Serial.println("Oy: "+String(y));
    //Serial.print("OX: " + String(t.getX()));
    //Serial.println("  OY: " + String(t.getY()));

  }
}