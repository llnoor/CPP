CC = g++
CPPFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++
OBJ_MODEL = model/*.cc
OBJ_CONTROLLER = controller/*.cc
OBJ_TEST = tests/test.cc
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
  	OPEN_CMD = xdg-open
	LEAKS_CMD = valgrind --tool=memcheck --leak-check=yes
	PATH_APP = SmartCalc_2/SmartCalc
	ADD_LIB = -lgtest -lpthread -lm
	GCOV_FLAGS = 
endif

ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open -a "Google Chrome"
	LEAKS_CMD = leaks -atExit --
	PATH_APP = SmartCalc_2/SmartCalc.app/Contents/MacOS/SmartCalc
	ADD_LIB = -lgtest -lm
	GCOV_FLAGS = 
endif

all: gcov_report

install:
	@rm -rf SmartCalc_2
	@mkdir SmartCalc_2
	@cd SmartCalc_2/ && qmake ../view/SmartCalc_2.pro && make -j6 && make clean && rm -rf Makefile .qmake.stash

uninstall:
	@rm -rf SmartCalc_2

dist: install
	@rm -rf dist
	@mkdir dist
	@cp -R $(PATH_APP) model view controller tests Makefile description.md dist
	@cd dist && tar cvzf SmartCalc_2.tgz * && rm -rf controller model tests view SmartCalc Makefile dvi.md
	@rm -rf SmartCalc_2

dvi:
	open description.md

tests: clean
	@$(CC) $(CPPFLAGS) $(OBJ_TEST) $(OBJ_MODEL) $(OBJ_CONTROLLER) -o test $(ADD_LIB)
	@./test

test_leaks: clean
	@$(CC) $(CPPFLAGS) $(OBJ_TEST) $(OBJ_MODEL) $(OBJ_CONTROLLER) -o test_leaks $(ADD_LIB)
	@$(LEAKS_CMD) ./test_leaks

gcov_report: clean
	@$(CC) $(CPPFLAGS) --coverage $(OBJ_TEST) $(OBJ_MODEL) $(OBJ_CONTROLLER) -o test $(ADD_LIB)
	@./test
	@rm -rf test.gcda test.gcno
	@lcov -t "test" -o SmartCalc_2.info -c -d . $(GCOV_FLAGS)
	@genhtml -o report SmartCalc_2.info
	open report/index.html

style:
	@clang-format -style=Google -n */*.h */*.cc

clean:
	@-rm -rf *.o *.gcno *.gcda *.info *.gcov *.a *.dSYM report test test_leaks main *.out
