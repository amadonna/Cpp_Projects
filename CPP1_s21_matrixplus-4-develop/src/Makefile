.PHONY: all s21_matrix_oop.a test gcov_report check rebuild clean test.o memcheck
CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
GCOVFLAGS =  -fprofile-arcs -ftest-coverage
LC = lcov -c -d .
C_FILES = s21_matrix_oop.cc
O_FILES = s21*.o
OS=$(shell uname -s)

all : s21_matrix_oop.a
clean :
	rm -rf *.o *.gcno *.gcda *.info test.out s21_matrix_oop.a
	rm -rf ./report
	rm -rf *.dSYM
	rm -rf *.gch
	rm -rf test
	rm -rf gcov_test
	rm -rf gcov_report/

rebuild : clean all

$(O_FILES) :
	$(CC) $(CFLAGS) -c $(C_FILES) s21_matrix_oop.h
test.o :
	$(CC) $(CFLAGS) -c -lgtest -pthread unit_tests.cc
s21_matrix_oop.a :
	$(CC) $(CFLAGS) -c $(C_FILES)
	ar r s21_matrix_oop.a $(O_FILES)

test: clean s21_matrix_oop.a
	$(CC) $(FLAGS) unit_tests.cc s21_matrix_oop.a -lgtest -pthread -o test
	./test

memcheck: test
ifeq ($(OS), Darwin)
	leaks -atExit -- ./test
else
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
endif

gcov_report : clean
	$(CC) $(CFLAGS) $(GCOVFLAGS) -o gcov_test -lgtest -pthread $(C_FILES) unit_tests.cc
	./gcov_test
	$(LC) -t "gcov_report" --no-external -o report.info
	genhtml -o gcov_report report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./gcov_report/index-sort-f.html

check:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.cc
	clang-format -n *.h
	rm -rf .clang-format