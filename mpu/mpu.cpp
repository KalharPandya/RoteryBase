MPU6050 mpu6050(Wire);
void setMpu6050()
{
    Wire.begin();
    mpu6050.begin();
}
class mpu
{
public:
    double currAngle = 0;
    bool autoCalibrate = true;
    int directionalOffset = 1;
    void setup(){
        setMpu6050();
        if(autoCalibrate){
            calibrate();
        }
    }
    void setOffset(int off = 1)
    {
        directionalOffset = off;
    }
    double getReadings()
    {
        mpu6050.update();
        currAngle = mpu6050.getAngleZ() * directionalOffset;
        return currAngle;
    }
    double getAngle(){
        mpu6050.update();
        currAngle = mpu6050.getAngleZ() * directionalOffset;
        return currAngle;
    }
    void calibrate()
    {
        mpu6050.calcGyroOffsets(true);
    }
} mpu;
