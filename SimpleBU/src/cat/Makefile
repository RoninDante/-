CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
LDFLAGS = -lcheck -lm -lsubunit  # Добавлено -lsubunit

# Исполняемые файлы
TARGET = s21_cat
TEST_TARGET = test_cat

all: $(TARGET)

$(TARGET): s21_cat.c
	$(CC) $(FLAGS) s21_cat.c -o $(TARGET)

# Цель для тестов
test: $(TEST_TARGET)
	./$(TEST_TARGET)  # Запуск тестов после компиляции

$(TEST_TARGET): test_cat.c
	$(CC) $(FLAGS) test_cat.c -o $(TEST_TARGET) $(LDFLAGS)

# Перестроить цель
rebuild: clean all

# Очистка скомпилированных файлов
clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all test rebuild clean
