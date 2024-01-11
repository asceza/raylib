/*
 * https://m.youtube.com/@my_asceza
 * https://t.me/my_asceza
 * https://vk.com/my_asceza
 * https://github.com/asceza/C
 */


#include <stdlib.h>
#include "raylib.h"


#define SCREEN_WIDTH                         800
#define SCREEN_HIGH                          800
#define HWM                                  400 //half width marks
#define X_MIN                                -10
#define X_MAX                                 10
#define dX                                   0.1
#define MAX_SPLINE_POINTS     (int)((X_MAX - X_MIN)/dX)



void draw_axes(int *m) {
    Vector2 x_axis_start = {0, SCREEN_HIGH/2};
    Vector2 x_axis_end = {SCREEN_WIDTH, SCREEN_HIGH/2};
    Vector2 y_axis_start = {SCREEN_WIDTH/2, 0};
    Vector2 y_axis_end = {SCREEN_WIDTH/2, SCREEN_HIGH};
    DrawLineEx(x_axis_start, x_axis_end, 2, GRAY); //ось x
    DrawLineEx(y_axis_start, y_axis_end, 2, GRAY); //ось y

    //разметка 0..x
    for (int x = SCREEN_WIDTH/2; x < SCREEN_WIDTH; x+=(1*(*m))) {
    DrawLine(x, SCREEN_HIGH/2 - HWM, x, SCREEN_HIGH/2 + HWM, DARKGRAY);
    }

    //разметка 0..-x
    for (int x = SCREEN_WIDTH/2; x > 0; x-=(1*(*m))) {
    DrawLine(x, SCREEN_HIGH/2 - HWM, x, SCREEN_HIGH/2 + HWM, DARKGRAY);
    }

    //разметка 0..y
    for (int y = SCREEN_HIGH/2; y < SCREEN_HIGH; y+=(1*(*m))) {
    DrawLine(SCREEN_WIDTH/2 - HWM, y, SCREEN_WIDTH/2 + HWM, y, DARKGRAY);
    }

    //разметка 0..-y
    for (int y = SCREEN_HIGH/2; y > 0; y-=(1*(*m))) {
    DrawLine(SCREEN_WIDTH/2 - HWM, y, SCREEN_WIDTH/2 + HWM, y, DARKGRAY);
    }
}


void draw_func_a_by_points(int *m) {
    for (float i = X_MIN; i < X_MAX; ) {
        DrawCircle(i*(*m) + SCREEN_WIDTH/2, -(i*i*(*m)) + SCREEN_HIGH/2, 3, RED); // y = x*x
        i = i + dX;
    }
}


void draw_func_a_by_spline(int *m) {
        //Vector2 points[MAX_SPLINE_POINTS] = {0}; //с присваиванием значений эелементам компилятор крашится
        Vector2 points[MAX_SPLINE_POINTS];
        int p = 0;
        for (float i = X_MIN; i < X_MAX; ) {

            points[p].x = (i*(*m) + SCREEN_WIDTH/2);
            points[p].y = (-(i*i*(*m)) + SCREEN_HIGH/2);
            p++;
            i = i + dX;
            //Vector2 points[MAX_SPLINE_POINTS] = {{0, 0}, {1, 1}, {2, 4}, ..., {x, y(x)}};
        }

        //DrawSplineLinear(points, MAX_SPLINE_POINTS, 2, BLUE);
        //DrawSplineBasis(points, MAX_SPLINE_POINTS, 2, GREEN);
        DrawSplineCatmullRom(points, MAX_SPLINE_POINTS, 2, MAGENTA);
}


void draw_func_b_by_points(int *m) {
    for (float i = X_MIN; i < X_MAX; ) {
        DrawCircle(i*(*m) + SCREEN_WIDTH/2, -(i*i*i*(*m)) + SCREEN_HIGH/2, 3, CLITERAL (Color){250, 174, 20, 255});
        i = i + dX;
    }
}


void draw_func_b_by_spline(int *m) {
        //Vector2 points[MAX_SPLINE_POINTS] = {0}; //с присваиванием значений эелементам компилятор крашится
        Vector2 points[MAX_SPLINE_POINTS];
        int p = 0;
        for (float i = X_MIN; i < X_MAX; ) {

            points[p].x = (i*(*m) + SCREEN_WIDTH/2);
            points[p].y = (-(i*i*i*(*m)) + SCREEN_HIGH/2);
            p++;
            i = i + dX;

            //Vector2 points[MAX_SPLINE_POINTS] = {{0, 0}, {1, 1}, {2, 4}, ..., {x, y(x)}};
        }

        //DrawSplineLinear(points, MAX_SPLINE_POINTS, 2, BLUE);
        //DrawSplineBasis(points, MAX_SPLINE_POINTS, 2, GREEN);
        DrawSplineCatmullRom(points, MAX_SPLINE_POINTS, 2, CLITERAL (Color){250, 174, 20, 255});
        //DrawSplineBezierQuadratic(points, MAX_SPLINE_POINTS, 2, MAGENTA);
        //DrawSplineBezierCubic(points, MAX_SPLINE_POINTS, 2, GREEN);
        //printf("%d", sizeof(points)/sizeof(points[0]));
}


int main(void) {
    int mult = 400; //multiplier, множитель для пересчета масштаба
    int dm = 10;
    char mult_str[10]; // при короткой длине массива, программа закроется с ошибкой
    // инициализация
    InitWindow(SCREEN_WIDTH, SCREEN_HIGH, "Function rendering");

    SetTargetFPS(60); // максималльное кол-во кадров в секунду

    // основной цикл
    while (!WindowShouldClose()) {// выполняем основной цикл пока окно не закрыто
        // обновляем переменные

        // преобразует число типа int в строку
        //(число, указатель на символьный массив, система счисления)
        _itoa(mult, mult_str, 10);

        // Отрисовка
        BeginDrawing();
            ClearBackground(BLACK); //цвет фона
            draw_axes(&mult);
            draw_func_a_by_points(&mult);
            draw_func_a_by_spline(&mult);
            draw_func_b_by_points(&mult);
            draw_func_b_by_spline(&mult);
            DrawText("scale: ", 10, 10, 22, GRAY);
            DrawText(mult_str, 90, 10, 22, GRAY);

            if (GetMouseWheelMove() > 0) {
                mult += dm;
                if (mult >= 1000) mult = 1000;
            }

            if (GetMouseWheelMove() < 0) {
                mult-=dm;
                if (mult <= 10) mult = 10;
            }

        EndDrawing();
    }

    // деинициализация
    CloseWindow(); //закрыть окно и контекст OpenGL
    return 0;
}
