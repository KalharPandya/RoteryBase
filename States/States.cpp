class MotorSpeeds{
    public:
    String a;
    int m1=0,m2=0, m3=0, m4=0;
    void display(){
        Serial.println("M1: "+String(m1)+"\tM2: "+String(m2)+"\tM3: "+String(m3)+"\tM4: "+String(m4));
    }
    void input(){
        a=Serial.readStringUntil(',');
        m1=a.toDouble();
        a=Serial.readStringUntil(',');
        m2=a.toDouble();
        a=Serial.readStringUntil(',');
        m3=a.toDouble();
        a=Serial.readStringUntil(',');
        m4=a.toDouble();
    }
};

class Direction{
    public:
    String a;
    double fx = 0, fy = 0, fr = 0;
    void display(){
        Serial.println("fx: "+String(fx)+"\tfy: "+String(fy)+"\tfr: "+String(fr));
    }
    double max(){
        if(fx>fy){
            if(fx > fr)
                return fx;
            else
                return fr;
        }
        else{
            if(fy>fr)
                return fy;
            else
                return fr;
        }

    }

    double absMax()
    {
        if (abs(fx) > abs(fy))
        {
            if (abs(fx) > abs(fr))
                return abs(fx);
            else
                return abs(fr);
        }
        else
        {
            if (abs(fy) > abs(fr))
                return abs(fy);
            else
                return abs(fr);
        }
    }
    void input(){
        a=Serial.readStringUntil(',');
        fx=a.toDouble();
        a=Serial.readStringUntil(',');
        fy=a.toDouble();
        a=Serial.readStringUntil(',');
        fr=a.toDouble();
    }
    
};