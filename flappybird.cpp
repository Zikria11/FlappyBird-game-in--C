#include "raylib.h"
#include <deque>

struct Pipe {
    float x;
    float gapY;
    float gapHeight;
    bool passed = false;
    Rectangle topRect;
    Rectangle bottomRect;

    Pipe(float screenWidth, float screenHeight) {
        x = screenWidth + 100.0f;
        gapHeight = 150.0f;
        gapY = GetRandomValue(gapHeight, screenHeight - gapHeight);
        topRect = { x, 0, 100, gapY - gapHeight / 2 };
        bottomRect = { x, gapY + gapHeight / 2, 100, screenHeight - (gapY + gapHeight / 2) };
    }

    void Update(float speed) {
        x -= speed * GetFrameTime();
        topRect.x = x;
        bottomRect.x = x;
    }

    bool Offscreen() {
        return x < -100;
    }

    bool Hits(float birdX, float birdY, float birdRadius) {
        Rectangle birdRect = { birdX - birdRadius, birdY - birdRadius, birdRadius * 2, birdRadius * 2 };
        return CheckCollisionRecs(birdRect, topRect) || CheckCollisionRecs(birdRect, bottomRect);
    }

    bool Passed(float birdX) {
        if (!passed && birdX > x + 100) {
            passed = true;
            return true;
        }
        return false;
    }
};

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Flappy Bird");
    SetTargetFPS(60);

    Texture2D birdTex = LoadTexture("bird.png");
    Texture2D pipeTopTex = LoadTexture("pipe_top.png");
    Texture2D pipeBottomTex = LoadTexture("pipe_bottom.png");

    float birdX = 200.0f;
    float birdY = screenHeight / 2.0f;
    float birdVelocity = 0.0f;
    const float gravity = 500.0f;
    const float flapStrength = -200.0f;
    const float birdRadius = 17.0f;
    const float birdWidth = 34.0f;
    const float birdHeight = 24.0f;

    std::deque<Pipe> pipes;
    float pipeSpeed = 200.0f;
    float pipeSpawnTimer = 0.0f;
    const float pipeSpawnInterval = 2.5f;

    int score = 0;
    bool gameOver = false;

    pipes.push_back(Pipe(screenWidth, screenHeight));

    while (!WindowShouldClose()) {
        if (!gameOver) {
            if (IsKeyPressed(KEY_SPACE)) {
                birdVelocity = flapStrength;
            }
            birdVelocity += gravity * GetFrameTime();
            birdY += birdVelocity * GetFrameTime();

            pipeSpawnTimer += GetFrameTime();
            if (pipeSpawnTimer >= pipeSpawnInterval) {
                pipes.push_back(Pipe(screenWidth, screenHeight));
                pipeSpawnTimer = 0.0f;
            }

            for (auto& pipe : pipes) {
                pipe.Update(pipeSpeed);
                if (pipe.Hits(birdX, birdY, birdRadius)) {
                    gameOver = true;
                }
                if (pipe.Passed(birdX)) {
                    score++;
                }
            }

            while (!pipes.empty() && pipes.front().Offscreen()) {
                pipes.pop_front();
            }

            if (birdY < 0 || birdY > screenHeight) {
                gameOver = true;
            }
        }
        else {
            if (IsKeyPressed(KEY_SPACE)) {
                birdX = 200.0f;
                birdY = screenHeight / 2.0f;
                birdVelocity = 0.0f;
                pipes.clear();
                pipes.push_back(Pipe(screenWidth, screenHeight));
                score = 0;
                gameOver = false;
                pipeSpawnTimer = 0.0f;
            }
        }

        BeginDrawing();
        ClearBackground({ 135, 206, 235, 255 });

        for (const auto& pipe : pipes) {
            if (pipeTopTex.id > 0) {
                DrawTexture(pipeTopTex, (int)pipe.topRect.x, (int)(pipe.topRect.y + pipe.topRect.height - pipeTopTex.height), WHITE);
            }
            else {
                DrawRectangleRec(pipe.topRect, GREEN);
            }
            if (pipeBottomTex.id > 0) {
                DrawTexture(pipeBottomTex, (int)pipe.bottomRect.x, (int)pipe.bottomRect.y, WHITE);
            }
            else {
                DrawRectangleRec(pipe.bottomRect, GREEN);
            }
        }

        if (birdTex.id > 0) {
            DrawTexturePro(birdTex,
                { 0, 0, (float)birdTex.width, (float)birdTex.height },
                { birdX - birdWidth / 2, birdY - birdHeight / 2, birdWidth, birdHeight },
                { birdWidth / 2, birdHeight / 2 }, 0.0f, WHITE);
        }
        else {
            DrawRectangle((int)(birdX - birdWidth / 2), (int)(birdY - birdHeight / 2), (int)birdWidth, (int)birdHeight, YELLOW);
        }

        DrawText(TextFormat("Score: %d", score), 10, 10, 30, WHITE);

        if (gameOver) {
            DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2 - 20, 40, RED);
            DrawText("Press SPACE to restart", screenWidth / 2 - 150, screenHeight / 2 + 30, 20, WHITE);
        }

        EndDrawing();
    }

    UnloadTexture(birdTex);
    UnloadTexture(pipeTopTex);
    UnloadTexture(pipeBottomTex);
    CloseWindow();
    return 0;
}
