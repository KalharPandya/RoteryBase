class encoderFeedback{
    public:
    int CPR = 720;
    int interval = 10;
    double wheelDiametre = 58;
    long prevReadings = 0;
    bool keepHistory = true;
    long readings = 0;
    long double rpm = 0;
    UniversalEncoder *enc = new UniversalEncoder();
    encoderFeedback(){}
    encoderFeedback(UniversalEncoder *e){
        setEncoder(e);
    }
    void setEncoder(UniversalEncoder *e){
        enc = e;
    }
    long getReadings(){
        readings = enc->getReadings();
        // Serial.println(String(readings)+"read");
        rpm = (((double)(readings - prevReadings)/CPR)/((double)interval)) * (1000*60);
        if(!keepHistory){
            prevReadings = readings;
        }
        return rpm;     
    }
    void reset(){
        enc->reset();
    }
};

// (((double)Enc1->getReadings() / CPR) * ((double)1000 * 60 / interval) * 0.058);