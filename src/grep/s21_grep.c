#include "s21_grep.h"

void options(SFlags *sflag, String *str, int argc, char *argv[]) {
  preparation(sflag, str, argc, argv);
  if (!sflag->e && argc > optind) {
    strcat(str->str_regex, argv[optind++]);
  }
  if (sflag->e) {
    del_last_char(str->str_regex);
  }
}

void open_file(SFlags *sflag, String *str, int argc, char *argv[]) {
  if (!sflag->exit) {
    for (int i = optind; i < argc; i++) {
      FILE *file = NULL;
      file = fopen(argv[i], "r");
      if (file != NULL) {
        sflag->c_file++;
        grep(sflag, str, file, argv[i], argc);
        fclose(file);
      } else if (!sflag->s)
        printf("grep: %s: No such file or directory\n", argv[i]);
    }
  }
}

void preparation(SFlags *sflag, String *str, int argc, char *argv[]) {
  char arg_symbol;
  while ((arg_symbol = getopt_long(argc, argv, SHORT_FLAGS, NULL, NULL)) !=
         -1) {
    switch (arg_symbol) {
      case 'e':
        sflag->e = true;
        strcat(str->str_regex, optarg);
        strcat(str->str_regex, "|");
        break;
      case 'i':
        sflag->i = true;
        break;
      case 'v':
        sflag->v = true;
        break;
      case 'c':
        sflag->c = true;
        break;
      case 'l':
        sflag->l = true;
        break;
      case 'n':
        sflag->n = true;
        break;
      case 'h':
        sflag->h = true;
        break;
      case 's':
        sflag->s = true;
        break;
      default:
        printf(
            "usage: s21_grep [-ivclnsh] [-e patstern] [pattern] [file ...]\n");
        sflag->exit = true;
        break;
    }
  }
}

void option_file(SFlags *sflag, SFile *name, char *argv, int argc) {
  strcpy(name->file_name, "");
  strcpy(name->file_name_l, argv);
  strcpy(name->str_count, "");

  if (argc - optind > 1 && !sflag->h) {
    strcpy(name->file_name, argv);
    strcat(name->file_name, ":");
  }
}

void grep(SFlags *sflag, String *str, FILE *file, char *argv, int argc) {
  SFile name;
  regex_t reg;
  regmatch_t start;
  int regflag = REG_EXTENDED;
  int match_count = 0;
  int match = 0;
  int while_flag = sflag->c_file;

  option_file(sflag, &name, argv, argc);
  flag_i(sflag, &regflag);
  regcomp(&reg, str->str_regex, regflag);

  while (fgets(str->str_file, SIZE, file) && (while_flag == sflag->c_file)) {
    match = regexec(&reg, str->str_file, 1, &start, 0);
    flag_n(&name, sflag);
    flag_v(sflag, &match);
    flag_c(sflag, match, &match_count);
    flag_l(sflag, str, name, match, &while_flag);
  }
  check_flags_after_reading(sflag, name, match, match_count);
  regfree(&reg);
}

void flag_l(SFlags *sflag, String *str, SFile name, int match,
            int *while_flag) {
  if (sflag->l && !match && (sflag->c_file == *while_flag)) {
    (*while_flag)++;
  } else
    info_file(sflag, str, name, match);
}

void check_flags_after_reading(SFlags *sflag, SFile name, int match,
                               int match_count) {
  if (sflag->c) {
    printf("%s%d\n", name.file_name, match_count);
  }
  if (sflag->l && !match) {
    printf("%s\n", name.file_name_l);
  }
}

void info_file(SFlags *sflag, String *str, SFile name, int match) {
  if (!match && !sflag->c) {
    printf("%s%s%s", name.file_name, name.str_count, str->str_file);
    print_new_str(str->str_file);
  }
}

void flag_c(SFlags *sflag, int match, int *match_count) {
  if (sflag->c && !match) {
    (*match_count)++;
  }
}

void flag_v(SFlags *sflag, int *match) {
  if (sflag->v) {
    *match = !(*match);
  }
}

void flag_n(SFile *name, SFlags *sflag) {
  if (sflag->n) {
    int num = atoi(name->str_count) + 1;
    sprintf(name->str_count, "%d:", num);
  }
}

void flag_i(SFlags *sflag, int *regflag) {
  if (sflag->i) {
    *regflag = REG_EXTENDED | REG_ICASE;
  }
}

void print_new_str(char *str) {
  if (str[strlen(str) - 1] != '\n') {
    printf("\n");
  }
}

void del_last_char(char *str) { str[strlen(str) - 1] = 0; }

int main(int argc, char *argv[]) {
  SFlags sflag = {0};
  String str = {0};
  options(&sflag, &str, argc, argv);
  open_file(&sflag, &str, argc, argv);

  return 0;
}