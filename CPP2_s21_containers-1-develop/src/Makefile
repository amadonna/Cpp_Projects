.PHONY: all test gcov_report check rebuild clean memcheck
CC = gcc -lstdc++
CFLAGS = -Wall -Werror -Wextra -std=c++17
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LC = lcov -c -d .
OS = $(shell uname -s)

all: art gcov_report

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
	$(CC) $(CFLAGS) $(GCOVFLAGS) -o test -lgtest -pthread unit_tests.cc
	./test

memcheck: test
ifeq ($(OS), Darwin)
	leaks -atExit -- ./test
else
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
endif

gcov_report: clean test
	$(LC) -t "gcov_report" --no-external -o report.info
	genhtml -o gcov_report --prefix src report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov test
	open ./gcov_report/index-sort-l.html

check:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.cc
	clang-format -n *.h
	clang-format -n ./*/*/*.tpp
	clang-format -n ./*/*/*.h
	rm -rf .clang-format

art:
	@for i in {0..4} ; \
	do                                      \
		sleep 0.2;\
		clear;\
		for y in {233..233} {52..52} {52..52} {88..88} {124..124} {124..124} {124..124} {124..124} {88..88} {52..52} {52..52} {233..233}; \
		do \
			printf "\033[48;5;$${y}m        \033[0m" ;\
		done ; echo ;                              \
		((i = i*6*6 + 16)) ; \
		echo ; \
		echo "    \033[38;5;$${i}m ▄████▄   ▒█████   ███▄    █ ▄▄▄█████▓ ▄▄▄       ██▓ ███▄    █ ▓█████  ██▀███    ██████ \033[0m";\
		echo "    \033[38;5;$${i}m▒██▀ ▀█  ▒██▒  ██▒ ██ ▀█   █ ▓  ██▒ ▓▒▒████▄    ▓██▒ ██ ▀█   █ ▓█   ▀ ▓██ ▒ ██▒▒██    ▒ \033[0m";\
		echo "    \033[38;5;$${i}m▒▓█    ▄ ▒██░  ██▒▓██  ▀█ ██▒▒ ▓██░ ▒░▒██  ▀█▄  ▒██▒▓██  ▀█ ██▒▒███   ▓██ ░▄█ ▒░ ▓██▄   \033[0m";\
		echo "    \033[38;5;$${i}m▒▓▓▄ ▄██▒▒██   ██░▓██▒  ▐▌██▒░ ▓██▓ ░ ░██▄▄▄▄██ ░██░▓██▒  ▐▌██▒▒▓█  ▄ ▒██▀▀█▄    ▒   ██▒\033[0m";\
		echo "    \033[38;5;$${i}m▒ ▓███▀ ░░ ████▓▒░▒██░   ▓██░  ▒██▒ ░  ▓█   ▓██▒░██░▒██░   ▓██░░▒████▒░██▓ ▒██▒▒██████▒▒\033[0m";\
		((i = (i - 16)/6/6)) ; \
		((i = i*2 + 232)) ; \
		echo "    \033[38;5;$${i}m░ ░▒ ▒  ░░ ▒░▒░▒░ ░ ▒░   ▒ ▒   ▒ ░░    ▒▒   ▓▒█░░▓  ░ ▒░   ▒ ▒ ░░ ▒░ ░░ ▒▓ ░▒▓░▒ ▒▓▒ ▒ ░\033[0m";\
		echo "    \033[38;5;$${i}m  ░  ▒     ░ ▒ ▒░ ░ ░░   ░ ▒░    ░      ▒   ▒▒ ░ ▒ ░░ ░░   ░ ▒░ ░ ░  ░  ░▒ ░ ▒░░ ░▒  ░ ░\033[0m";\
		echo "    \033[38;5;$${i}m░        ░ ░ ░ ▒     ░   ░ ░   ░        ░   ▒    ▒ ░   ░   ░ ░    ░     ░░   ░ ░  ░  ░  \033[0m";\
		echo "    \033[38;5;$${i}m░ ░          ░ ░           ░                ░  ░ ░           ░    ░  ░   ░           ░  \033[0m";\
		echo "    \033[38;5;$${i}m░                                                                                       \033[0m";\
		echo ; \
		for y in {233..233} {52..52} {52..52} {88..88} {124..124} {124..124} {124..124} {124..124} {88..88} {52..52} {52..52} {233..233};             \
		do                                  \
			printf "\033[48;5;$${y}m        \033[0m" ;\
		done ; echo ;                              \
	done
