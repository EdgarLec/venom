#include <raylib.h>
#include <math.h>

Vector3 rotate(Vector3 center, Vector3 rt, float angle)
{
    float p_angle = angle * (PI / 180);
    float s = sin(p_angle);
    float c = cos(p_angle);
    float xnew;
    float ynew;

    rt.x -= center.x;
    rt.z -= center.z;
    xnew = rt.x * c - rt.z * s;
    ynew = rt.x * s + rt.z * c;
    rt.x = xnew + center.x;
    rt.z = ynew + center.z;
    return rt;
}

float distance(Vector3 pos1, Vector3 pos2)
{
    return (abs(pos1.x - pos2.x) + abs(pos1.y - pos2.y) + abs(pos1.z - pos2.z)) / 3.0;
}



float distance_2d(Vector3 pos1, Vector3 pos2)
{
    return (abs(pos1.x - pos2.x) + abs(pos1.z - pos2.z)) / 2.0;
}