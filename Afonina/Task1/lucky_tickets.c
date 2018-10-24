#include <stdio.h>
#include <string.h>

int main(void) {
    int digits_sum_cnt[28], tickets_cnt = 0;
    memset(digits_sum_cnt, 0, 28 * sizeof(int));
    for (int i = 0; i < 1000; ++i) {
        ++digits_sum_cnt[(i % 10) + ((i / 10) % 10) + i / 100];
    }

    for (int i = 0; i < 28; ++i) {
        tickets_cnt += digits_sum_cnt[i] * digits_sum_cnt[i];
    }

    printf("%d\n", tickets_cnt);
	return 0;
}
