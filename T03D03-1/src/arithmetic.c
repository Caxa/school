#include <stdio.h>

int sum(int a, int b);
int raz(int a, int b);
int del(int a, int b);
int mul(int a, int b);

int main() {
  int a, b;

  if (!(scanf("%d%d", &a, &b) != 2) && getchar() == '\n') {
    if (a == (int)a && b == (int)b) {
      printf("%d %d ", sum(a, b), raz(a, b));
      printf("%d ", mul(a, b));

      if (b == 0) {
        printf("n/a");
      } else {
        printf("%d", del(a, b));
      }
    } else {
      printf("n/a n/a n/a n/a");
    }
  } else {
    printf("n/a n/a n/a n/a");
  }

  return 0;
}

int sum(int a, int b) { return a + b; }

int raz(int a, int b) { return a - b; }

int del(int a, int b) { return a / b; }

int mul(int a, int b) { return a * b; }
