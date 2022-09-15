#include "Include.hpp"
#include <raylib.h>
#include "venom.hpp"

int main(void)
{
    InitWindow(800, 600, "Venom");
    srand(time(NULL));
    int seed = rand();
    Camera camera = {{5.0f, 5.0f, 5.0f}, {0.0f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, 45.0f, 0};
    Vector3 position = {0.0f, 0.0f, 0.0f};
    Model ball = LoadModelFromMesh(GenMeshSphere(0.1, 8, 8));
    Model sky = LoadModelFromMesh(GenMeshSphere(200, 8, 8));

    Image image;
    Image color;
    set_map(image, color, seed);
    Venom ven(image.data);
    Texture2D texture = LoadTextureFromImage(color);
    Mesh mesh = GenMeshHeightmap(image, (Vector3){100, 1, 100});
    Model model = LoadModelFromMesh(mesh);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    Model flat = LoadModelFromMesh(GenMeshPoly(10, 10000.0f));
    SetCameraMode(camera, CAMERA_THIRD_PERSON);
    SetTargetFPS(60);
    Shader shader = LoadShader(TextFormat("shaders/glsl%i/base_lighting.vs", GLSL_VERSION),
                               TextFormat("shaders/glsl%i/fog.fs", GLSL_VERSION));
    float fogDensity = 0.05f;
    int fogDensityLoc = GetShaderLocation(shader, "fogDensity");
    SetShaderValue(shader, fogDensityLoc, &fogDensity, SHADER_UNIFORM_FLOAT);

    int viewPos = GetShaderLocation(shader, "viewPos");

    ball.materials[0].shader = shader;
    flat.materials[0].shader = shader;
    model.materials[0].shader = shader;
    while (!WindowShouldClose()) {
        float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        SetShaderValue(shader, viewPos, cameraPos, SHADER_UNIFORM_VEC3);
        camera.target.x = ven.pos.x;
        camera.target.z = ven.pos.z;
        ven.move_ven(camera);
        UpdateCamera(&camera);
        BeginDrawing();
            ClearBackground(Color{0.1 * 255, 0.05 * 255, 0.05 * 255, 255});
            BeginMode3D(camera);
                BeginShaderMode(shader);
                DrawModel(model, Vector3{-50, -0.5, -50}, 1.0f, WHITE);
                DrawModel(sky, Vector3{0, 0, 0}, 1.0f, WHITE);
                DrawModel(flat, Vector3{-500, -1, -500}, 1.0f, BLACK);
                ven.draw_ven(ball, seed);
                EndShaderMode();
                // DrawGrid(100, 1.0);
            EndMode3D();
            DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
