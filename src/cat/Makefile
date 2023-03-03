CC=gcc
CFLAGS=-Wall -Werror -Wextra
FILES=cat.c s21_cat.c
HEADERS=cat.h

all: rebuild linters tests leaks

s21_cat:
	$(CC) $(CFLAGS) $(FILES) -o s21_cat

linters:
	cp ../../materials/linters/.clang-format ./.clang-format && \
	clang-format -n $(FILES) $(HEADERS) && \
	rm -rf .clang-format

fix_linters:
	cp ../../materials/linters/.clang-format ./.clang-format && \
	clang-format -i $(FILES) $(HEADERS) && \
	rm -rf .clang-format

tests: s21_cat
	cd ./Linux_tests/ && \
    bash ./test_func_cat.sh

leaks: s21_cat
	cd ./Linux_tests/ && \
	bash ./test_leak_cat.sh

clean:
	rm -rf *.o s21_cat

rebuild: clean s21_cat