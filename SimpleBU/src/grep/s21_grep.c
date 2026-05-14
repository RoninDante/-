#define _POSIX_C_SOURCE 200809L
#include "s21_grep.h"

int main(int argc, char* argv[]) {
  Flags fl = {0};
  Flags* ufl = &fl;
  if (parser(argc, argv, &ufl)) {
    return 1;
  }
  create_reg(argc, argv, fl);
  free(fl.temp);
  return 0;
}

int parser(int argc, char* argv[], Flags** fl) {
  int f = 0;
  int rez;

  while ((rez = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (rez) {
      case 'e':
        (*fl)->e = 1;
        create_temp(*fl, optarg);
        break;

      case 'i':
        (*fl)->i = REG_ICASE;
        break;

      case 'v':
        (*fl)->v = 1;
        break;

      case 'c':
        (*fl)->c = 1;
        break;

      case 'l':
        (*fl)->l = 1;
        break;

      case 'n':
        (*fl)->n = 1;
        break;

      case 'h':
        (*fl)->h = 1;
        break;

      case 's':
        (*fl)->h = 1;
        break;

      case 'f':
        (*fl)->f = 1;
        create_temp_file(*fl, optarg);
        break;

      case 'o':
        (*fl)->o = 1;
        break;

      case '?':
        f = 1;
        break;
    }
  }

  if (((*fl)->len_temp) == 0) {
    create_temp(*fl, argv[optind]);
    optind += 1;
  }

  if (argc - optind == 1) {
    (*fl)->h = 1;
  }

  return f;
}

void create_temp(Flags* fl, const char* temp) {
  int n = strlen(temp);
  if (fl->len_temp == 0) {
    fl->temp = (char*)malloc(1024 * sizeof(char));
    fl->temp[0] = '\0';
    fl->m_temp = 1024;
  }
  if (fl->m_temp < fl->len_temp + n) {
    fl->temp = (char*)realloc(fl->temp, fl->m_temp + n + 2 * sizeof(char));
    fl->m_temp = fl->m_temp + n + 2;
  }
  if (fl->len_temp != 0) {
    strcat(fl->temp + fl->len_temp, "|");
    fl->len_temp++;
  }
  fl->len_temp += sprintf(fl->temp + fl->len_temp, "(%s)", temp);
}

void create_temp_file(Flags* fl, const char* tempfile) {
  FILE* file = fopen(tempfile, "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening file: %s\n", tempfile);
    return;
  }

  char* line_f = NULL;
  size_t len_f = 0;
  ssize_t read_f;

  while ((read_f = getline(&line_f, &len_f, file)) != -1) {
    if (read_f > 0 && line_f[read_f - 1] == '\n') {
      line_f[read_f - 1] = '\0';
      read_f--;
    }

    if (read_f > 0) {
      create_temp(fl, line_f);
    }
  }

  free(line_f);
  fclose(file);
}

int create_reg(int argc, char* argv[], Flags fl) {
  regex_t regex;

  int reti = regcomp(&regex, fl.temp, REG_EXTENDED | fl.i);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    return 1;
  }

  for (int i = optind; i < argc; i++) {
    processing_files(argv[i], fl, &regex);
  }
  regfree(&regex);
  return 0;
}

int processing_files(const char* path, Flags fl, regex_t* regex) {
  FILE* file_point;
  char* line = NULL;
  size_t len = 0;
  ssize_t read;

  file_point = fopen(path, "r");

  if (file_point == NULL) {
    if (fl.s == 0) {
      fprintf(stderr, "grep: %s No such file in directory\n", path);
    }
    return 1;
  }

  read = getline(&line, &len, file_point);
  int count_line = 1;
  int coincid = 0;

  while (read > 0) {
    int result = regexec(regex, line, 0, NULL, 0);

    if ((result == 0 && !fl.v) || (fl.v && result != 0)) {
      if (!fl.c && !fl.l) {
        if (fl.o && !fl.v) {
          find_match(line, regex, count_line, path, fl);
        } else {
          fl_analysis(count_line, path, fl);
          output_line(line, read);
        }
      }
      coincid++;
      if (fl.c && fl.l && coincid > 0) coincid = 1;
    }

    read = getline(&line, &len, file_point);
    count_line++;
  }

  if (fl.c) {
    if (!fl.h) printf("%s:", path);
    printf("%d\n", coincid);
  }
  if (fl.l && coincid > 0) printf("%s\n", path);

  free(line);
  fclose(file_point);

  return 0;
}

void output_line(const char* line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') putchar('\n');
}

void find_match(char* line, regex_t* regex, int count_line, const char* path,
                Flags fl) {
  regmatch_t match;
  int cursor = 0;
  while (1) {
    int res = regexec(regex, line + cursor, 1, &match, 0);
    if (res != 0) break;
    fl_analysis(count_line, path, fl);
    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(line[cursor + i]);
    }
    putchar('\n');

    cursor += match.rm_eo;
  }
}

void fl_analysis(int count_line, const char* path, Flags fl) {
  if (!fl.h) printf("%s:", path);
  if (fl.n) printf("%d:", count_line);
}