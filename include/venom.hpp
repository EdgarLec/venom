#ifndef PLAYER_H
    #define PLAYER_H
    #include <utility>
    #include "raylib.h"
    #include "Include.hpp"
    #include <math.h>
class Venom
{
private:
    Model models;
    Mesh mesh;
    Texture2D texture;
public:
    float time;
    Vector3 pos;
    Vector3 *pos_feet;
    Venom(void *data);
    ~Venom();
    void Draw_leg(Vector3 pos, Model ball, int seed);
    void beg_leg(Vector3 pos, Model ball, int seed);
    void move_ven(Camera camera);
    void draw_ven(Model ball, int seed);
};

#endif
