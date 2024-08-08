#include <stdio.h>

void render(int leftR, int rightR, int ballX, int ballY) {
    // Очистить экран с использованием ANSI Escape Sequences
    printf("\033[H");

    for (int height = 0; height < 25; height++) {
        for (int width = 0; width < 80; width++) {
            if (height == 0 || height == 24) {
                printf("#");
            } else if (height == ballY && width == ballX) {
                printf("O");
            } else if ((height == leftR || height == leftR + 1 || height == leftR - 1) && width == 1) {
                printf("|");
            } else if ((height == rightR || height == rightR + 1 || height == rightR - 1) && width == 78) {
                printf("|");
            } else if (width == 0 || width == 79) {
                printf("*");
            } else {
                printf(" ");
            }
            if (width == 40 && (height > 1 && height < 23)) {
                printf("$");
            }
        }
        printf("\n");
    }
}

int main() {
    int leftR = 12;
    int rightR = 12;
    int ballX = 40;           // Начальная позиция мяча по оси X
    int ballY = 12;           // Начальная позиция мяча по оси Y
    int ballDirectionX = 1;   // Направление движения мяча по оси X
    int ballDirectionY = -1;  // Направление движения мяча по оси Y
    int scoreLeft = 0;        // Счет левого игрока
    int scoreRight = 0;       // Счет правого игрока

    while (1) {
        // Перемещение курсора в начало экрана с использованием ANSI Escape Sequences
        printf("\033[H");

        ballX += ballDirectionX;
        ballY += ballDirectionY;

        if (ballX == 1 || ballX == 78) {
            ballDirectionX =
                -(ballDirectionX);  // Изменить направление движения мяча при достижении края поля по оси X
        }

        if (ballY == 1 || ballY == 23) {
            ballDirectionY =
                -(ballDirectionY);  // Изменить направление движения мяча при достижении края поля по оси X
        }

        // Проверка столкновения мяча с ракетками
        if ((ballX == 2 && (ballY == leftR || ballY == leftR + 1 || ballY == leftR - 1)) ||
            (ballX == 77 && (ballY == rightR || ballY == rightR + 1 || ballY == rightR - 1))) {
            ballDirectionX =
                -(ballDirectionX);  // Изменить направление движения мяча при столкновении с ракеткой
        }

        if (ballX == 1) {
            scoreRight += 1;
            ballX = 40;
            ballY = 12;
            leftR = 12;
            rightR = 12;
        }

        if (ballX == 78) {
            scoreLeft += 1;
            ballX = 40;
            ballY = 12;
            leftR = 12;
            rightR = 12;
        }
        // Логика движения ракеток
        if (1) {
            char key = getchar();
            if (key == 'a' && leftR > 2) {
                (leftR)--;
            } else if (key == 'z' && leftR < 22) {
                (leftR)++;
            } else if (key == 'k' && rightR > 2) {
                (rightR)--;
            } else if (key == 'm' && rightR < 22) {
                (rightR)++;
            }
        }

        render(leftR, rightR, ballX, ballY);

        // Здесь можно добавить логику для других действий игроков
        // Вывод счета
        printf("Score: Left - %d, Right - %d\n", scoreLeft, scoreRight);

        // Проверка на завершение игры при достижении 2 очков одним из игроков
        if (scoreLeft == 21 || scoreRight == 21) {
            printf("%s %s", "Congratilutaion!", "Game Over\n");
            break;
        }

        // Задержка для визуализации движения мяча
        for (int i = 0; i < 100000000; i++) {
        }
    }

    return 0;
}
