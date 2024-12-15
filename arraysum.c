#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define SIZE 100
int array[SIZE]; // Large array to be filled
int main() {
  for (int i = 0; i < SIZE; i++) {
    array[i] = i+1;
  }
  int sum = 0;
  #pragma omp parallel for reduction(+:sum)
  for (int i = 0; i < SIZE; i++) {
    sum += array[i]; // Calculate sum
  }
  printf("Total Sum: %d\n", sum);
  return 0;
}