class PIDDirections
{
public:
    Direction *target = new Direction();
    Direction *_feedback = new Direction();
    Direction *output = new Direction();
    double xKp = 0, xKi = 0, xKd = 0;
	double yKp = 0, yKi = 0, yKd = 0;
	double rKp = 0, rKi = 0, rKd = 0;
    PID *fxPID, *fyPID, *frPID;
    PIDDirections(){}
    PIDDirections(Direction *tar, Direction *feed, Direction *out){
        set(tar, feed, out);
    }
    void set(Direction *tar, Direction *feed, Direction *out){
        target = tar;
        _feedback = feed;
        output = out;
    }
    void setup(){
        fxPID = new PID(&_feedback->fx, &output->fx, &target->fx, xKp, xKi, xKd, DIRECT);
        fyPID = new PID(&_feedback->fy, &output->fy, &target->fy, yKp, yKi, yKd, DIRECT);
        frPID = new PID(&_feedback->fr, &output->fr, &target->fr, rKp, rKi, rKd, DIRECT);
    }
    void compute(){
        fxPID->Compute();
        fyPID->Compute();
        frPID->Compute();
    }
}PID_xyr;