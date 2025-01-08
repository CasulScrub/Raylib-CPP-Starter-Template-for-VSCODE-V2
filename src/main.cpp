#include "raylib.h"
#include <stdlib.h>
#include <math.h>

#define MAX_BALLS 300
#define MIN_SPEED 2.0f
#define MAX_SPEED 6.0f

typedef struct {
    Vector2 position;
    Vector2 speed;
    float radius;
    Color color;
    bool active;
} Ball;

// Helper function to ensure minimum speed
float getRandomSpeed(float minSpeed, float maxSpeed) {
    float speed = GetRandomValue(-maxSpeed * 100, maxSpeed * 100) / 100.0f;
    if (fabs(speed) < minSpeed) {
        speed = (speed < 0) ? -minSpeed : minSpeed;
    }
    return speed;
}

int main(void) {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Bouncing Balls - Press SPACE to spawn");
    // Initialize ball array
    Ball balls[MAX_BALLS] = { 0 };
    int activeBalls = 0;

    // Initialize first ball
    balls[activeBalls].position = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    balls[activeBalls].speed = (Vector2){ 5.0f, 4.0f };
    balls[activeBalls].radius = 20;
    balls[activeBalls].color = MAROON;
    balls[activeBalls].active = true;
    activeBalls++;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        // Spawn new ball when spacebar is pressed
        if (IsKeyPressed(KEY_SPACE) && activeBalls < MAX_BALLS) {
            balls[activeBalls].position = (Vector2){ 
                GetRandomValue(20, screenWidth - 20),
                GetRandomValue(20, screenHeight - 20)
            };
            balls[activeBalls].speed = (Vector2){ 
                getRandomSpeed(MIN_SPEED, MAX_SPEED),
                getRandomSpeed(MIN_SPEED, MAX_SPEED)
            };
            balls[activeBalls].radius = GetRandomValue(10, 30);
            balls[activeBalls].color = (Color){ 
                GetRandomValue(50, 255),
                GetRandomValue(50, 255),
                GetRandomValue(50, 255),
                255
            };
            balls[activeBalls].active = true;
            activeBalls++;
        }

        // Update all active balls
        for (int i = 0; i < MAX_BALLS; i++) {
            if (!balls[i].active) continue;

            // Update ball position
            balls[i].position.x += balls[i].speed.x;
            balls[i].position.y += balls[i].speed.y;

            // Check walls collision
            if ((balls[i].position.x >= (screenWidth - balls[i].radius)) || 
                (balls[i].position.x <= balls[i].radius)) {
                balls[i].speed.x *= -1.0f;
                
                // Ensure minimum speed after collision
                if (fabs(balls[i].speed.x) < MIN_SPEED) {
                    balls[i].speed.x = (balls[i].speed.x < 0) ? -MIN_SPEED : MIN_SPEED;
                }
            }
            if ((balls[i].position.y >= (screenHeight - balls[i].radius)) || 
                (balls[i].position.y <= balls[i].radius)) {
                balls[i].speed.y *= -1.0f;
                
                // Ensure minimum speed after collision
                if (fabs(balls[i].speed.y) < MIN_SPEED) {
                    balls[i].speed.y = (balls[i].speed.y < 0) ? -MIN_SPEED : MIN_SPEED;
                }
            }
        }

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            // Draw all active balls
            for (int i = 0; i < MAX_BALLS; i++) {
                if (balls[i].active) {
                    DrawCircleV(balls[i].position, balls[i].radius, balls[i].color);
                }
            }
            
            // Draw UI
            DrawFPS(10, 10);
            DrawText(TextFormat("Balls: %d/%d", activeBalls, MAX_BALLS), 10, 30, 20, DARKGRAY);
            DrawText("Press SPACE to spawn new ball", 10, 50, 20, DARKGRAY);
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}