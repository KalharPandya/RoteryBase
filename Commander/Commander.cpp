#define maxLines 100

class Line
{
public:
    int steps;
    int orignalSteps = 0;
    Direction speed;
    Direction modifiedSpeed;

    void set(Direction _speed, int _steps)
    {
        speed.fx = _speed.fx;
        speed.fy = _speed.fy;
        speed.fr = _speed.fr;
        steps = _steps;
        orignalSteps = _steps;
    }
    Direction getSpeed()
    {
        steps -= 1;
        double offset;
        if (steps > orignalSteps / 2)
        {
            //Incrementing
            offset = (double)(orignalSteps - steps) / (orignalSteps / 2);
        }
        else
        {
            offset = (double)(steps) / (orignalSteps / 2);
        }
        modifiedSpeed.fx = speed.fx * offset;
        modifiedSpeed.fy = speed.fy * offset;
        modifiedSpeed.fr = speed.fr * offset;
        return modifiedSpeed;
    }
};
long meterToPulse(double meter)
{
    return ((meter * 1000.0) / (0.5 * 3.14 * 48.0)) * 720.0;
}

long mps(int ms, int interval = 10)
{
    int pulses = meterToPulse(ms);
    return (pulses / (1000 / interval));
}
class TargetPoint
{
public:
    Direction point, rationalSpeed;

    int speed;
    double xFactor = 1, yFactor = 1, rFactor = 1;
    long total = 0;
    double maxPoint = 0;
    int steps = 0;
    TargetPoint() {}
    TargetPoint(Direction _point, int _speed)
    {
        set(_point, _speed);
    }
    void set(Direction _point, int _speed)
    {
        point.fx = _point.fx;
        point.fy = _point.fy;
        point.fr = _point.fr;
        speed = _speed;
        Serial.println("Converted");
        point.display();
        Serial.println("Speed = " + speed);
        computeSpeeds();
    }
    void computeSpeeds()
    {

        maxPoint = point.absMax();
        if (maxPoint == 0)
            return;
        Serial.print("Max =");
        Serial.println(maxPoint);
        xFactor = ((double)point.fx / maxPoint);
        yFactor = ((double)point.fy / maxPoint);
        rFactor = ((double)point.fr / maxPoint);

        rationalSpeed.fx = xFactor * speed;
        rationalSpeed.fy = yFactor * speed;
        rationalSpeed.fr = rFactor * speed;
        rationalSpeed.display();
        double rmax = rationalSpeed.absMax();
        if (rmax == 0)
            return;
        steps = maxPoint / rmax;
        Serial.println("Steps = " + String(steps));
    }
} lineProcessor;

class Commander
{
public:
    Line *allLines[maxLines];
    Direction empty;
    int lineIndex = -1;
    int feederIndex = -1;
    int lineCount = 0;
    bool available = false;
    Commander()
    {

        empty.fx = 0;
        empty.fy = 0;
        empty.fr = 0;
    }
    void addPoint(Direction target, int speed)
    {
        if (lineIndex >= maxLines - 1)
        {
            Serial.println("Commander Overflow");
            return;
        }

        available = true;
        lineIndex += 1;
        allLines[lineIndex] = new Line();

        lineProcessor.set(target, speed);

        allLines[lineIndex]->set(lineProcessor.rationalSpeed, lineProcessor.steps);
    }

    Direction next()
    {
        if (allLines[lineCount]->steps > 0)
        {
            // allLines[lineCount]->steps -= 1;
            return allLines[lineCount]->getSpeed();
        }
        if (lineCount < lineIndex)
        {
            lineCount += 1;
            return next();
        }
        available = false;
        return empty;
    }

} AutoCommander;