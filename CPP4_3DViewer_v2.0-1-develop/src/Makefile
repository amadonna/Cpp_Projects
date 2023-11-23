..PHONY: all install uninstall clean dvi dist tests check memcheck test
CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
OS = $(shell uname -s)
GCOVFLAGS = -fprofile-arcs -ftest-coverage
SRCS = unit_test/unit_tests.cc  model/*.cc model/**/*.cc
LC = lcov -c -d .
LIBS=-lgtest
LINUX=-lgtest -lm -lpthread -lrt


all: install

clean:
	rm -rf *.o *.gcno *.gcda *.info test.out
	rm -rf ./report
	rm -rf *.dSYM
	rm -rf *.gch
	rm -fr test
	rm -rf gcov_test
	rm -rf gcov_report/

rebuild: clean all

test: clean
	$(CC) $(CFLAGS) $(SRCS) -lgtest -pthread -o test
	./test

tests: test

memcheck: test
ifeq ($(OS), Darwin)
	leaks -atExit -- ./test
else
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
endif


gcov_report: clean 
ifeq ($(OS), Darwin)
	$(CC) $(GCOVFLAGS) $(CFLAGS) $(SRCS) -o report.out $(LIBS)
else
	$(CC) $(GCOVFLAGS) $(CFLAGS) $(SRCS) -o report.out $(LINUX)
endif
	./report.out
	lcov -t "gcov_report" --ignore-errors mismatch -o report.info --no-external -c -d .
	genhtml -o report/ report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index.html

install:
	make clean
	rm -fr build
	mkdir build
	cd view/3d_viewer && qmake && make && make clean && rm Makefile && cd ../../ && mv view/3d_viewer/3dv.app build
	open build/3dv.app

uninstall:
	rm -rf build*


dist:
	rm -rf Archive_3dv/
	mkdir Archive_3dv/
	mkdir Archive_3dv/src
	mv ./build/3dv.app Archive_3dv/src/
	tar cvzf Archive_3dv.tgz Archive_3dv/
	rm -rf Archive_3dv/

dvi:
	open readme_3dviewer.md 

check:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.cc
	clang-format -n ./*/*.cc
	clang-format -n ./*/*.h
	clang-format -n ./*/*/*.cc
	clang-format -n ./*/*/*.h
	rm -rf .clang-format



