#include "s21_cat.h"

int main(int argc, char **argv) {
  Flags fl = {0};
  if (parser(argc, argv, &fl)) {
    fprintf(stderr, "Unknown option\n");
    return 1;
  }

  if (optind >= argc) {
    fprintf(stderr, "No files provided\n");
    return 1;
  }

  while (optind < argc) {
    print_field(argv, &fl);
    optind++;
  }
  return 0;
}

int parser(int argc, char *argv[], Flags *fl) {
  int f = 0;
  int rez;
  int option_index;

  struct option log_options[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                 {"number", no_argument, NULL, 'n'},
                                 {"squeeze-blank", no_argument, NULL, 's'},
                                 {"show-ends", no_argument, NULL, 'e'},
                                 {"show-tabs", no_argument, NULL, 't'},
                                 {0, 0, 0, 0}};

  while ((rez = getopt_long(argc, argv, "+beEvnst", log_options,
                            &option_index)) != -1) {
    switch (rez) {
      case 'b':
        fl->b = 1;
        break;
      case 'e':
        fl->e = 1;
        fl->v = 1;
        break;
      case 'n':
        fl->n = 1;
        break;
      case 's':
        fl->s = 1;
        break;
      case 't':
        fl->t = 1;
        fl->v = 1;
        break;
      case 'v':
        fl->v = 1;
        break;
      case '?':
        f = 1;
        break;
    }
  }

  // Если включен -b, выключаем -n
  if (fl->b) {
    fl->n = 0;
  }

  return f;
}

void print_field(char **argv, const Flags *fl) {
  FILE *file_point;
  int c;
  int past_c = '\n';
  int count_str = 1;
  int last_line_blank = 0;

  if ((file_point = fopen(argv[optind], "r")) == NULL) {
    fprintf(stderr, "cat: %s: No such file in directory\n", argv[optind]);
    return;
  }

  while ((c = fgetc(file_point)) != EOF) {
    // Сжатие пустых строк
    if (fl->s && past_c == '\n' && c == '\n') {
      // Если это вторая и последующая пустые строки, пропускаем вывод
      last_line_blank++;
      if (last_line_blank > 0)
        continue;  // Пропускаем, если это не первая пустая строка
    } else {
      last_line_blank = 0;  // Сбрасываем, если строка не пустая
    }

    // Вывод номера строки
    if (fl->n && past_c == '\n' && c != '\n') {
      printf("%6d\t", count_str++);
    }

    if (fl->b && past_c == '\n' && c != '\n') {
      printf("%6d\t", count_str++);
    }

    // Обработка табуляций
    if (fl->t && c == '\t') {
      printf("^I");
      past_c = c;
      continue;
    }

    // Обработка концов строк
    if (fl->e && c == '\n') {
      printf("$");
    }

    // Обработка специальных символов с флагом -v
    if (fl->v) {
      if (c > 127 && c < 160) {
        printf("M-^");
      } else if (c < 32 && c != '\n' && c != '\t') {
        printf("^%c", c + 64);
      } else if (c == 127) {
        printf("^?");  // Обработка DEL
        past_c = c;
        continue;
      }
    }

    // Вывод обычных символов
    printf("%c", c);
    past_c = c;  // Обновляем предшествующий символ
  }

  fclose(file_point);
}