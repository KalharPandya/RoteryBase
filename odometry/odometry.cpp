class odometry
{
public:
    double m1_x = 0.7071;
    double m1_y = 0.7071;
    double m1_r = 1;
    Direction *directions = new Direction();
    MotorSpeeds *ms = new MotorSpeeds();
    double m2_x = 0.7071;
    double m2_y = -0.7071;
    double m2_r = 1;

    double m3_x = -0.7071;
    double m3_y = -0.7071;
    double m3_r = 1;

    double m4_x = -0.7071;
    double m4_y = 0.7071;
    double m4_r = 1;
    double max_coef;

    odometry()
    {
        max_coef = abs(m1_x) + abs(m1_y) + abs(m1_r);
        m1_x = m1_x / max_coef;
        m2_x = m2_x / max_coef;
        m3_x = m3_x / max_coef;
        m4_x = m4_x / max_coef;

        m1_y = m1_y / max_coef;
        m2_y = m2_y / max_coef;
        m3_y = m3_y / max_coef;
        m4_y = m4_y / max_coef;

        m1_r = m1_r / max_coef;
        m2_r = m2_r / max_coef;
        m3_r = m3_r / max_coef;
        m4_r = m4_r / max_coef;
    }

    void setDirections(Direction *d)
    {
        this->directions = d;
    }

    void setMotors(MotorSpeeds *m){
        this->ms = m;
    }
    void compute()
    {
        ms->m1 = (m1_x * directions->fx + m1_y * directions->fy + m1_r * directions->fr);
        ms->m2 = (m2_x * directions->fx + m2_y * directions->fy + m2_r * directions->fr);
        ms->m3 = (m3_x * directions->fx + m3_y * directions->fy + m3_r * directions->fr);
        ms->m4 = (m4_x * directions->fx + m4_y * directions->fy + m4_r * directions->fr);
    }
} OdometryHelper;