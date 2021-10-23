#include <Wire.h>
#include <PID_v1.h>
#include <Motor.h>
#include <MPU6050_tockn.h>
#include "States/States.cpp"
#include "optimizer/optimizer.cpp"
#include "virtualBase/virtualBase.cpp"
// #include "translatorXY/translator.h"
#include "./Commander/Commander.cpp"
#include "odometry/odometry.cpp"
#include "encoderFeedback/encoderFeedback.h"
#include "mpu/mpu.cpp"

#include "MotorHandler/MotorHandler.cpp"
#include "feedbackHandler/feedbackHandler.cpp"
#include "PIDDirections/PIDDirections.cpp"
#include "PIDRatio/PIDRatio.cpp"

// translateXY *translate;
class RoteryBase{
    public:
    Direction *UserInput = new Direction();
    Direction *translated = new Direction();
    Direction *feedbackDirections = feedback.directions;
    Direction *PID_Output = new Direction();
    MotorSpeeds *FinalSpeeds = new MotorSpeeds();
    RoteryBase(){}
    void setup()
    {
        base.setMotorSpeeds(FinalSpeeds);
        feedback.setup();
        //translate->setDirections( UserInput, translated);    //changed
        PID_xyr.set(translated,feedbackDirections, feedbackDirections);
    }
    void compute(){
        // translate->setCurrentAngle(mpu.getAngle());
        // translate->compute();

        PID_xyr.compute();
        base.apply();
    }

};