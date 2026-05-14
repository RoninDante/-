#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} Flags;

int parser(int argc, char **argv, Flags *fl);
void print_field(char **argv, const Flags *fl);

#endif