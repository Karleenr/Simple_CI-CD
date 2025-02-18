CCFLAGS= gcc -Wall -Werror -Wextra -std=c11
CAT= s21_cat.c

all: s21_cat 

s21_cat: clean
	$(CCFLAGS) $(CAT) -o s21_cat

test: clean s21_cat
	bash test_s21_cat.sh

clang:
	clang-format -style=Google -n -Werror *.c
	clang-format -style=Google -n -Werror *.h

clean:
	rm -rf *.log s21_cat

rebuild:
	make clean
	make all
