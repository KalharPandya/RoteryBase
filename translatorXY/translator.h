#include <math.h>
#include <Arduino.h>
class translateXY
{
public:
   int add = 0;
   double currentTheta, targetTheta, mag, diff;
   Direction *directionIn = new Direction();
   Direction *directionOut = new Direction();
   translateXY()
   {
      currentTheta = 0;
      targetTheta = 0;
   }
   double degreeToRadian(double t)
   {
      return (t / 180) * 3.14;
   }
   double radianToDegree(double t)
   {
      return (t * 180) / 3.14;
   }
   void setDirections(Direction *din, Direction *dout)
   {
      directionIn = din;
      directionOut = dout;
   }

   void setCurrentAngle(double a)
   {
      // Serial.println(a);
      currentTheta = degreeToRadian(a);
   }

   void compute()
   {
      mag = sqrt(pow(directionIn->fx, 2) + pow(directionIn->fy, 2));
      if (directionIn->fx > 0)
      {
         if (directionIn->fy < 0)
         {
            add = 270;
         }
         else if (directionIn->fy >= 0)
         {
            add = 0;
         }
      }
      else if (directionIn->fx < 0)
      {
         if (directionIn->fy < 0)
         {
            add = 180;
         }
         else if (directionIn->fy >= 0)
         {
            add = 90;
         }
      }
      if (directionIn->fx == 0)
      {
         if (directionIn->fy < 0)
         {
            targetTheta = -1.57;
         }
         else if (directionIn->fy >= 0)
         {
            targetTheta = 1.57;
         }
      }
      else
      {

         targetTheta = abs(atan(directionIn->fy / directionIn->fx)) + degreeToRadian(add);
      }

      diff = targetTheta - currentTheta;
      // Serial.println(targetTheta);
      // Serial.println(String(radianToDegree(targetTheta)) +"Add = "+ String(add));
      // targetTheta = degreeToRadian(targetTheta);
      directionOut->fx = mag * cos(diff);
      directionOut->fy = mag * sin(diff);
   }

   //     void setDirections(Direction *d, Direction *e);
   //     void setCurrentAngle(double ang = 0);
   //     void compute();
};