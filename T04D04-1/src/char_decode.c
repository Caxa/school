#include <ctype.h> // Для функции isxdigit
#include <math.h>
#include <stdio.h>
#include <stdlib.h> // Для функции atoi

// Function to encode a single character
void encodeSingle(char c) { printf("%02X ", c); }
void encodeSingle2(char c) { printf("%02X", c); }

// Function to decode a single character
void decode(int num1) {
  if (num1 < 0 || num1 > 255) {
    printf("n/a");
  } else {
    printf("%c ", (char)num1);
  }
}
void decode2(int num1) {
  if (num1 < 0 || num1 > 255) {
    printf("n/a");
  } else {
    printf("%c", (char)num1);
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("n/a");
    return 1;
  }

  int mode = atoi(argv[1]);

  if (mode == 0) {
    char c;
    char probel;
    while (scanf(" %c", &c) == 1) {
      probel = getchar();
      if (probel == ' ') {
        encodeSingle(c);
      } else if (probel == '\n') {
        encodeSingle2(c);
        return 0;
      } else {
        printf("n/a");
        return 0;
      }
    }
  } else if (mode == 1) {
    int num1;
    while (scanf("%X", &num1) == 1) {
      if (num1 > 127) {
        printf("n/a");
        return 0;
        ;
      } else {
        char probel = getchar();
        if (probel == ' ') {
          decode(num1);
        } else if (probel == '\n') {
          decode2(num1);
          return 0;
        }
      }
    }
  } else {
    printf("n/a");
    return 1;
  }

  return 0;
}
