#include <stdio.h>

int LuckySumCount[28];

int main() {
  for (int a = 0; a < 10; ++ a) {
    for (int b = 0; b < 10; ++b) {
      for (int c = 0; c < 10; ++c) {
        ++LuckySumCount[a + b + c];
      }
    }
  }
  int LuckyTicketsCount = 0;
  for (int i = 0; i < 28; ++i) {
    LuckyTicketsCount += LuckySumCount[i] * LuckySumCount[i];
  }
  printf("%d", LuckyTicketsCount);
}
