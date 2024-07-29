#include <stdio.h>

int fibonacci(int n) {
  if (n <= 1)
    return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
  int n, result;

  if (scanf("%d", &n) != 1 || getchar() != '\n') {
    printf("n/a\n");
    return 1;
  }

  result = fibonacci(n);
  printf("%d\n", result);

  return 0;
}
