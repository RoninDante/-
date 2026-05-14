#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  char* temp;
  int len_temp;
  int m_temp;
} Flags;

int parser(int argc, char* argv[], Flags** fl);
int create_reg(int argc, char* argv[], Flags fl);
int processing_files(const char* path, Flags fl, regex_t* regex);
void find_match(char* line, regex_t* regex, int count_line, const char* path,
                Flags fl);
void create_temp(Flags* fl, const char* temp);
void create_temp_file(Flags* fl, const char* tempfile);
void output_line(const char* line, int n);
void fl_analysis(int count_line, const char* path, Flags fl);

#endif