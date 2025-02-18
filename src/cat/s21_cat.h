#ifndef C3_SIMPLEBASHUTILS_1_SRC_CAT_S21_CAT_H_
#define C3_SIMPLEBASHUTILS_1_SRC_CAT_S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

const char SHORT_FLAGS[] = "+beEnstTv";

struct SFlags {
  unsigned char b;
  unsigned char e;
  unsigned char v;
  unsigned char n;
  unsigned char s;
  unsigned char t;
};

typedef struct SFlags SFlags;

struct option LONG_FLAGS[] = {{"number-nonblank", 0, NULL, 'b'},
                              {"end-line", 0, NULL, 'e'},
                              {"number", 0, NULL, 'n'},
                              {"squeeze-blank", 0, NULL, 's'},
                              {"tabs", 0, NULL, 't'},
                              {"non-printing", 0, NULL, 'v'},
                              {NULL, 0, NULL, 0}};

int parser(int argc, char **argv, SFlags *sflag);
int set_flags(char arg_symbol, SFlags *sflag);
void open_file(char **argv, const SFlags *sflag);
int check_flag_s(const SFlags *sflag, const char *last_symbol, const int *ch,
                 int *count_ent);
void check_flag_b(const char *last_symbol, const SFlags *sflag, const int *ch,
                  int *count_str);
int check_t_flag(const SFlags *sflag, int *ch);
void check_flag_e(const SFlags *sflag, int ch);
void check_flag_v(const SFlags *sflag, int *ch);

#endif
