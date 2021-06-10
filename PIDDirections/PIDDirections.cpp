class PIDDirections
{
public:
    Direction *target = new Direction();
    Direction *_feedback = new Direction();
    Direction *output = new Direction();
    long interval = 10000;
    long prevtime = 0;
    double xKp = 0.08, xKi = 0, xKd = 0;

o
    double yKp = 0.08, yKi = 0, yKd = 0;
    double rKp = 0.6, rKi = 0, rKd = 0;
    PID *fxPID, *fyPID, *frPID;
    bool keepHistory = true;
    bool continueRotation = false;
    long prevX = 0, prevY = 0, prevR = 0;
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
            feedback.compute();
            
            Serial.print("Feed Back From Sensor : ");
            _feedback->display();
            Serial.println();

            _feedback->fx -= prevX;
            _feedback->fy -= prevY;
            _feedback->fr -= prevR;

            Serial.print("Prev Reading");
            Serial.println("X : " + String(prevX)+"  Y : " + String(prevY)+ "  R : " + String(prevR));

            Serial.print("Feed After Subtracting Prev : ");
            _feedback->display();
            Serial.print("Target  ");
            target->display();
            Serial.println();
            fxPID->Compute();
            fyPID->Compute();
            frPID->Compute();
            
            Serial.print("output  ");
            output->display();
            if (keepHistory)
            {
                prevX += target->fx;
                prevY += target->fy;
                prevR += target->fr;
            }
            // Serial.println("target:"+ String((target->fr)));
            
        }
    }
} PID_xyr;