class PIDRatio
{
public:
    Direction *target = new Direction();
    Direction *prevFeedback = new Direction();
    Direction *currentFeedback = new Direction();
    Direction *_feedback = new Direction();
    Direction *output = new Direction();
    Direction *UserIn = new Direction();
    optimizer *opt = new optimizer();
    long interval = 10000;
    long prevtime = 0;
    double xKp = 10, xKi = 0, xKd = 0;
    double yKp = 10, yKi = 0, yKd = 0;
    double rKp = 10, rKi = 0, rKd = 0;
    PID *fxPID, *fyPID, *frPID;

    PIDRatio() {}
    PIDRatio(Direction *in, Direction *out, Direction *setp)
    {
        set(in, out, setp);
    }
    void set(Direction *in, Direction *out, Direction *setp)
    {
        UserIn = setp;
        _feedback = in;
        output = out;
       opt->set(UserIn, currentFeedback);
    }
    void setup()
    {    
        fxPID = new PID(&currentFeedback->rfx, &output->fx, &target->fx, xKp, xKi, xKd, DIRECT);
        fyPID = new PID(&currentFeedback->rfy, &output->fy, &target->fy, yKp, yKi, yKd, DIRECT);
        frPID = new PID(&currentFeedback->rfr, &output->fr, &target->fr, rKp, rKi, rKd, DIRECT);
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
            // feedback.compute();
            vbase.feedbackCompute();
            currentFeedback->fx=_feedback->fx - prevFeedback->fx;
            currentFeedback->fy=_feedback->fy - prevFeedback->fy;
            currentFeedback->fr=_feedback->fr - prevFeedback->fr;

            // currentFeedback->displayGraph();
            // prevFeedback->display();

            currentFeedback->process();
            UserIn->process();
            modifyUserInput();
            if(UserIn->isZero){
                UserIn->magnitude = 50;
            }
            
           
            fxPID->Compute();
            fyPID->Compute();
            frPID->Compute();
            // Serial.printf("%lf, %lf, %lf\n",_feedback->rfx, output->fx, target->fx);
            
            output->process();
            output->magnitude = UserIn->magnitude;
            output->invertProcess();

            //REDUCE VALUE OF FEEDBACK BY USING UserIn RATIO
            if(!UserIn->isZero){
                opt->minimize();
            }
            prevFeedback->fx=_feedback->fx - currentFeedback->fx;
            prevFeedback->fy=_feedback->fy - currentFeedback->fy;
            prevFeedback->fr=_feedback->fr - currentFeedback->fr;


        }
    }

    void modifyUserInput(){
        target->rfx = UserIn->rfx;
        target->rfy = UserIn->rfy;
        target->rfr = UserIn->rfr;
        target->magnitude = 255;
        target->invertProcess();
    }
} PID_ratio;