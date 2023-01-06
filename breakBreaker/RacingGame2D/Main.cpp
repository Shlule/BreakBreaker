#include "raylib.h"
#include"Ball.h"
#include"Paddle.h"
#include"Bricks.h"
#include <iostream>
#include <stdio.h>  
#include <math.h> 
#include <vector>
#include <string>


using namespace std;

//Editor Variable
void Update();
void Draw();
void DrawUi();
void Load();
void Start();

//Setup la taille de l'écran
int const screenWidth = 960;
int const screenHeight = 1080;


Ball ball = Ball(25, 25,{100,800});
Paddle paddle = Paddle(120, 25,{50, 850});
Bricks brick = Bricks(80, 30, { 0,0 });

float brickWidth;
float brickHeight;
vector<Bricks> bricks;


int collumnNb;
int rowsNb;


float collisionAABB(Rectangle a, Rectangle b) {
    int xMinA = a.x;
    int xMaxA = a.x + a.width;
    int xMinB = b.x;
    int xMaxB = b.x + b.width;
    int yMinA = a.y;
    int yMaxA = a.y + a.height;
    int yMinB = b.y;
    int yMaxB = b.y + b.height;
    Vector2 centerA = { (xMaxA - xMinA) / 2, (yMaxA - yMinA) / 2 };
    Vector2 centerB = { (xMaxB - xMinB) / 2, (yMaxB - yMinB) / 2 };
    Vector2 posCenterA = { xMaxA - centerA.x, yMaxA - centerA.y };
    Vector2 posCenterB = { xMaxB - centerB.x, yMaxB - centerB.y };

    // verrify if it collide
    if (!(xMinB > xMaxA || yMinB > yMaxA || xMaxB < xMinA || yMaxB < yMinA)) {
        //if it collide return were it collide on the x axis between the center of the two object
        // and normalize
        return (posCenterA.x - posCenterB.x) / (centerA.x+centerB.x);
    }
    
        
}


void createBricks(int collumnP, int rowsP, float brickheightP) {

    brickWidth = screenWidth / collumnP;
    brickHeight = brickheightP;
    rowsNb = rowsP;
    collumnNb = collumnP;

    for (int i = 0; i < rowsP; i++) {
        for (int j = 0; j < collumnP; j++) {
            Bricks brick = Bricks{ brickWidth-5, brickheightP -5 ,{brickWidth * j,brickheightP * i+brickHeight/2} };
            bricks.emplace_back(brick);
        }
    }
}
void drawBricks() {
    for each (Bricks brick in bricks)
    {
        brick.draw();
    }
}

void collision() {
    int collumn = floor(ball.getCenter().x / brickWidth);
    int rows = floor(ball.getCenter().y / brickHeight);
    int index = collumn + rows * collumnNb;
    
    if (index < bricks.size()) {
        if (!bricks[index].getIsDead()) {
            bricks[index].setIsDead(true);

            float previousBallX = ball.getCenter().x - ball.getSpeed().x;
            float previousBallY = ball.getCenter().y - ball.getSpeed().y;
            int previousTileCol = floor(previousBallX / brickWidth);
            int previousTileRow = floor(previousBallY / brickHeight);

            if (previousTileCol != collumn) {
                ball.reverseSpeed(1);
            }
            if (previousTileRow != rows) {
                ball.reverseSpeed(2);
            }
        }
    }
    
}

int main(int argc, char* argv[])
{

    //Créer un écran et on met les fps à 60
    string windowName = "GameWindow";
    InitWindow(screenWidth, screenHeight, windowName.c_str());

    //ToggleFullscreen();
    SetWindowPosition(10, 50);
    SetTargetFPS(60);

    Load();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        Update();
        // Draw
        Draw();       

    }

    CloseWindow();

    return 0;


}
void Start() {

}

void Load()
{
    ball.setSpeed({ -5,-5 });
    createBricks(5,4,30.0);
    

}

void Update()
{
    //Ball wall collision
    if (ball.getPos().x < 0) {
        ball.reverseSpeed(1);
   }
    if (ball.getPos().y < 0 + ball.getHeight()) {
        ball.reverseSpeed(2);
    }
    if (ball.getPos().x > screenWidth - ball.getWidth()) {
        ball.reverseSpeed(1);
    }
    if (ball.getPos().y > screenHeight) {
        ball.reverseSpeed(2);
    }

    // paddle input
    if (IsKeyDown(KEY_D)) {
        paddle.setPos({ paddle.getPos().x + 5, paddle.getPos().y });
        
    }
    if (IsKeyDown(KEY_A)) {
        paddle.setPos({ paddle.getPos().x - 5, paddle.getPos().y });
    }

    // ball stop
    if (IsKeyDown(KEY_SPACE)) {
        ball.setSpeed({0,0});

    }

    //collision between ball ans paddle
    if (collisionAABB(ball.getCollisionBox(), paddle.getCollisionBox()) >= -1 &&
        collisionAABB(ball.getCollisionBox(), paddle.getCollisionBox()) <= 1) {

        
        float ratioAngle = collisionAABB(ball.getCollisionBox(), paddle.getCollisionBox());
        ball.setSpeed({10 * ratioAngle,-(ball.getSpeed().y)});
   }



    ball.update();
    paddle.update();
    collision();
}

void Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    
    paddle.draw();
    drawBricks();
    ball.draw();
    

    DrawUi();
    EndDrawing();
}

void DrawUi()
{

}



