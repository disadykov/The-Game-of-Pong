// Copyright[2022] <celestac, eugenieg, leighaxe, yamchajh>
#include <stdio.h>
#define HEIGHT_POLYGON 27;
#define WIDTH_POLYGON 82;
#define ROCK_LEFT_START 22;
#define ROCK_RIGHT_START 4;

// Рисуем игровое поле
// row col - кол-во строк и столбцов
// rockLY rockRY - координата левого верхнего угла каждой рокетки
// ballX ballY - координаты мяча
void gamePolygon(int row, int col, int rockLY,
                int rockRY, int ballY, int ballX);
// Очистить консоль
void clearScreen();
// Вывод и отрисовка итогов игры
// pOne pTwo - набранные очки игроков
void gameStatus(int col, int pOne, int pTwo);
// заполнение пробелами N штук
void spaceBar(int n);

int main() {
    int height = HEIGHT_POLYGON;
    int width = WIDTH_POLYGON;
    int rleftY = ROCK_LEFT_START;
    int rrightY = ROCK_RIGHT_START;
    int playerOne = 0;
    int playerTwo = 0;
    int dx = -1;
    int dy = 1;
    int x = height / 2;
    int y = width / 2;

    while (playerOne <= 21 && playerTwo <= 21) {
    clearScreen();
    gameStatus(width, playerOne, playerTwo);
    gamePolygon(height, width, rleftY, rrightY, x, y);

    // Проверка на корректность считанных клавиш
    char key;
    printf("Enter 'a','z','k' or 'm' or space bar: \n");
    while (((key = getchar()) != 'a') && (key != 'z') && (key != 'A')
            && (key != 'Z') && (key != 'k') && (key != 'm')
            && (key != 'K') && (key != 'M') && (key != ' ')) {
    clearScreen();
    gameStatus(width, playerOne, playerTwo);
    gamePolygon(height, width, rleftY, rrightY, x, y);
    printf("Enter 'a','z','k' or 'm' or space bar: \n");
    }
    char button_1;
    button_1 = key;

    // Изменение положений ракеток
    if ((button_1 == 97) || (button_1 == 65)) {
        if (rleftY >= 3) {--rleftY;}
    } else if ((button_1 == 122) || (button_1 == 90)) {
        if (rleftY <= 23) {++rleftY;}
    } else if ((button_1 == 107) || (button_1 == 75)) {
        if (rrightY >= 3) {--rrightY;}
    } else if ((button_1 == 109) || (button_1 == 77)) {
        if (rrightY <= 23) {++rrightY;}
    }

    // Изменение положения мяча
    x = x + dx;
    y = y + dy;
      if (x == 2 || x == 26) {dx = -dx;}
      if (y == 3) {
        if (x >= rleftY && x <= rleftY + 3) {
            dy = -dy;
        } else {
          x = height / 2;
          y = width / 2;
          dy = -dy;
          playerTwo++;
            if (playerTwo == 21) {
            clearScreen();
            gameStatus(width, playerOne, playerTwo);
            gamePolygon(height, width, rleftY, rrightY, x, y);
            break;
         }
        }
      }
      if (y == 80) {
        if (x >= rrightY && x <= rrightY + 3) {
            dy = -dy;
        } else {
         x = height / 2;
         y = width / 2;
         dy = -dy;
         playerOne++;
            if (playerOne == 21) {
            clearScreen();
            gameStatus(width, playerOne, playerTwo);
            gamePolygon(height, width, rleftY, rrightY, x, y);
            break;
         }
        }
      }
}
     return 0;
}

void clearScreen() { printf("\033[0d\033[2J"); }

void gamePolygon(int row, int col, int rockLY,
                 int rockRY, int ballY, int ballX) {
    // Символ для рисования рокетки
    char rockMask = '|';
    // Символ для рисования центрального разделения
    char centrMask = '|';
    // Символ для горизонтальной линии
    char maskG = '#';
    // Символ для вертикальной линии
    char maskV = '#';
    // Символ для мяча
    char ballMask = 'o';
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            if (i == 1 || i == row) {
                printf("%c", maskG);
            } else {
                if ((j == 1 && i > 1) || (j == col && i > 1)) {
                    printf("%c", maskV);
                } else {
                    if (((i == rockLY || i == rockLY + 1 || i == rockLY + 2) &&
                        (j == 2)) ||
                        ((i == rockRY || i == rockRY + 1 || i == rockRY + 2) &&
                        (j == 81))) {
                        printf("%c", rockMask);
                    } else {
                        if (j == ballX && i == ballY) {
                            printf("%c", ballMask);

                        } else {
                            if (j == (col / 2)) {
                                printf("%c", centrMask);

                            } else {
                                printf(" ");
                            }
                        }
                    }
                }
            }
        }
        printf("\n");
    }
}
void spaceBar(int n) {
    for (int i = 0; i <= n; i++) {
        printf(" ");
    }
}
void gameStatus(int col, int pOne, int pTwo) {
    char mask = '-';
    for (int i = 1; i <= col; i++) {
        printf("%c", mask);
    }
    printf("\n");

    if (pOne < 21) {
        spaceBar(10);
        printf("Gamer 1 points = %d", pOne);
        spaceBar(9);
    } else {
        spaceBar(6);
        printf("Gamer 1 WIN! Congratulations! ");
        spaceBar(3);
    }

    if (pTwo < 21) {
        spaceBar(10);
        printf("Gamer 2 points = %d", pTwo);
    } else {
        spaceBar(6);
        printf("Gamer 2 WIN! Congratulations! ");
    }
    printf("\n");

    for (int i = 1; i <= col; i++) {
        printf("%c", mask);
    }
    printf("\n");
}
