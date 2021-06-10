class odometry
{
public:
    double m1_x = 1;
    double m1_y = 1;
    double m1_r = -1;
    Direction *directions = new Direction();
    MotorSpeeds *ms = new MotorSpeeds();
    double m2_x = 1;
    double m2_y = -1;
    double m2_r = -1;

    double m3_x = -1;
    double m3_y = -1;
    double m3_r = -1;

    double m4_x = -1;
    double m4_y = 1;
    double m4_r = -1;
    double max = 0;

    
    void setDirections(Direction *d)
    {
        this->directions = d;
    }

    void setMotors(MotorSpeeds *m){
        this->ms = m;
    }
    void manageMax(int num){
        if(abs(num) > abs(max))
            max = abs(num);
    }
    int mapFun(int m){
        return map(m,-max,max,-255,255);
    }
    void mapAll(){
        ms->m1=mapFun(ms->m1);
        ms->m2=mapFun(ms->m2);
        ms->m3=mapFun(ms->m3);
        ms->m4=mapFun(ms->m4);
    }
    void compute()
    {
        // directions->display();
        ms->m1 = (m1_x * directions->fx + m1_y * directions->fy + m1_r * directions->fr);
        max = abs(ms->m1);
        ms->m2 = (m2_x * directions->fx + m2_y * directions->fy + m2_r * directions->fr);
        manageMax(ms->m2);
        ms->m3 = (m3_x * directions->fx + m3_y * directions->fy + m3_r * directions->fr);
        manageMax(ms->m3);
        ms->m4 = (m4_x * directions->fx + m4_y * directions->fy + m4_r * directions->fr);
        manageMax(ms->m4);
        // Serial.println("max: "+String(max));
        if(max>255){
            mapAll();
        }
        // ms->display();
    }
} OdometryHelper;