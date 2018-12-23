#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>

extern int sort(int *a, int *b, int l, int r, int flag);

int from, to;
int ex_from = 0, ex_to = 0;

int data[100], copy[100], n, inp;

int main(int argc, char **argv) {
  static struct option opt[] = {
    {"from", 1, 0, 'f'},
    {"to", 1, 0, 't'},
    {0, 0, 0, 0}
  };
  while (1) {
    int optid;
    int cur = getopt_long(argc, argv, "f:t:", opt, &optid);
    if (cur == -1) break;
    switch (cur) {
      case 'f': from = atoi(optarg), ex_from = 1; break;
      case 't': to = atoi(optarg), ex_to = 1; break;
    }
  }
  while (scanf("%d", &inp)) {
    if (ex_from && (inp <= from)) {
      fprintf(stdout, "%d ", inp);
    }
    else if (ex_to && (inp >= to)) {
      fprintf(stderr, "%d ", inp);
    }
    else {
      copy[n] = data[n] = inp, ++n;
    }
  }
  int res = sort(data, copy, 0, n, 1);
  return res;
}
