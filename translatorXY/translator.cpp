// #include "translator.h"
// double degreeToRadian(double t)
// {
//     return (t / 180) * 3.14;
// }
// void translateXY::setDirections(Direction *din, Direction *dout)
// {
//     translateXY::directionIn = din;
//     translateXY::directionOut = dout;
// }
// void translateXY::setCurrentAngle(double a)
// {
//     // Serial.println(a);
//     translateXY::currentTheta = degreeToRadian(a);
// }

// void translateXY::compute()
// {
//     translateXY::mag = sqrt(pow(translateXY::directionIn > fx, 2) + pow(translateXY::directionIn->fy, 2));
//     if (fx == 0)
//     {
//         translateXY::targetTheta = 1.57;
//     }
//     else
//         translateXY::targetTheta = atan(translateXY::fy / translateXY::fx);
//     translateXY::diff = translateXY::targetTheta - translateXY::currentTheta;
//     // Serial.println(translateXY::currentTheta);
//     translateXY::directionOut->fx = translateXY::mag * cos(translateXY::diff);
//     translateXY::directionOut->fy = translateXY::mag * sin(translateXY::diff);
// }

// double translateXY::getX(){
//     return translateXY::directionOut->fx;
// }
// double translateXY::getY(){
//     return translateXY::directionOut->fy;
// }