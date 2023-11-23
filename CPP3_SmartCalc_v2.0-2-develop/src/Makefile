..PHONY: all install uninstall clean dvi dist tests check memcheck test
CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
OS = $(shell uname -s)
GCOVFLAGS = -fprofile-arcs -ftest-coverage
SRCS = unit_tests.cc SmartCalc2/Model/calculate.cc
LC = lcov -c -d .

all: install

clean:
	rm -rf *.o *.gcno *.gcda *.info test.out
	rm -rf ./report
	rm -rf *.dSYM
	rm -rf *.gch
	rm -rf test
	rm -rf gcov_test
	rm -rf gcov_report/

rebuild: clean all

test: clean
	$(CC) $(CFLAGS) $(SRCS) -lgtest -pthread -o test
	./test

memcheck: test
ifeq ($(OS), Darwin)
	leaks -atExit -- ./test
else
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
endif


gcov_report: clean
	$(CC) $(CFLAGS) $(GCOVFLAGS) -o gcov_test -lgtest -pthread  $(SRCS)
	./gcov_test
	$(LC) -t "gcov_report" --no-external -o report.info || true
	geninfo . --ignore-errors mismatch --output-filename report.info
	genhtml -o gcov_report report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./gcov_report/index-sort-f.html

install: uninstall 
		make clean
		mkdir build
		cd SmartCalc2 && qmake && make && make clean && rm Makefile && cd ../ && mv SmartCalc2/SmartCalc2.app build

uninstall:
		rm -rf build


dist:
	rm -rf Archive_SmartCalc2/
	mkdir Archive_SmartCalc2/
	mkdir Archive_SmartCalc2/src
	mv ./build/SmartCalc2.app Archive_SmartCalc2/src/
	tar cvzf Archive_SmartCalc2.tgz Archive_SmartCalc2/
	rm -rf Archive_SmartCalc2/

dvi:
	open README_SmartCalc.md 

check:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.cc
	clang-format -n ./*/*.cc
	clang-format -n ./*/*.h
	clang-format -n ./*/*/*.cc
	clang-format -n ./*/*/*.h
	rm -rf .clang-format


