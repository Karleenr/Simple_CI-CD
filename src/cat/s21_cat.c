#include "s21_cat.h"

int parser(int argc, char **argv, SFlags *sflag) {
  int flag = 1;
  int index = 0;
  char arg_symbol;
  int error = 0;
  while ((arg_symbol =
              getopt_long(argc, argv, SHORT_FLAGS, LONG_FLAGS, &index)) != -1) {
    error = set_flags(arg_symbol, sflag);
  }
  if (sflag->b) {
    sflag->n = 0;
  }
  if (error) {
    flag = 0;
  }
  return flag;
}

int set_flags(char arg_symbol, SFlags *sflag) {
  int flag = 0;
  switch (arg_symbol) {
    case 'b':
      sflag->b = 1;
      sflag->n = 0;
      break;
    case 'e':
      sflag->v = 1;
      sflag->e = 1;
      break;
    case 'E':
      sflag->e = 1;
      break;
    case 'n':
      sflag->n = 1;
      break;
    case 's':
      sflag->s = 1;
      break;
    case 't':
      sflag->v = 1;
      sflag->t = 1;
      break;
    case 'T':
      sflag->t = 1;
      break;
    case 'v':
      sflag->v = 1;
      break;
    default:
      printf("usage: s21_cat [-beEnstTv] [file ...]\n");
      flag = 1;
      break;
  }
  return flag;
}

void open_file(char **argv, const SFlags *sflag) {
  int ch;
  int count_ent = 0;
  char last_symbol = '\n';
  int count_str = 1;
  FILE *file = NULL;
  file = fopen(argv[optind], "r");
  if (file != NULL) {
    while ((ch = fgetc(file)) != EOF) {
      if (check_flag_s(sflag, &last_symbol, &ch, &count_ent) == 1) {
        continue;
      }
      check_flag_b(&last_symbol, sflag, &ch, &count_str);
      check_flag_e(sflag, ch);
      check_t_flag(sflag, &ch);
      check_flag_v(sflag, &ch);
      printf("%c", ch);
      last_symbol = ch;
    }
    fclose(file);
  } else
    printf("s21_cat: %s: No such file or directory", argv[optind]);
}

void check_flag_v(const SFlags *sflag, int *ch) {
  if (sflag->v) {
    if ((*ch > 127) && (*ch < 160)) {
      printf("M-^");
    }
    if ((*ch < 32 && *ch != '\n' && *ch != '\t') || *ch == 127) {
      printf("^");
    }
    if ((*ch < 32 || ((*ch > 126) && (*ch < 160))) && *ch != '\n' &&
        *ch != '\t') {
      *ch = *ch > 126 ? *ch - 128 + 64 : *ch + 64;
    }
  }
}

int check_flag_s(const SFlags *sflag, const char *last_symbol, const int *ch,
                 int *count_ent) {
  int flag = 0;
  if (sflag->s && *ch == '\n' && *last_symbol == '\n') {
    *count_ent += 1;
    if (*count_ent > 1) {
      flag = 1;
    }

  } else
    *count_ent = 0;
  return flag;
}

void check_flag_b(const char *last_symbol, const SFlags *sflag, const int *ch,
                  int *count_str) {
  if (*last_symbol == '\n' && ((sflag->b && *ch != '\n') || sflag->n)) {
    printf("%6d\t", *count_str);
    ++(*count_str);
  } else if (*last_symbol == '\n' && sflag->e && (sflag->b || sflag->n))
    printf("%6c\t", ' ');
}

int check_t_flag(const SFlags *sflag, int *ch) {
  if (sflag->t && *ch == '\t') {
    printf("^");
    *ch = 'I';
  }
  return *ch;
}

void check_flag_e(const SFlags *sflag, int ch) {
  if (sflag->e && ch == '\n') {
    printf("$");
  }
}

int main(int argc, char **argv) {
  SFlags sflag = {0};
  if (parser(argc, argv, &sflag)) {
    while (optind < argc) {
      open_file(argv, &sflag);
      optind++;
    }
  }
  return 0;
}