MPU6050 mpu6050(Wire);
void setMpu6050()
{
    Wire.begin();
    mpu6050.begin();
}
class mpu
{
public:
    double currAngle = 0, readings;

    double rpm;
    bool autoCalibrate = true;
    int directionalOffset = 1;
    long prevReadings, prevTime;
    double rotationalOffset = 8;
    int interval = 10;
    bool keepHistory;
    void setup(bool history = true)
    {
        keepHistory = history;
        setMpu6050();
        if (autoCalibrate)
        {
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
        currAngle = mpu6050.getAngleZ() * directionalOffset * rotationalOffset;
        // Serial.print("Readings");
        // Serial.println(currAngle);
        return currAngle;
    }
    double getAngle()
    {
        mpu6050.update();
        currAngle = mpu6050.getAngleZ() * directionalOffset;
        return currAngle;
    }
    double getSpeed()
    {

        readings = getReadings();
        Serial.println(String(readings)+"Prev"+ + "read" + String(interval));
        rpm = (((double)(readings - prevReadings) * rotationalOffset / 360) * ((double)1000 * 60 / interval));
        if (!keepHistory)
        {
            prevReadings = readings;
        }
        prevTime = micros();
        return rpm;
    }
    void calibrate()
    {
        mpu6050.calcGyroOffsets(true);
    }
} mpu;