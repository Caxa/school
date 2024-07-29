#include <math.h>
#include <stdio.h>

int main() {
  float x, res;
  if (scanf("%f", &x) == 1 && getchar() == '\n' && x != 0) {
    res = 7e-3 * powf(x, 4) +((22.8 * powf(x, 1.0 / 3.0) - 1e3) * x + 3) / (x * x / 2) -x * powf(10 + x, 2.0 / x) - 1.01;
    printf("%.1f", res);
  } else {
    printf("n/a");
  }
  return 0;
}
