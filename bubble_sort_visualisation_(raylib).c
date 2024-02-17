/*
 * https://m.youtube.com/@my_asceza
 * https://t.me/my_asceza
 * https://vk.com/my_asceza
 * https://github.com/asceza/C
 */
#include "raylib.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define RADIUS 6           //радиус круга
#define SCREEN_WIDTH (900) //ширина экрана
#define SCREEN_HEIGH 400   //высота экрана
#define LENGTH 30          //длина массива
#define MAX_NUMBER 70      //максимальное число в массиве

int array[LENGTH] = {0};

void init_array(int *array) {
    srand(time(NULL)); //текущее время в качестве начального значения
    for (int i = 0; i < LENGTH; i++) {
        int r = rand()%MAX_NUMBER + 1; //случайное число 0..(MAX_NUMBER-1)
        array[i] = r;
    }
}


void draw_circles(int *x, int *y) {
    for (int i = 0; i < *x; i++) {
        DrawCircle(i * 2 * RADIUS + 30, (*y) * 2 * RADIUS,
                   RADIUS-1, CLITERAL(Color){200, i * 2, i * 3, 255});
    }
}


void draw_array(int *array) {
    int y = 1; //для посроковой отрисовки
    char dig_str[10]; //строка для вывода числового значения
    for (int i = 0; i < LENGTH; i++) {

        // преобразует число типа int в строку
        //(число, указатель на символьный массив, система счисления)
        _itoa(array[i], dig_str, 10);
        DrawText(dig_str, 6, y * 2 * RADIUS - 5, 10, GOLD);

        draw_circles(&array[i], &y);
        y++;
    }
}


void one_step_bubble_sort(int *array) {
    int j = 0, tmp = 0;
    for (int i = LENGTH - 1; i >= 1; --i) {
        for (j = 0; j < i; ++j) {
            if (array[j] < array[j + 1]) {
                    tmp = array[j + 1];
                    array[j + 1] = array[j];
                    array[j] = tmp;
                    return 0;
            }
        }
    }
}


int main(void) {
    // инициализация
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGH, "Visualisation of bubble sort");
    init_array(array);
    draw_array(array);

    SetTargetFPS(20); // максимальное кол-во кадров в секунду

    // основной цикл
    while (!WindowShouldClose()) { // выполняем основной цикл пока окно не закрыто

        // отрисовка
        BeginDrawing();
        ClearBackground(BLACK); //цвет фона
        one_step_bubble_sort(array);
        draw_array(array);
        EndDrawing();

    }
    // Деинициализация
    CloseWindow(); //закрыть окно и контекст OpenGL
    return 0;
}
