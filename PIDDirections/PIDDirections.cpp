class PIDDirections
{
public:
    Direction *target = new Direction();
    Direction *_feedback = new Direction();
    Direction *output = new Direction();
    long interval = 5000;
    long prevtime = 0;
    double xKp = 0.8, xKi = 0, xKd = 0;
    double yKp = 0.8, yKi = 0, yKd = 0;
    double rKp = 20.1, rKi =1.05, rKd = 0;
    double rcKp = 3.1, rcKi =1.05, rcKd = 0;
    PID *fxPID, *fyPID, *frPID;
    bool keepHistory = false;
    bool continueRotation = false;
    double prevX = 0, prevY = 0, prevR = 0;
    double rotationPerCount = 0;
    PIDDirections() {}
    PIDDirections(Direction *in, Direction *out, Direction *setp)
    {
        set(in, out, setp);
    }
    void set(Direction *in, Direction *out, Direction *setp)
    {
        target = setp;
        _feedback = in;
        output = out;
       
    }
    void setup()
    {    
        fxPID = new PID(&_feedback->fx, &output->fx, &target->fx, xKp, xKi, xKd, DIRECT);
        fyPID = new PID(&_feedback->fy, &output->fy, &target->fy, yKp, yKi, yKd, DIRECT);
        frPID = new PID(&_feedback->fr, &output->fr, &target->fr, rKp, rKi, rKd, DIRECT);
        fxPID->SetMode(AUTOMATIC);
        fxPID->SetSampleTime(1);

        fyPID->SetMode(AUTOMATIC);
        fyPID->SetSampleTime(1);

        frPID->SetMode(AUTOMATIC);
        frPID->SetSampleTime(1);

        fxPID->SetOutputLimits(-255, 255);
        fyPID->SetOutputLimits(-255, 255);
        frPID->SetOutputLimits(-255, 255);
    }
    void compute()
    {
        if (micros() - prevtime > interval)
        {
            prevtime = micros();
            if (continueRotation){
                frPID->SetTunings(rcKp,rcKi,rcKd);
            }
            // Serial.print("target  ");
            // target->display();
            feedback.compute();
            // _feedback->display();
            
            _feedback->fx -= prevX;
            _feedback->fy -= prevY;
            _feedback->fr -= prevR;
            // Serial.print("feedback  ");
            // _feedback->display();
            fxPID->Compute();
            fyPID->Compute();
            frPID->Compute();
            // Serial.print("output  ");
            // output->display();
            if(continueRotation){
                rotationPerCount = (target->fr * (interval/1000))/1000;
                prevR+=rotationPerCount;
            }
            if (keepHistory)
            {
                prevX += target->fx;
                prevY += target->fy;
            }
            // Serial.println("target:"+ String((target->fr)));
            
        }
    }
} PID_xyr;