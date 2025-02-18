#ifndef C3_SIMPLEBASHUTILS_1_SRC_GREP_S21_GREP_H_
#define C3_SIMPLEBASHUTILS_1_SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10000

const char SHORT_FLAGS[] = "e:isvnhlc";

typedef struct {
  bool e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  bool h;
  bool s;
  bool exit;
  int c_file;
} SFlags;

typedef struct {
  char str_file[SIZE];
  char str_regex[SIZE];
} String;

typedef struct {
  char file_name[SIZE];
  char file_name_l[SIZE];
  char str_count[SIZE];
} SFile;

void flag_l(SFlags *sflag, String *str, SFile name, int match, int *while_flag);
void flag_i(SFlags *sflag, int *regflag);
void flag_n(SFile *name, SFlags *sflag);
void flag_v(SFlags *sflag, int *match);
void flag_c(SFlags *sflag, int match, int *match_count);

void preparation(SFlags *opt, String *str, int argc, char *argv[]);
void options(SFlags *opt, String *str, int argc, char *argv[]);
void grep(SFlags *opt, String *str, FILE *file, char *argv, int argc);
void info_file(SFlags *sflag, String *str, SFile name, int match);
void open_file(SFlags *sflag, String *str, int argc, char *argv[]);
void option_file(SFlags *sflag, SFile *name, char *argv, int argc);
void check_flags_after_reading(SFlags *sflag, SFile name, int match,
                               int match_count);
void print_new_str(char *str);
void del_last_char(char *str);

#endif