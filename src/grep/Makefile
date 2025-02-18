CCFLAGS= gcc -Wall -Werror -Wextra -std=c11
GREP= s21_grep.c

all: s21_grep

s21_grep: clean
	$(CCFLAGS) $(GREP) -o s21_grep

test: clean s21_grep
	bash test_s21_grep.sh

clang:
	clang-format -style=Google -n -Werror *.c
	clang-format -style=Google -n -Werror *.h

clean:
	rm -rf *.log s21_grep

rebuild:
	make clean
	make all
