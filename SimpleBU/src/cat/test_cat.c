#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "s21_cat.h"

void create_test_file(const char *filename, const char *content) {
  FILE *file = fopen(filename, "w");
  if (file) {
    fprintf(file, "%s", content);
    fclose(file);
  } else {
    perror("Failed to create test file");
    exit(EXIT_FAILURE);
  }
}

void delete_test_file(const char *filename) {
  if (remove(filename) != 0) {
    perror("Failed to delete test file");
  }
}

void run_test(const char *args[], const char *expected_output) {
  int fd[2];
  pipe(fd);
  pid_t pid = fork();

  if (pid == 0) {
    // Дочерний процесс
    dup2(fd[1], STDOUT_FILENO);  // Перенаправляем stdout в конец конвейера
    close(fd[0]);  // Закрываем неиспользуемый конец
    execvp(args[0], (char *const *)args);  // Выполняем команду
    perror("exec failed");                 // Если exec не удалась
    exit(EXIT_FAILURE);
  } else if (pid > 0) {
    // Родительский процесс
    close(fd[1]);  // Закрываем неиспользуемый конец
    char buffer[256];
    int bytesRead =
        read(fd[0], buffer, sizeof(buffer) - 1);  // Читаем из канала
    buffer[bytesRead] = '\0';  // Завершаем строку
    wait(NULL);  // Ждем завершения дочернего процесса

    // Отладочная информация
    printf("Output: '%s'\nExpected: '%s'\n", buffer, expected_output);

    ck_assert_str_eq(buffer, expected_output);  // Проверяем вывод
  } else {
    perror("fork failed");
    exit(EXIT_FAILURE);
  }
}

START_TEST(test_no_flags) {
  create_test_file("test.txt", "Hello World\n");
  const char *args[] = {"./s21_cat", "test.txt", NULL};
  run_test(args, "Hello World\n");
  delete_test_file("test.txt");
}

START_TEST(test_number_nonblank) {
  create_test_file("test.txt", "Hello World\n\nThis is a test\n");

  const char *args[] = {"./s21_cat", "-b", "test.txt", NULL};

  // Исправленный ожидаемый вывод с учетом лишних переносов строк
  run_test(args, "     1\tHello World\n\n     2\tThis is a test\n");

  delete_test_file("test.txt");
}

START_TEST(test_squeeze_blank) {
  create_test_file("test.txt", "Hello World\n\n\nThis is a test\n\n");

  const char *args[] = {"./s21_cat", "-s", "test.txt", NULL};

  // Исправленный ожидаемый вывод с учетом лишних пустых строк
  run_test(args, "Hello World\nThis is a test\n");

  delete_test_file("test.txt");
}

START_TEST(test_show_ends) {
  create_test_file("test.txt", "Hello World\n");

  const char *args[] = {"./s21_cat", "-e", "test.txt", NULL};

  run_test(args, "Hello World$\n");  // Добавляем переход на новую строку

  delete_test_file("test.txt");
}

START_TEST(test_show_tabs) {
  create_test_file("test.txt", "Hello\tWorld\n");

  const char *args[] = {"./s21_cat", "-t", "test.txt", NULL};

  run_test(args, "Hello^IWorld\n");

  delete_test_file("test.txt");
}

int main(void) {
  Suite *s;
  SRunner *sr;

  s = suite_create("S21 Cat Tests");

  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_no_flags);
  tcase_add_test(tc_core, test_number_nonblank);
  tcase_add_test(tc_core, test_squeeze_blank);
  tcase_add_test(tc_core, test_show_ends);
  tcase_add_test(tc_core, test_show_tabs);

  suite_add_tcase(s, tc_core);

  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);

  int number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  if (number_failed == 0) {
    printf("All tests passed successfully!\n");
    return 0;
  } else {
    printf("Number of failed tests: %d\n", number_failed);
    return 1;
  }
}