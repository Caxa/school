#include <stdio.h>

int is_prime(int num) {
  if (num <= 1) {
    return 0;
  }
  for (int i = 2; i * i <= num; i++) {
    int product = i * i;
    while (product <= num) {
      if (product == num) {
        return 0;
      }
      product += i;
    }
  }
  return 1;
}

int find_largest_prime_divisor(int num) {
  if (num < 0) {
    num = -num;
  }
  int largest_prime_divisor = 1;
  for (int i = 2; i <= num; i++) {
    int product = i;
    while (product <= num) {
      if (num - product == 0 && is_prime(i)) {
        largest_prime_divisor = i;
      }
      product += i;
    }
  }
  return largest_prime_divisor;
}

int main() {
  int num;
  if (scanf("%d", &num) != 1 || getchar() != '\n' || num == 0 || num == 1) {
    printf("a\n");
    return 1;
  }
  int result = find_largest_prime_divisor(num);
  printf("%d", result);

  return 0;
}
