#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

// Функция для установки режима небуферизованного ввода
void setBufferedInput(int enable) {
    static struct termios oldt, newt;
    if (enable) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    } else {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
}

// Функция для проверки нажатия клавиши
int kbhit() {
    struct termios oldt, newt;
    int oldf;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

void printTable(int leftR, int rightR, int ballX, int ballY, int scoreLeft, int scoreRight) {
    printf("\033[H");  // Перемещение курсора в верхний левый угол

    // Вывод верхней границы
    for (int width = 0; width < 80; width++) {
        printf("#");
    }
    printf("\n");

    // Вывод игрового поля
    for (int height = 1; height < 24; height++) {
        for (int width = 0; width < 80; width++) {
            if (width == 0 || width == 79) {
                printf("#");  // Боковые границы
            } else if (height == ballY && width == ballX) {
                printf("O");  // Мяч
            } else if ((height == leftR || height == leftR + 1 || height == leftR - 1) && width == 1) {
                printf("|");  // Левая ракетка
            } else if ((height == rightR || height == rightR + 1 || height == rightR - 1) && width == 78) {
                printf("|");  // Правая ракетка
            } else {
                printf(" ");  // Пустое пространство
            }
            if (width == 40 && (height > 1 && height < 23)) {  //вывод сетки
                printf("$");
            }
        }
        printf("\n");
    }

    // Вывод нижней границы
    for (int width = 0; width < 80; width++) {
        printf("#");
    }
    printf("\n");

    // Вывод счета
    printf("Score: Left - %d | Right - %d\n", scoreLeft, scoreRight);
}

int main() {
    int leftR = 12;
    int rightR = 12;
    int ballX = 40;
    int ballY = 12;
    int ballDirectionX = 1;
    int ballDirectionY = -1;
    int scoreLeft = 0;
    int scoreRight = 0;

    // Переменные для отслеживания состояния клавиш
    int leftUp = 0, leftDown = 0;
    int rightUp = 0, rightDown = 0;

    setBufferedInput(0);  // Установить режим небуферизованного ввода

    // Очистка экрана в начале игры
    printf("\033[2J\033[H");

    while (1) {
        ballX += ballDirectionX;
        ballY += ballDirectionY;

        if (ballX == 1 || ballX == 78) {
            ballDirectionX = -ballDirectionX;
        }

        if (ballY == 1 || ballY == 23) {
            ballDirectionY = -ballDirectionY;
        }

        if ((ballX == 2 && (ballY == leftR || ballY == leftR + 1 || ballY == leftR - 1)) ||
            (ballX == 77 && (ballY == rightR || ballY == rightR + 1 || ballY == rightR - 1))) {
            ballDirectionX = -ballDirectionX;
        }

        if (ballX == 1) {
            scoreRight += 1;
            ballX = 40;
            ballY = 12;
            leftR = 12;
            rightR = 12;
            leftUp = 0;
            leftDown = 0;
            rightUp = 0;
            rightDown = 0;
        }

        if (ballX == 78) {
            scoreLeft += 1;
            ballX = 40;
            ballY = 12;
            leftR = 12;
            rightR = 12;
            leftUp = 0;
            leftDown = 0;
            rightUp = 0;
            rightDown = 0;
        }

        // Логика движения ракеток
        if (kbhit()) {
            char key = getchar();
            if (key == 'a') {  // Удержание клавиши a для движения вверх
                leftUp = 1;
                leftDown = 0;
            } else if (key == 'z') {  // Удержание клавиши z для движения вниз
                leftUp = 0;
                leftDown = 1;
            } else if (key == 'k') {  // Удержание клавиши k для движения вверх
                rightUp = 1;
                rightDown = 0;
            } else if (key == 'm') {  // Удержание клавиши m для движения вниз
                rightUp = 0;
                rightDown = 1;
            } else if (key == 's') {  // Остановка движения левой ракетки
                leftUp = 0;
                leftDown = 0;
            } else if (key == 'l') {  // Остановка движения правой ракетки
                rightUp = 0;
                rightDown = 0;
            } else if (key == 'q') {  // Выход из игры
                break;
            }
        }

        // Обработка движения ракеток
        if (leftUp && leftR > 2) {
            leftR--;
        }
        if (leftDown && leftR < 21) {  // Изменено на 21, чтобы предотвратить выход за границы
            leftR++;
        }
        if (rightUp && rightR > 2) {
            rightR--;
        }
        if (rightDown && rightR < 21) {  // Изменено на 21, чтобы предотвратить выход за границы
            rightR++;
        }

        // Очистка экрана перед выводом нового состояния
        printf("\033[2J\033[H");
        printTable(leftR, rightR, ballX, ballY, scoreLeft, scoreRight);

        if (scoreLeft == 21 || scoreRight == 21) {
            printf("Congratulations! Game Over\n");
            break;
        }

        // Задержка для визуализации движения мяча
        usleep(50000);  // Задержка 50 мс
    }

    setBufferedInput(1);  // Восстановить режим буферизованного ввода

    return 0;
}
