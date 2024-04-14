#include "raylib.h"
#include <stdint.h>
#include <stdlib.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 450
#define FONT_SIZE 16

//---------buttons-------------------------------------------------------------------------
typedef struct {
    Rectangle rec; //координаты кнопки
    float r; //скругление углов
    uint8_t cR, cG, cB, cA; //компоненты цвета
    Vector2 text_pos; //координаты позиции текста
    char button_name[30]; //текст на кнопке
    float half_text_width; //половина ширины надписи на кнопке
    _Bool pressed; //статус нажатия на кнопку
} button_t;

button_t button_1, button_2, button_3;
uint8_t which_button_is_pressed = 0; //какая кнопка нажата?
//---------buttons-------------------------------------------------------------------------

//---------sliders-------------------------------------------------------------------------
typedef struct {
    Rectangle rec; //координаты слайдера
    float full_width; //полная ширина слайдера
    float r; //скругление углов
    uint8_t cR, cG, cB, cA; //компоненты цвета
    Vector2 text_pos; //координаты позиции текста
    char slider_text[3]; //текст около слайдера
} slider_t;

slider_t slider_1, slider_2, slider_3, slider_3;
//---------sliders-------------------------------------------------------------------------

//---------checkboxes----------------------------------------------------------------------
typedef struct {
    Rectangle rec; //координаты чекбокса
    float r; //скругление углов
    uint8_t cR, cG, cB, cA; //компоненты цвета
    Vector2 text_pos; //координаты позиции текста
    char checkbox_name[30]; //текст около чекбокса
    _Bool select; //статус выбора чекбокса
} checkbox_t;

checkbox_t checkbox_1, checkbox_2, checkbox_3;
//---------checkboxes----------------------------------------------------------------------


Font current_font;
Vector2 mouse;
uint8_t circleR, circleG, circleB; //компоненты цвета круга
uint8_t circleR_2, circleG_2, circleB_2; //компоненты цвета прямоугольника

float rect_rounded = 0.0; //скругление углов прямоугольника


void init(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Colors");
    current_font = LoadFont("C:/Windows/Fonts/unispace bd.ttf"); //загрузка шрифта

//---------button_1------------------------------------------------------------------------
    strcpy(button_1.button_name, "But"); //надпись на кнопке
    button_1.rec.x = 30; //координата левого верхнего угла
    button_1.rec.y = 30; //координата левого верхнего угла
    button_1.rec.width = (MeasureTextEx(current_font, button_1.button_name, FONT_SIZE, 0).x < 170) ? 180: 240; //ширина
    button_1.rec.height = 40; //высота
    button_1.r = 0.3; //скругление углов
    button_1.cR = 26; //компонент Red
    button_1.cG = 188; //компонент Green
    button_1.cB = 156; //компонент Blue
    button_1.cA = 255; //компонент Alpha
    button_1.half_text_width = MeasureTextEx(current_font, button_1.button_name, FONT_SIZE, 0).x/2; //половина ширины надписи на кнопке
    button_1.text_pos.x = (button_1.rec.x) + (button_1.rec.width/2.0) - button_1.half_text_width; //координата позиции текста
    button_1.text_pos.y = button_1.rec.y + 13; //координата позиции текста
    button_1.pressed = 0; //статус нажатия на кнопку
//---------button_1------------------------------------------------------------------------

//---------button_2------------------------------------------------------------------------
    strcpy(button_2.button_name, "Button 2");
    button_2.rec = (Rectangle){30, 80, (MeasureTextEx(current_font, button_2.button_name, FONT_SIZE, 0).x < 170) ? 180: 240, 40};
    button_2.r = 0.3;
    button_2.cR = 241;
    button_2.cG = 196;
    button_2.cB = 15;
    button_2.cA = 255;
    button_2.half_text_width = MeasureTextEx(current_font, button_2.button_name, FONT_SIZE, 0).x/2;
    button_2.text_pos.x = (button_2.rec.x) + (button_2.rec.width/2.0) - button_2.half_text_width; //позиция текста
    button_2.text_pos.y = button_2.rec.y + 13;
    button_2.pressed = 0;
//---------button_2------------------------------------------------------------------------

//---------button_3------------------------------------------------------------------------
    strcpy(button_3.button_name, "Other Long Text Button 3");
    button_3.rec = (Rectangle){30, 130, (MeasureTextEx(current_font, button_3.button_name, FONT_SIZE, 0).x < 170) ? 180: 240, 40};
    button_3.r = 0.3;
    button_3.cR = 231;
    button_3.cG = 76;
    button_3.cB = 60;
    button_3.cA = 255;
    button_3.half_text_width = MeasureTextEx(current_font, button_3.button_name, FONT_SIZE, 0).x/2;
    button_3.text_pos.x = (button_3.rec.x) + (button_3.rec.width/2.0) - button_3.half_text_width; //позиция текста
    button_3.text_pos.y = button_3.rec.y + 13;
    button_3.pressed = 0;
//---------button_3------------------------------------------------------------------------

//---------slider_1------------------------------------------------------------------------
    slider_1.rec.x = 30;
    slider_1.rec.y = 250;
    slider_1.rec.width = 150;
    slider_1.full_width = 300;
    slider_1.rec.height = 5;
    slider_1.r = 1.0;
    slider_1.cR = 255;
    slider_1.cG = 0;
    slider_1.cB = 0;
    slider_1.cA = 255;
    strcpy(slider_1.slider_text, "127");
    slider_1.text_pos.x = slider_1.rec.x + slider_1.full_width + 10;
    slider_1.text_pos.y = slider_1.rec.y - 5;
//---------slider_1------------------------------------------------------------------------

//---------slider_2------------------------------------------------------------------------
    slider_2.rec = (Rectangle){30, 280, 150, 5};
    slider_2.full_width = 300;
    slider_2.r = 1.0;
    slider_2.cR = 0;
    slider_2.cG = 255;
    slider_2.cB = 0;
    slider_2.cA = 255;
    strcpy(slider_2.slider_text, "127");
    slider_2.text_pos.x = slider_2.rec.x + slider_2.full_width + 10;
    slider_2.text_pos.y = slider_2.rec.y - 5;
//---------slider_2------------------------------------------------------------------------

//---------slider_3------------------------------------------------------------------------
    slider_3.rec = (Rectangle){30, 310, 150, 5};
    slider_3.full_width = 300;
    slider_3.r = 1.0;
    slider_3.cR = 0;
    slider_3.cG = 0;
    slider_3.cB = 255;
    slider_3.cA = 255;
    strcpy(slider_3.slider_text, "127");
    slider_3.text_pos.x = slider_3.rec.x + slider_3.full_width + 10;
    slider_3.text_pos.y = slider_3.rec.y - 5;
//---------slider_3------------------------------------------------------------------------

//---------checkbox_1----------------------------------------------------------------------
    strcpy(checkbox_1.checkbox_name, "Rounded 0.0");
    checkbox_1.rec = (Rectangle){30, 340, 16, 16};
    checkbox_1.r = 0.3;
    checkbox_1.cR = 26;
    checkbox_1.cG = 188;
    checkbox_1.cB = 156;
    checkbox_1.cA = 255;
    checkbox_1.text_pos.x = (checkbox_1.rec.x) + 25; //позиция текста
    checkbox_1.text_pos.y = checkbox_1.rec.y + 2;
    checkbox_1.select = 1;
//---------checkbox_1----------------------------------------------------------------------

//---------checkbox_2----------------------------------------------------------------------
    strcpy(checkbox_2.checkbox_name, "Rounded 0.5");
    checkbox_2.rec = (Rectangle){30, 370, 16, 16};
    checkbox_2.r = 0.3;
    checkbox_2.cR = 26;
    checkbox_2.cG = 188;
    checkbox_2.cB = 156;
    checkbox_2.cA = 255;
    checkbox_2.text_pos.x = (checkbox_2.rec.x) + 25; //позиция текста
    checkbox_2.text_pos.y = checkbox_2.rec.y + 2;
    checkbox_2.select = 0;
//---------checkbox_2----------------------------------------------------------------------

//---------checkbox_3----------------------------------------------------------------------
    strcpy(checkbox_3.checkbox_name, "Rounded 1.0");
    checkbox_3.rec = (Rectangle){30, 400, 16, 16};
    checkbox_3.r = 0.3;
    checkbox_3.cR = 26;
    checkbox_3.cG = 188;
    checkbox_3.cB = 156;
    checkbox_3.cA = 255;
    checkbox_3.text_pos.x = (checkbox_3.rec.x) + 25; //позиция текста
    checkbox_3.text_pos.y = checkbox_3.rec.y + 2;
    checkbox_3.select = 0;
//---------checkbox_3----------------------------------------------------------------------

//---------circles-------------------------------------------------------------------------
    circleR = button_1.cR;
    circleG = button_1.cG;
    circleB = button_1.cB;
    circleR_2 = 127;
    circleG_2 = 127;
    circleB_2 = 127;
//---------circle--------------------------------------------------------------------------
}

void draw_buttons(void) {
    DrawRectangleRounded(button_1.rec,
                         button_1.r,
                         5,
                         CLITERAL(Color){button_1.cR,
                         button_1.cG,
                         button_1.cB,
                         (button_1.pressed)? button_1.cA - 80: button_1.cA});
    DrawTextEx(current_font, button_1.button_name, button_1.text_pos, FONT_SIZE, 0, WHITE);

    DrawRectangleRounded(button_2.rec,
                         button_2.r,
                         5,
                         CLITERAL(Color){button_2.cR,
                         button_2.cG,
                         button_2.cB,
                         (button_2.pressed)? button_2.cA - 80: button_2.cA});
    DrawTextEx(current_font, button_2.button_name, button_2.text_pos, FONT_SIZE, 0, WHITE);
    //DrawLine(40, 100, 40 + (int)MeasureTextEx(current_font, button_1.button_name, 16, 0).x, 100, RED);

    DrawRectangleRounded(button_3.rec,
                         button_3.r,
                         5,
                         CLITERAL(Color){button_3.cR,
                         button_3.cG,
                         button_3.cB,
                         (button_3.pressed)? button_3.cA - 80: button_3.cA});
    DrawTextEx(current_font, button_3.button_name, button_3.text_pos, FONT_SIZE, 0, WHITE);
}

void draw_sliders(void) {
//---------slider_1------------------------------------------------------------------------
    DrawRectangleRounded((Rectangle){slider_1.rec.x, slider_1.rec.y, slider_1.full_width, slider_1.rec.height},
                         slider_1.r,
                         5,
                         CLITERAL(Color){153,
                         153,
                         153,
                         255});
    DrawRectangleRounded(slider_1.rec,
                         slider_1.r,
                         5,
                         CLITERAL(Color){slider_1.cR,
                         slider_1.cG,
                         slider_1.cB,
                         slider_1.cA});
    DrawTextEx(current_font, slider_1.slider_text, slider_1.text_pos, FONT_SIZE, 0, WHITE);

//---------slider_2------------------------------------------------------------------------
    DrawRectangleRounded((Rectangle){slider_2.rec.x, slider_2.rec.y, slider_2.full_width, slider_2.rec.height},
                         slider_2.r,
                         5,
                         CLITERAL(Color){153,
                         153,
                         153,
                         255});
    DrawRectangleRounded(slider_2.rec,
                         slider_2.r,
                         5,
                         CLITERAL(Color){slider_2.cR,
                         slider_2.cG,
                         slider_2.cB,
                         slider_2.cA});
    DrawTextEx(current_font, slider_2.slider_text, slider_2.text_pos, FONT_SIZE, 0, WHITE);

//---------slider_3------------------------------------------------------------------------
    DrawRectangleRounded((Rectangle){slider_3.rec.x, slider_3.rec.y, slider_3.full_width, slider_3.rec.height},
                         slider_3.r,
                         5,
                         CLITERAL(Color){153,
                         153,
                         153,
                         255});
    DrawRectangleRounded(slider_3.rec,
                         slider_3.r,
                         5,
                         CLITERAL(Color){slider_3.cR,
                         slider_3.cG,
                         slider_3.cB,
                         slider_3.cA});
    DrawTextEx(current_font, slider_3.slider_text, slider_3.text_pos, FONT_SIZE, 0, WHITE);

}

void draw_checkboxes(void) {
//---------checkbox_1----------------------------------------------------------------------
    DrawRectangleRounded(checkbox_1.rec,
                         checkbox_1.r,
                         5,
                         CLITERAL(Color){checkbox_1.cR,
                         checkbox_1.cG,
                         checkbox_1.cB,
                         checkbox_1.cA});
    if (checkbox_1.select) DrawCircle(checkbox_1.rec.x + checkbox_1.rec.width/2, checkbox_1.rec.y + checkbox_1.rec.height/2, 3, CLITERAL(Color){255, 255, 255, 255});
    DrawTextEx(current_font, checkbox_1.checkbox_name, checkbox_1.text_pos, FONT_SIZE, 0, WHITE);
//---------checkbox_1----------------------------------------------------------------------

//---------checkbox_2----------------------------------------------------------------------
    DrawRectangleRounded(checkbox_2.rec,
                         checkbox_2.r,
                         5,
                         CLITERAL(Color){checkbox_2.cR,
                         checkbox_2.cG,
                         checkbox_2.cB,
                         checkbox_2.cA});
    if (checkbox_2.select) DrawCircle(checkbox_2.rec.x + checkbox_2.rec.width/2, checkbox_2.rec.y + checkbox_2.rec.height/2, 3, CLITERAL(Color){255, 255, 255, 255});
    DrawTextEx(current_font, checkbox_2.checkbox_name, checkbox_2.text_pos, FONT_SIZE, 0, WHITE);
//---------checkbox_2----------------------------------------------------------------------

//---------checkbox_3----------------------------------------------------------------------
    DrawRectangleRounded(checkbox_3.rec,
                         checkbox_3.r,
                         5,
                         CLITERAL(Color){checkbox_3.cR,
                         checkbox_3.cG,
                         checkbox_3.cB,
                         checkbox_3.cA});
    if (checkbox_3.select) DrawCircle(checkbox_3.rec.x + checkbox_3.rec.width/2, checkbox_3.rec.y + checkbox_3.rec.height/2, 3, CLITERAL(Color){255, 255, 255, 255});
    DrawTextEx(current_font, checkbox_3.checkbox_name, checkbox_3.text_pos, FONT_SIZE, 0, WHITE);
//---------checkbox_3----------------------------------------------------------------------
}

void check_collision (void) {
//---------buttons-------------------------------------------------------------------------
    if (CheckCollisionPointRec(mouse, button_1.rec) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        button_1.pressed = 1; //для изменения цвета кнопки
        which_button_is_pressed = 1; //для обработки действия (изменения цвета круга)
    } else button_1.pressed = 0;

    if (CheckCollisionPointRec(mouse, button_2.rec) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        button_2.pressed = 1;
        which_button_is_pressed = 2;
    } else button_2.pressed = 0;

    if (CheckCollisionPointRec(mouse, button_3.rec) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        button_3.pressed = 1;
        which_button_is_pressed = 3;
    } else button_3.pressed = 0;
//---------buttons-------------------------------------------------------------------------

//---------sliders-------------------------------------------------------------------------
    if (CheckCollisionPointCircle(mouse, (Vector2){slider_1.rec.x + slider_1.rec.width, slider_1.rec.y + slider_1.rec.height/2}, 20)
        && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        slider_1.rec.width = mouse.x - slider_1.rec.x;
        if (slider_1.rec.width < 0) slider_1.rec.width = 0;
        if (slider_1.rec.width > slider_1.full_width) slider_1.rec.width = slider_1.full_width;
        _itoa((int)(slider_1.rec.width*255/300), slider_1.slider_text, 10);
        circleR_2 = (int)(slider_1.rec.width*255/300);
    }

    if (CheckCollisionPointCircle(mouse, (Vector2){slider_2.rec.x + slider_2.rec.width, slider_2.rec.y + slider_2.rec.height/2}, 20)
        && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        slider_2.rec.width = mouse.x - slider_2.rec.x;
        if (slider_2.rec.width < 0) slider_2.rec.width = 0;
        if (slider_2.rec.width > slider_2.full_width) slider_2.rec.width = slider_2.full_width;
        _itoa((int)(slider_2.rec.width*255/300), slider_2.slider_text, 10);
        circleG_2 = (int)(slider_2.rec.width*255/300);
    }

    if (CheckCollisionPointCircle(mouse, (Vector2){slider_3.rec.x + slider_3.rec.width, slider_3.rec.y + slider_3.rec.height/2}, 20)
        && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        slider_3.rec.width = mouse.x - slider_3.rec.x;
        if (slider_3.rec.width < 0) slider_3.rec.width = 0;
        if (slider_3.rec.width > slider_3.full_width) slider_3.rec.width = slider_3.full_width;
        _itoa((int)(slider_3.rec.width*255/300), slider_3.slider_text, 10);
        circleB_2 = (int)(slider_3.rec.width*255/300);
    }
//---------sliders-------------------------------------------------------------------------

//---------checkboxes----------------------------------------------------------------------
    if (CheckCollisionPointRec(mouse, checkbox_1.rec) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        checkbox_1.select = 1;
        checkbox_2.select = 0;
        checkbox_3.select = 0;
        rect_rounded = 0.0;
    }

        if (CheckCollisionPointRec(mouse, checkbox_2.rec) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        checkbox_1.select = 0;
        checkbox_2.select = 1;
        checkbox_3.select = 0;
        rect_rounded = 0.5;
        }

    if (CheckCollisionPointRec(mouse, checkbox_3.rec) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        checkbox_1.select = 0;
        checkbox_2.select = 0;
        checkbox_3.select = 1;
        rect_rounded = 1.0;
    }
//---------checkboxes----------------------------------------------------------------------
}

void change_circle_color(void) {
    switch(which_button_is_pressed) {
        case 1:
            circleR = button_1.cR;
            circleG = button_1.cG;
            circleB = button_1.cB;
            break;
        case 2:
            circleR = button_2.cR;
            circleG = button_2.cG;
            circleB = button_2.cB;
            break;
        case 3:
            circleR = button_3.cR;
            circleG = button_3.cG;
            circleB = button_3.cB;
            break;
    }
}

void draw_figures(void) {
    DrawCircle(400, 100, 50, CLITERAL(Color){circleR, circleG, circleB, 255});
    DrawRectangleRounded((Rectangle){160, 340, 200, 80}, rect_rounded, 10, CLITERAL(Color){circleR_2, circleG_2, circleB_2, 255});
}

int main(void) {
    init(); //инициализация
    SetTargetFPS(30);
    while (!WindowShouldClose()) {

        mouse = GetMousePosition(); //определение позиции курсора мыши
        check_collision();
        change_circle_color();

        BeginDrawing();

            ClearBackground(CLITERAL(Color){41, 58, 74, 255}); //очистка экрана
            draw_buttons();
            draw_sliders();
            draw_checkboxes();
            draw_figures(); //отрисовка круга и прямоугольника

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
