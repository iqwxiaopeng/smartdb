#include <stdio.h>

extern "C"
void print_csv() {
  FILE *fp = fopen("hogehoge.csv", "r");

  char content[1000];
  fread(content, 1000, 1, fp);

  printf("%s\n", content);
}
