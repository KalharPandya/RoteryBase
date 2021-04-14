class feedbackHandler{
    
    public:
    Direction *directions = new Direction();
    encoderFeedback *encX = new encoderFeedback();
    encoderFeedback *encY = new encoderFeedback();
    void setDirections(Direction *d)
    {
        this->directions = d;
    }
    void setup(){
        mpu.setup();
    }
    void setEncoderXY(encoderFeedback *x,encoderFeedback *y){
        encX = x;
        encY = y;
    }
    void compute(){
        directions -> fx = encX->getReadings();
        directions -> fy = encY->getReadings();
        directions -> fr = mpu.getReadings();
        // Serial.println("X:"+String(directions -> fx)+"\tY:"+String(directions -> fy )+"\tR:"+String(directions -> fr));
    }
    
}feedback;