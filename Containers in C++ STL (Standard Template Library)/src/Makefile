CC = g++
FLAGS = -Wall -Wextra -g -std=c++17 -Werror
GCOV = --coverage
TEST = tests.cc
A = containers.a
O = *.o
GTEST = gtest
OS = $(shell uname)

ifeq ($(OS), Darwin)
	LIBFLAGS = -lm -lgtest -lstdc++
else
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs gtest` -lm
endif

all: clean test leaks gcov_report

test:
	$(CC) $(FLAGS) $(TEST) $(LIBFLAGS) -o $(GTEST)
	./$(GTEST)

containers.a: clean
	$(CC) $(FLAGS) -c $(TEST)
	ar rcs $(A) $(O)

gcov_report: containers.a
	$(CC) $(FLAGS) $(GCOV) $(TEST) $(A) $(LIBFLAGS) -o $(GTEST)
	./$(GTEST)
	lcov -t "./test" -o report.info --no-external -c -d . --ignore-errors mismatch
	genhtml -o report report.info
	open ./report/index.html

leaks: test
ifeq ($(OS), Darwin)
	leaks -atExit -- ./$(GTEST)
else
	CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(GTEST)
endif

style: clean
	clang-format -style=google -n $(shell find . -name "*.cc" -o -name "*.h" -o -name "*.tpp")

clean:
	rm -rf *.a  *.o *.out gtest 
	rm -rf *.info  *.gcda *.gcno -rf *.gcov -rf *dSYM
	rm -rf report/ *.