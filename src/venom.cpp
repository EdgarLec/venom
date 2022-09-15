#include "Include.hpp"
#include <math.h>
#include "venom.hpp"
#define BALL_NB 150
#define FLOAT_NB 150.0f
#define INTENSITY 30.0f
#include <cfloat>

Venom::Venom(void *data)
{
    pos_feet = (Vector3 *)malloc(5000 * sizeof(Vector3));
    unsigned char *tmp = (unsigned char *)data;
    for (int i = 0; i < 5000; i++) {
        float x = GetRandomValue(0, 100) / 100.0;
        float y = GetRandomValue(0, 100) / 100.0;
        pos_feet[i].x = x + i % 100 - 50;
        pos_feet[i].z = (y + i / 100 - 50) * 2 + 50;
        pos_feet[i].y = tmp[int((i / 100 + y) * 4 * 2) * 400 + int((i % 100 + x) * 4)] / 255.0 - 0.5;
    }
    models = LoadModelFromMesh(mesh);
    pos = {2.5, 0.75, 2.5};

    Image checked = GenImageChecked(2, 2, 1, 1, RED, BLUE);
    texture = LoadTextureFromImage(checked);
    UnloadImage(checked);
    models.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
}


Venom::~Venom()
{
    UnloadTexture(this->texture);
}

void Venom::Draw_leg(Vector3 leg, Model ball, int seed)
{
    Vector3 vec = {pos.x - leg.x, 0, pos.z - leg.z};
    Vector3 noise;
    Vector3 tmp;
    float dis = distance(pos, leg);
    vec.x /= FLOAT_NB;
    vec.z /= FLOAT_NB;
    for (int i = 0; i < BALL_NB; i++) {
        tmp = {pos.x - vec.x * i, sinf((i / FLOAT_NB * PI * 4 + PI) / 5.0), pos.z - vec.z * i};
        if ((i / FLOAT_NB * PI * 4 + PI) / 5.0 > PI / 2.0) {
            tmp.y = tmp.y * (tmp.y * dis + 0.869088) / (dis + 1);
            tmp.y = tmp.y / 0.869088 * (0.869088 - leg.y) + leg.y;
        } else
            tmp.y = (tmp.y * dis + 0.869088) / (dis + 1);
        for (int j = 0; j < 5; j++) {
            noise = tmp;
            noise.x += ValueNoise_2D(seed * j, i / (FLOAT_NB / 12.5), seed, 1) * ((i / FLOAT_NB + 0.5) / 2.0);
            noise.z += ValueNoise_2D(seed * j * 2, i / (FLOAT_NB / 12.5), seed, 1) * ((i / FLOAT_NB + 0.5) / 2.0);
            if (noise.y < 0)
                noise.y = 0;
            float red = i > BALL_NB / (0.8 + dis) ? i : BALL_NB / (0.8 + dis);
            red = ((red - i) / red);
            if (i > BALL_NB / 2.0 || i % 2 == 0)
                DrawModel(ball, noise, ((BALL_NB - i) / FLOAT_NB + 0.1) * float(1.5 - j / 10.0), Color{red * 100.0, 0, 0, 255});
        }
    }
}

void Venom::beg_leg(Vector3 leg, Model ball, int seed)
{
    Vector3 vec = {pos.x - leg.x, 0, pos.z - leg.z};
    Vector3 noise;
    Vector3 tmp;
    float dis = distance_2d(pos, leg);
    float nb = BALL_NB * (1 - (distance(pos, leg) - 1.2) / 0.3);
    vec.x /= FLOAT_NB;
    vec.z /= FLOAT_NB;
    for (int i = 0; i < nb; i++) {
        tmp = {pos.x - vec.x * i, sinf((i / FLOAT_NB * PI * 4 + PI) / 5.0), pos.z - vec.z * i};
        if ((i / FLOAT_NB * PI * 4 + PI) / 5.0 > PI / 2.0) {
            tmp.y = tmp.y * (tmp.y * dis + 0.869088) / (dis + 1);
            tmp.y = tmp.y / 0.869088 * (0.869088 - leg.y) + leg.y;
        } else
            tmp.y = (tmp.y * dis + 0.869088) / (dis + 1);
        for (int j = 0; j < 5; j++) {
            noise = tmp;
            noise.x += ValueNoise_2D(seed * j, i / (FLOAT_NB / 12.5), seed, 1) * ((i / FLOAT_NB + 0.5) / 2.0);
            noise.z += ValueNoise_2D(seed * j * 2, i / (FLOAT_NB / 12.5), seed, 1) * ((i / FLOAT_NB + 0.5) / 2.0);
            if (noise.y < 0)
                noise.y = 0;
            float red = i > BALL_NB / (0.8 + dis) ? i : BALL_NB / (0.8 + dis);
            red = ((red - i) / red);
            if (i > BALL_NB / 2.0 || i % 2 == 0)
                DrawModel(ball, noise, ((BALL_NB - i) / FLOAT_NB + 0.1) * float(1.5 - j / 10.0), Color{red * 100.0, 0, 0, 255});
        }
    }
}

void Venom::move_ven(Camera camera)
{
    int tmp = 0;
    float norm = 0;
    Vector3 vec;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D) || IsKeyDown(KEY_A)) {
        vec = {camera.position.x - camera.target.x, 0, camera.position.z - camera.target.z};
        norm = sqrt(pow(vec.x, 2) + pow(vec.z, 2));
    }
    if (IsKeyDown(KEY_W)) {
        pos.x -= vec.x / norm / 20.0;
        pos.z -= vec.z / norm / 20.0;
        tmp = 1;
    }
    if (IsKeyDown(KEY_S)) {
        pos.x += vec.x / norm / 20.0;
        pos.z += vec.z / norm / 20.0;
        tmp = 1;
    }
    if (IsKeyDown(KEY_D)) {
        pos.x += vec.z / norm / 20.0;
        pos.z -= vec.x / norm / 20.0;
        tmp = 1;
    }
    if (IsKeyDown(KEY_A)) {
        pos.x -= vec.z / norm / 20.0;
        pos.z += vec.x / norm / 20.0;
        tmp = 1;
    }
}

void Venom::draw_ven(Model ball, int seed)
{
    for (int i = 0; i < 5000; i++) {
        time = GetTime();
        // DrawModel(ball, pos_feet[i], 1, GREEN);
        if (distance(pos, pos_feet[i]) < 1.2)
            Draw_leg(pos_feet[i], ball, seed + i * 1000);
        else if (distance(pos, pos_feet[i]) < 1.5)
        // DrawModel(ball, pos_feet[i], 1, GREEN);
            beg_leg(pos_feet[i], ball, seed + i * 1000);
    }
}