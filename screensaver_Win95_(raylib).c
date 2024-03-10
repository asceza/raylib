#include "raylib.h"
#include <stdint.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define RADIUS 40 //радиус шара
#define NUMBER_OF_BALLS 24 //количество шаров


typedef struct ball{
    Vector2 position; //структура Vector2, 2 переменные типа float (координаты шара - x,y)
    Vector2 delta; //структура Vector2, 2 переменные типа float (смешение шара - dx, dy)
} ball_t; //имя нового типа данных

ball_t balls[NUMBER_OF_BALLS] = {0}; //массив структур

uint8_t coord_shift = 10;

void init(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Screensaver");

    for (int i = 0; i < NUMBER_OF_BALLS; i++) {
        balls[i].position.x = rand()%(SCREEN_WIDTH - RADIUS*2) + RADIUS;
        balls[i].position.y = rand()%(SCREEN_HEIGHT - RADIUS*2) + RADIUS;
        balls[i].delta.x = 1.92 + (i/10.0);
        balls[i].delta.y = 1.27 + (i/10.0);
    }
}


void calculate_position(void) {
    for (int i = 0; i < NUMBER_OF_BALLS; i++) {
    balls[i].position.x += balls[i].delta.x;
    balls[i].position.y += balls[i].delta.y;
    }
}


void check_borders_collision(void) {
    for (int i = 0; i < NUMBER_OF_BALLS; i++) {
        if ((balls[i].position.x >= (GetScreenWidth() - RADIUS)) || (balls[i].position.x <= 0 + RADIUS)) balls[i].delta.x *= -1.0f;
        if ((balls[i].position.y >= (GetScreenHeight() - RADIUS)) || (balls[i].position.y <= 0 + RADIUS)) balls[i].delta.y *= -1.0f;
    }
}


void draw_balls(void) {
    for (int i = 0; i < NUMBER_OF_BALLS; i++) {
        //DrawCircleV(balls[i].position, RADIUS, CLITERAL(Color){255 - i * 10, i * 10, i, 255});
        DrawCircleGradient(balls[i].position.x, balls[i].position.y, RADIUS, CLITERAL(Color){255, 221, 31, 255}, CLITERAL(Color){80, 0, 0, 0});
    }
}


void draw_lines_1(void){
    for (int i = 0; i < NUMBER_OF_BALLS; i+=2) {
        DrawLine(balls[i].position.x, balls[i].position.y, balls[i+1].position.x, balls[i+1].position.y, CLITERAL(Color){i, i * 10, 255 - i * 10, 255});
    }
}


void draw_lines_2(void){
    for (int i = 0; i < NUMBER_OF_BALLS; i+=1) {
        //DrawLine(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, balls[i].position.x, balls[i].position.y, CLITERAL(Color){i, i * 8, 128 - i * 10, 255});
        DrawLine(balls[0].position.x, balls[0].position.y, balls[i].position.x, balls[i].position.y, CLITERAL(Color){i, i * 8, 128 - i * 10, 255});
    }
}


void draw_lines_3(void){
    int color = 10;
    for (int i = 0; i < NUMBER_OF_BALLS; i+=4) {
        DrawLine(balls[i].position.x, balls[i].position.y, balls[i+1].position.x, balls[i+1].position.y, CLITERAL(Color){122 + color, 122, 255, 255});
        DrawLine(balls[i].position.x, balls[i].position.y, balls[i+1].position.x + coord_shift, balls[i+1].position.y - coord_shift, CLITERAL(Color){122 + color, 122 - color, 255, 205});
        DrawLine(balls[i].position.x, balls[i].position.y, balls[i+1].position.x + coord_shift * 2, balls[i+1].position.y - coord_shift * 2, CLITERAL(Color){122 + color, 122 - color * 2, 255, 155});
        DrawLine(balls[i].position.x, balls[i].position.y, balls[i+1].position.x + coord_shift * 3, balls[i+1].position.y - coord_shift * 3, CLITERAL(Color){122 + color, 122 - color * 3, 255, 105});
        DrawLine(balls[i].position.x, balls[i].position.y, balls[i+3].position.x + coord_shift, balls[i+3].position.y - coord_shift, CLITERAL(Color){122 + color, 122 - color, 255, 205});
        DrawLine(balls[i].position.x, balls[i].position.y, balls[i+3].position.x + coord_shift * 2, balls[i+3].position.y - coord_shift * 2, CLITERAL(Color){122 + color, 122 - color * 2, 255, 155});
        DrawLine(balls[i].position.x, balls[i].position.y, balls[i+3].position.x + coord_shift * 3, balls[i+3].position.y - coord_shift * 3, CLITERAL(Color){122 + color, 122 - color * 3, 255, 105});

        DrawLine(balls[i+1].position.x, balls[i+1].position.y, balls[i+2].position.x, balls[i+2].position.y, CLITERAL(Color){122, 122 + color, 255, 255});
        DrawLine(balls[i+1].position.x + coord_shift, balls[i+1].position.y - coord_shift, balls[i+2].position.x, balls[i+2].position.y, CLITERAL(Color){122 - color, 122 + color, 255, 205});
        DrawLine(balls[i+1].position.x + coord_shift * 2, balls[i+1].position.y - coord_shift * 2, balls[i+2].position.x, balls[i+2].position.y, CLITERAL(Color){122 - color * 2, 122 + color, 255, 155});
        DrawLine(balls[i+1].position.x + coord_shift * 3, balls[i+1].position.y - coord_shift * 3, balls[i+2].position.x, balls[i+2].position.y, CLITERAL(Color){122 - color * 3, 122 + color, 255, 105});

        DrawLine(balls[i+3].position.x + coord_shift, balls[i+3].position.y - coord_shift, balls[i+2].position.x, balls[i+2].position.y, CLITERAL(Color){122 - color, 122 + color, 255, 205});
        DrawLine(balls[i+3].position.x + coord_shift * 2, balls[i+3].position.y - coord_shift * 2, balls[i+2].position.x, balls[i+2].position.y, CLITERAL(Color){122 - color * 2, 122 + color, 255, 155});
        DrawLine(balls[i+3].position.x + coord_shift * 3, balls[i+3].position.y - coord_shift * 3, balls[i+2].position.x, balls[i+2].position.y, CLITERAL(Color){122 - color * 3, 122 + color, 255, 105});
        DrawLine(balls[i+2].position.x, balls[i+2].position.y, balls[i+3].position.x, balls[i+3].position.y, CLITERAL(Color){122, 255, 122 + color, 255});

        DrawLine(balls[i+3].position.x, balls[i+3].position.y, balls[i].position.x, balls[i].position.y, CLITERAL(Color){122, 122 + color, 255, 255});
        color += 20;
    }
}


int main(void) {
    init(); //инициализация
    SetTargetFPS(60);
    while (!WindowShouldClose()) {

        calculate_position(); //пересчет новой позиции шаров
        check_borders_collision(); //проверка столкновения с границей окна

        BeginDrawing();
            ClearBackground(BLACK); //очистка экрана
            draw_balls();//отрисовка шаров в новом месте
            draw_lines_3();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
