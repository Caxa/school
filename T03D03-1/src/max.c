#include <stdio.h>

int max(int a, int b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
  return -1000000000;
}

int main(void) {
  int a, b;

  if (!(scanf("%d%d", &a, &b) != 2) && getchar() == '\n') {
    int result = max(a, b);
    if (result == -1000000000) {
      printf("n/a");
    } else {
      printf("%d", result);
    }
  } else {
    printf("n/a");
  }

  return 0;
}
