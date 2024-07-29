#include <stdio.h>

int main() {
  float a, b;

  if (!(scanf("%f", &a) != 1.0) && !(scanf("%f", &b) != 1.0)) {
    if (a * a + b * b <= 25) {
      printf("GOTCHA");
    } else {
      printf("MISS");
    }
  } else {
    printf("n/a");
  }

  return 0;
}
