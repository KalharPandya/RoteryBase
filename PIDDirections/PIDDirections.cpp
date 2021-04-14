class PIDDirections
{
public:
    Direction *target = new Direction();
    Direction *_feedback = new Direction();
    Direction *output = new Direction();
    long interval = 500;
    long prevtime = 0;
    double xKp = 0.5, xKi = 1, xKd = 0;
    double yKp = 0.5, yKi = 1, yKd = 0;
    double rKp = 20, rKi = 0, rKd = 0;
    PID *fxPID, *fyPID, *frPID;
    bool keepHistory = true;
    double prevX = 0, prevY = 0;
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
            // target->display();
            feedback.compute();
            _feedback->display();
            _feedback->fx -= prevX;
            _feedback->fy -= prevY;
            fxPID->Compute();
            fyPID->Compute();
            frPID->Compute();
            // output->display();
            if (keepHistory)
            {
                prevX += target->fx;
                prevY += target->fy;
            }
        }
    }
} PID_xyr;