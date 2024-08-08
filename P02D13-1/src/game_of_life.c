#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define ROWS 25
#define COLS 80

void printBoard(const int board[ROWS][COLS]);
int countNeighbors(const int board[ROWS][COLS], int x, int y);
void checkLiveCells(const int board[ROWS][COLS], int *exitFlag);
void inputMatrix(int board[ROWS][COLS], int *exitFlag);
void updateBoard(int board[ROWS][COLS]);
int stringToInt(const char *str);
void updateDelay(int *delay, int speed);
void displayMenu(int currentSpeed, int paused);
void displayStatistics(const int board[ROWS][COLS]);
void initializeNcurses();

int main(int argc, char *argv[]) {
    int exitFlag = 0, speed;

    if (argc != 2 || (speed = stringToInt(argv[1])) < 1 || speed > 5) {
        fprintf(stderr, "Usage: %s <speed (1-5)>\n", argv[0]);
        exitFlag = 1;
    } else {
        int currentSpeed = speed, paused = 0, delay;
        updateDelay(&delay, speed);
        int board[ROWS][COLS] = {0};

        inputMatrix(board, &exitFlag);
        if (!exitFlag && freopen("/dev/tty", "r", stdin)) {
            initializeNcurses();
        } else {
            fprintf(stderr, "Failed to reopen stdin.\n");
            exitFlag = 1;
        }
        while (!exitFlag) {
            int ch = getch();
            if (ch == 'q') {
                exitFlag = 1;
            } else if (ch == 'p') {
                paused = !paused;
            } else if (ch >= '1' && ch <= '5') {
                currentSpeed = ch - '0';
                updateDelay(&delay, currentSpeed);
            }
            if (!paused) {
                printBoard(board);
                updateBoard(board);
                checkLiveCells(board, &exitFlag);
            } else {
                printBoard(board);
            }
            displayMenu(currentSpeed, paused);
            displayStatistics(board);
            usleep(delay);
        }
        endwin();
    }

    return exitFlag;
}

void initializeNcurses() {
    initscr();
    cbreak();
    noecho();
    timeout(0);
    keypad(stdscr, TRUE);
}

void printBoard(const int board[ROWS][COLS]) {
    clear();
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 1) {
                mvprintw(i, j, "*");
            } else {
                mvprintw(i, j, " ");
            }
        }
    }
    refresh();
}

int countNeighbors(const int board[ROWS][COLS], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int row = (x + i + ROWS) % ROWS;
            int col = (y + j + COLS) % COLS;
            count += board[row][col];
        }
    }
    count -= board[x][y];
    return count;
}

void updateBoard(int board[ROWS][COLS]) {
    int newBoard[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = countNeighbors(board, i, j);
            if (board[i][j] == 1) {
                if (neighbors < 2 || neighbors > 3) {
                    newBoard[i][j] = 0;
                } else {
                    newBoard[i][j] = 1;
                }
            } else {
                if (neighbors == 3) {
                    newBoard[i][j] = 1;
                } else {
                    newBoard[i][j] = 0;
                }
            }
        }
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = newBoard[i][j];
        }
    }
}

void displayStatistics(const int board[ROWS][COLS]) {
    int liveCells = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 1) {
                liveCells++;
            }
        }
    }

    move(ROWS + 1, 0);
    clrtoeol();
    printw("Live cells: %d", liveCells);
    refresh();
}

void displayMenu(int currentSpeed, int paused) {
    move(ROWS, 0);
    clrtoeol();
    if (paused == 0) {
        printw("[p] Pause | [1-5] Change Speed: %d | [q] Quit", currentSpeed);
    } else {
        printw("[p] Resume | [1-5] Change Speed: %d | [q] Quit", currentSpeed);
    }
    refresh();
}

void updateDelay(int *delay, int speed) {
    switch (speed) {
        case 1:
            *delay = 500000;
            break;
        case 2:
            *delay = 200000;
            break;
        case 3:
            *delay = 100000;
            break;
        case 4:
            *delay = 50000;
            break;
        case 5:
            *delay = 10000;
            break;
        default:
            fprintf(
                stderr,
                "Invalid speed. Use 1 (slow), 2 (medium), 3 (fast), 4 (very fast), or 5 (very very fast).\n");
    }
}

int stringToInt(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    while (str[i] == ' ') {
        i++;
    }
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return -1;
        }
        result = result * 10 + (str[i] - '0');
    }

    return sign * result;
}

void inputMatrix(int board[ROWS][COLS], int *exitFlag) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (scanf("%d", &board[i][j]) != 1) {
                fprintf(stderr, "Error reading board input.\n");
                *exitFlag = 1;
                return;
            }
        }
    }
}

void checkLiveCells(const int board[ROWS][COLS], int *exitFlag) {
    int liveCells = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 1) {
                liveCells++;
            }
        }
    }
    if (liveCells == 0) {
        move(ROWS + 2, 0);
        printw("No live cells remaining. Exiting...");
        refresh();
        sleep(2);
        *exitFlag = 1;
        endwin();
    }
}
