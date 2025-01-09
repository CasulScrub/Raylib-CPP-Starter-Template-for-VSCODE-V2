#include "raylib.h"
#include <stdlib.h>
#include <math.h>

#define MAX_BALLS 100
#define MIN_SPEED 2.0f
#define MAX_SPEED 6.0f

typedef struct {
    Vector2 position;
    Vector2 speed;
    float radius;
    Color color;
    float mass;  // Added mass property
    bool active;
} Ball;

float getRandomSpeed(float minSpeed, float maxSpeed) {
    float speed = GetRandomValue(-maxSpeed * 100, maxSpeed * 100) / 100.0f;
    if (fabs(speed) < minSpeed) {
        speed = (speed < 0) ? -minSpeed : minSpeed;
    }
    return speed;
}

// Function to handle collision between two balls
void resolveCollision(Ball *b1, Ball *b2) {
    // Calculate distance between balls
    Vector2 delta = { b2->position.x - b1->position.x, b2->position.y - b1->position.y };
    float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
    
    // Check if balls are overlapping
    if (distance < b1->radius + b2->radius) {
        // Normal vector of collision
        Vector2 normal = { delta.x / distance, delta.y / distance };
        
        // Relative velocity
        Vector2 relativeVel = {
            b2->speed.x - b1->speed.x,
            b2->speed.y - b1->speed.y
        };
        
        // Relative velocity along normal
        float velAlongNormal = relativeVel.x * normal.x + relativeVel.y * normal.y;
        
        // Don't resolve if objects are moving apart
        if (velAlongNormal > 0) return;
        
        // Coefficient of restitution (bounciness)
        float restitution = 0.8f;
        
        // Calculate impulse scalar
        float impulseScalar = -(1 + restitution) * velAlongNormal;
        impulseScalar /= 1/b1->mass + 1/b2->mass;
        
        // Apply impulse
        Vector2 impulse = { impulseScalar * normal.x, impulseScalar * normal.y };
        
        b1->speed.x -= impulse.x / b1->mass;
        b1->speed.y -= impulse.y / b1->mass;
        b2->speed.x += impulse.x / b2->mass;
        b2->speed.y += impulse.y / b2->mass;
        
        // Separate balls to prevent sticking (position correction)
        float overlap = (b1->radius + b2->radius - distance) * 0.5f;
        Vector2 correction = {
            normal.x * overlap,
            normal.y * overlap
        };
        
        b1->position.x -= correction.x;
        b1->position.y -= correction.y;
        b2->position.x += correction.x;
        b2->position.y += correction.y;
    }
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Bouncing Balls - Press SPACE to spawn");

    Ball balls[MAX_BALLS] = { 0 };
    int activeBalls = 0;

    // Initialize first ball
    balls[activeBalls].position = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    balls[activeBalls].speed = (Vector2){ 5.0f, 4.0f };
    balls[activeBalls].radius = 20;
    balls[activeBalls].color = MAROON;
    balls[activeBalls].mass = 1.0f;  // Set initial mass
    balls[activeBalls].active = true;
    activeBalls++;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
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
            balls[activeBalls].mass = balls[activeBalls].radius / 10.0f;  // Mass proportional to size
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

            // Update position
            balls[i].position.x += balls[i].speed.x;
            balls[i].position.y += balls[i].speed.y;

            // Wall collisions
            if ((balls[i].position.x >= (screenWidth - balls[i].radius)) || 
                (balls[i].position.x <= balls[i].radius)) {
                balls[i].speed.x *= -1.0f;
                if (fabs(balls[i].speed.x) < MIN_SPEED) {
                    balls[i].speed.x = (balls[i].speed.x < 0) ? -MIN_SPEED : MIN_SPEED;
                }
            }
            if ((balls[i].position.y >= (screenHeight - balls[i].radius)) || 
                (balls[i].position.y <= balls[i].radius)) {
                balls[i].speed.y *= -1.0f;
                if (fabs(balls[i].speed.y) < MIN_SPEED) {
                    balls[i].speed.y = (balls[i].speed.y < 0) ? -MIN_SPEED : MIN_SPEED;
                }
            }

            // Check collisions with other balls
            for (int j = i + 1; j < MAX_BALLS; j++) {
                if (balls[j].active) {
                    resolveCollision(&balls[i], &balls[j]);
                }
            }
        }

        BeginDrawing();
            ClearBackground(BLACK);
            
            // Draw balls
            for (int i = 0; i < MAX_BALLS; i++) {
                if (balls[i].active) {
                    DrawCircleV(balls[i].position, balls[i].radius, balls[i].color);
                }
            }
            
            DrawFPS(10, 10);
            DrawText(TextFormat("Balls: %d/%d", activeBalls, MAX_BALLS), 10, 30, 20, RAYWHITE);
            DrawText("Press SPACE to spawn new ball", 10, 50, 20, RAYWHITE);
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}