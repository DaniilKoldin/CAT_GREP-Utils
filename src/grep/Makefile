CC=gcc
CFLAGS=-Wall -Werror -Wextra
FILES=vector.c grep.c s21_grep.c
HEADERS=grep.h

all: rebuild linters tests leaks

s21_grep:
	$(CC) $(CFLAGS) $(FILES) -o s21_grep

linters:
	cp ../../materials/linters/.clang-format ./.clang-format && \
	clang-format -n $(FILES) $(HEADERS) && \
	rm -rf .clang-format

fix_linters:
	cp ../../materials/linters/.clang-format ./.clang-format && \
	clang-format -i $(FILES) $(HEADERS) && \
	rm -rf .clang-format

tests: s21_grep
	cd ./Linux_tests/ && \
    bash ./test_func_grep.sh

leaks: s21_grep
	cd ./Linux_tests/ && \
	bash ./test_leak_grep.sh

clean:
	rm -rf *.o s21_grep

rebuild: clean s21_grep