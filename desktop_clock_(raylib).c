/*
 * https://m.youtube.com/@my_asceza
 * https://t.me/my_asceza
 * https://vk.com/my_asceza
 * https://github.com/asceza/C
 */
#include "raylib.h"
#include <time.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGH 400
#define SECOND_ANGLE   2
#define MINUTE_ANGLE   4
#define HOUR_ANGLE     6


void draw_clock_field(Vector2 *c) {
    // желтый круг
    DrawCircle(SCREEN_WIDTH/2.0f, SCREEN_HEIGH/2.0f, 114, GOLD);

    //12 узких меток
    for (int a = 0; a < 360; a += 30) {
        DrawCircleSector(*c, 114, a-2, a + 2, 1, BLACK);
    }

    // 4 широких метки
    for (int a = 0; a < 360; a += 90) {
        DrawCircleSector(*c, 114, a-8, a + 8, 4, BLACK);
    }

    // черный круг
    DrawCircle(SCREEN_WIDTH/2.0f, SCREEN_HEIGH/2.0f, 108, BLACK);

    // статичные цифры на циферблате
    DrawText("12", SCREEN_WIDTH/2.0f - 8, 80, 20, GOLD);
    DrawText("3", SCREEN_WIDTH - 93, 190, 20, GOLD);
    DrawText("6", SCREEN_WIDTH/2.0f - 6, SCREEN_HEIGH - 96, 20, GOLD);
    DrawText("9", 84, 190, 20, GOLD);
}


void get_current_time_and_date (int *c_s, int *c_m, int *c_h, char *c_t, char *c_d, char *c_w_d) {
    struct tm *ptm = NULL; // указатель на структуру с нужными полями
    time_t t = time(NULL); // возвращает кол-во секунд, прошедших с начала эпохи 01.01.1970

    // возвращает указатель на структуру tm с локальным датой и временем
    // в качестве параметра указывается адрес переменной
    // с количеством секунд, прошедших с начала эпохи 01.01.1970
    ptm = localtime(&t);

    *c_s = ptm->tm_sec;
    *c_m = ptm->tm_min;
    *c_h = ptm->tm_hour;

    if (!ptm) { // если указатель пустой
        printf("error_localtime\n");
        exit(1);
    }

    // записывает строковое представление даты и времени из структуры типа tm
    // в соответствии со строкой формата в строку str
    // первый параметр - указатель на символьный массив (куда запишем)
    // второй - максимальный размер символьного массива (ошибка при переполнении!)
    // третий - формат
    // четвертый - указатель на структуру tm с представлением даты
    // функции возвращает кол-во записанных символов
    size_t err = strftime(c_t, 20, "%H:%M:%S", ptm); // записываем время
    strftime(c_d, 20, "%d.%m.%Y", ptm); // записываем дату
    strftime(c_w_d, 20, "%A", ptm); // записываем день недели

    if (!err) { // функции возвращает 0 в случае ошибки
        printf("error_strftime\n");
        exit(1);
    }
}


void translate_time_to_angles(int *s, int *m, int *h, float *s_a, float *m_a, float *h_a) {
    *s_a = 6 * (*s) - 90; // 360гр/60значений = 6,
    *m_a = (6 * (*m) - 90) + 6*(*s)/60; // + sec
    *h_a = (30 * (*h) - 90) + 6*(*m)/12 + 6*(*s)/3600; // + min + sec
}


void draw_time(char *c_t) {
    DrawText(c_t, 143, 185, 30, GOLD);
}


void draw_date(char *c_d) {
    DrawText(c_d, 130, 25, 30, GOLD);
}


void draw_week_day(int *c_w_d) {
    DrawText(c_w_d, 130, 340, 30, GOLD);
}


int main(void) {
    int cur_sec, cur_min, cur_hour; // текущее значение сек, мин, ч
    char cur_time[20] = ""; // текущее значение времени в строковом формате
    char cur_date[20] = ""; // текущее значение даты в строковом формате
    char cur_week_day[20] = ""; // текущее значение дня недели в строковом формате

    //угол поворота секундной, минутной и часовой стрелки
    float sec_angle, min_angle, hour_angle; //

    // инициализация
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGH, "CLOCK");
    Vector2 center = {(GetScreenWidth())/2.0f, GetScreenHeight()/2.0f};

    SetTargetFPS(10); // максимальное кол-во кадров в секунду

    // основной цикл
    while (!WindowShouldClose()) { // выполняем основной цикл пока окно не закрыто
        get_current_time_and_date(&cur_sec, &cur_min, &cur_hour, cur_time, cur_date, cur_week_day);
        translate_time_to_angles(&cur_sec, &cur_min, &cur_hour, &sec_angle, &min_angle, &hour_angle);

        // отрисовка
        BeginDrawing();
            ClearBackground(BLACK);
            draw_clock_field(&center);

            DrawCircleSector(center, 102, hour_angle - HOUR_ANGLE/2, hour_angle + HOUR_ANGLE/2, 2, DARKGREEN);
            DrawCircleSector(center, 102, min_angle - MINUTE_ANGLE/2, min_angle + MINUTE_ANGLE/2, 10, BLUE);
            DrawCircleSector(center, 102, sec_angle - SECOND_ANGLE/2, sec_angle + SECOND_ANGLE/2, 1, RED);

            DrawCircle(SCREEN_WIDTH/2.0f, SCREEN_HEIGH/2.0f, 65, BLACK); // поле для электронных часов
            draw_time(cur_time);
            draw_date(cur_date);
            draw_week_day(cur_week_day);
        EndDrawing();
    }
    // Деинициализация
    CloseWindow(); //закрыть окно и контекст OpenGL
    return 0;
}
