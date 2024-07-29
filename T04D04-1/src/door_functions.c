#include <math.h>
#include <stdio.h>

double witch_of_agnesi(double x) { return 1 / (1 + x * x); }

double bernoulli_lemniscate(double x) {
  return sqrt(sqrt(1 + 4 * x * x) - (x * x) - 1);
}

double quadratic_hyperbola(double x) { return 1 / pow(x, 2); }

int main() {
  double x, y1, y2, y3;

  for (int i = 0; i <= 41; i++) {
    x = -M_PI + i * (2 * M_PI / 41);
    y1 = witch_of_agnesi(x);
    y2 = bernoulli_lemniscate(x);
    y3 = quadratic_hyperbola(x);

    if (isnan(y2) || isinf(y2)) {
      printf("%.7f | %.7f | - | %.7f\n", x, y1, y3);
    } else if (isnan(y1) || isinf(y1)) {
      printf("%.7f | - | %.7f | %.7f\n", x, y2, y3);
    } else if (isnan(y3) || isinf(y3)) {
      printf("%.7f | %.7f | %.7f | -\n", x, y1, y2);
    } else
      printf("%.7f | %.7f | %.7f | %.7f\n", x, y1, y2, y3);
  }

  return 0;
}
