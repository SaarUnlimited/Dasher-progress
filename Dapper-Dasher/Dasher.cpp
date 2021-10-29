#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    int windowDimensions[2];
    windowDimensions[0] = 518;
    windowDimensions[1] = 400;


    //Initialize The Window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    //Acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};

    //nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    
    const int sizeOfNebulae{10};
    AnimData nebulae[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
        nebulae[i].pos.x = windowDimensions[0] + i * 325;
    }

    //Nebula X Velocity (pixels/second)
    int nebVel{-244};

    // alex variables
    Texture2D alex = LoadTexture("textures/alex.png");
    AnimData alexData;
    alexData.rec.width = alex.width / 6;
    alexData.rec.height = alex.height;
    alexData.rec.x = 0;
    alexData.rec.y = 0;
    alexData.pos.x = windowDimensions[0] / 2 - alexData.rec.width / 2;
    alexData.pos.y = windowDimensions[1] - alexData.rec.height;
    alexData.frame = 0;
    alexData.updateTime = 1.0 / 12.0;
    alexData.runningTime = 0.0;

    // Is The Rectangle in The Air?
    bool isInAir{};
    // Jump  velocity (pixels/s)/s
    const int jumpVel{-600};

    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //Delta Time (Time since last frame)
        const float dT{GetFrameTime()};
        //Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //Perform Ground Check
        if (alexData.pos.y >= windowDimensions[1] - alexData.rec.height)
        {
            // Rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is in the air
            velocity += gravity * dT;
            isInAir = true;
        }
        //Jump checking
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            //  Update each nebula Position
            nebulae[i].pos.x += nebVel * dT;
        }

        //Update alex Position
        alexData.pos.y += velocity * dT;

        //update alex's animation frame
        if (!isInAir)
        {
            //Update Running Time
            alexData.runningTime += dT;
            if (alexData.runningTime >= alexData.updateTime)
            {
                alexData.runningTime = 0.0;
                // Update Animation frame
                alexData.rec.x = alexData.frame * alexData.rec.width;
                alexData.frame++;
                if (alexData.frame > 5)
                {
                    alexData.frame = 0;
                }
            }
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            //Update nebula animation frame
            nebulae[i].runningTime += dT;
            if (nebulae[i].runningTime >= nebulae[i].updateTime)
            {
                nebulae[i].runningTime = 0.0;
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                if (nebulae[i].frame > 7)
                {
                    nebulae[i].frame = 0;
                }
            }
        }
        for (int i = 0; i < sizeOfNebulae; i++)
        {
             //Draw nebula
        DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        //Draw alex
        DrawTextureRec(alex, alexData.rec, alexData.pos, WHITE);

        //Stop Drawing
        EndDrawing();
    }
    UnloadTexture(alex);
    UnloadTexture(nebula);
    CloseWindow();
}