CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11

all: s21_grep

s21_grep:
	$(CC) $(FLAGS) s21_grep.c -o s21_grep

rebuild:
	rm s21_grep
	make all


test_start:all test test_sh clean

test: test.o 
	$(CC) $(CFLAGS) test.o -o test

test.o: test.c
	$(CC) -c $(CFLAGS) test.c	

test_sh:
	sh test_s21_grep.sh	

clean:
	rm -rf *.o ./s21_grep
	rm -rf *.o ./test
