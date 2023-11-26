#include <cmath>

const double PI = (22.0 / 7.0);

float angleInRadians(float x, float y)
{
    return atan2(y, x);
}

int angleInDegrees(float x, float y)
{
    return angleInRadians(x, y) * 180 / PI;
}

float magnitude(float x, float y)
{
    return sqrt(x * x + y * y);
}