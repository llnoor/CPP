CC = g++ -std=c++17 -g
FLAGS = -Wall -Werror -Wextra
OS = $(shell uname)
LIBSOURCES = matrix_oop.cc tests.cc

ifeq ($(OS), Linux)
	CHECKFLAGS=-lgtest -lgtest_main -lrt -lm -lstdc++ -pthread -fprofile-arcs -ftest-coverage
else
	CHECKFLAGS=-lgtest -lgtest_main -lm -lpthread -fprofile-arcs -ftest-coverage -lstdc++
endif

all: test
	
matrix_oop.a:
	$(CC) $(FLAGS) -c matrix_oop.cc
	ar -crs lib_matrix_oop.a matrix_oop.o
	rm -f *.o

test: clean
	$(CC) $(FLAGS) $(LIBSOURCES) -o run $(CHECKFLAGS) -lgcov --coverage
	./run

gcov_report: test
	lcov -t "gcov_report"  -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html

test_leaks: test
	leaks --atExit -- ./run

valgrind: test
	 CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./run
	 make clean

docker_check:
	docker build -t "valgrind:1.0" .
	docker run --rm -v $(PWD):/tmp -w /tmp valgrind:1.0

to_style:
	cp ../materials/linters/.clang-format ./
	clang-format -i ./*.cc
	clang-format -i ./*.h
	rm -rf .clang-format

style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -style=Google -n matrix_oop.* tests.cc
	rm -rf .clang-format

clean:
	rm -rf report \
	lib_matrix_oop.a \
	report.info \
	*.gcda \
	*.gcno \
	matrix_oop.o \
	run.dSYM \
	run