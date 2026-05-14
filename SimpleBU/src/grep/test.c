#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {
  FILE *fp1, *fp2;
  char buffer1[MAX_LINE_LENGTH], buffer2[MAX_LINE_LENGTH];

  if (argc != 3) {
    printf("Usage: %s <filename1> <filename2>\n", argv[0]);
    exit(1);
  }

  fp1 = fopen(argv[1], "r");
  if (fp1 == NULL) {
    printf("Error opening file %s\n", argv[1]);
    exit(1);
  }

  fp2 = fopen(argv[2], "r");
  if (fp2 == NULL) {
    printf("Error opening file %s\n", argv[2]);
    exit(1);
  }

  while (fgets(buffer1, sizeof(buffer1), fp1) &&
         fgets(buffer2, sizeof(buffer2), fp2)) {
    if (strcmp(buffer1, buffer2) != 0) {
      printf("Тест не пройден\n");
      fclose(fp1);
      fclose(fp2);
      return 1;
    }
  }

  if (fgets(buffer1, sizeof(buffer1), fp1) != NULL ||
      fgets(buffer2, sizeof(buffer2), fp2) != NULL) {
    printf("Тест не пройден\n");
    fclose(fp1);
    fclose(fp2);
    return 1;
  }

  printf("Тест пройден\n");
  fclose(fp1);
  fclose(fp2);
  return 0;
}
