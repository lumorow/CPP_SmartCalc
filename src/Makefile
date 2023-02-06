CC = g++
CFLAG = -Wall -Wextra -Werror
UNAME:= $(shell uname -s)

ifeq ($(UNAME), Linux)
OPEN_CMD = xdg-open
ADD_LIB = -lm -lrt -lpthread -D_GNU_SOURCE
leaks_util := valgrind --leak-check=full
endif
ifeq ($(UNAME), Darwin)
OPEN_CMD = open
ADD_LIB =
leaks_util := CK_FORK=no leaks --atExit --
endif
PATH := $(PATH):$(BREW)/bin
GCOV = --coverage

all: install

install: clean
	cp -r my_calc/* build
	cd build; qmake; make; $(OPEN_CMD) my_calc.app

uninstall: clean
	rm -rf ./my_calc/my_calc.app

dvi: 
	$(OPEN_CMD) my_calc_documentation.html
	
dist:
	@rm -rf my_calc.tar.gz
	tar -czvf my_calc.tar.gz .

tests: clean
	cp -r tests/* build_tests
	cd build_tests; qmake; make; $(OPEN_CMD) tests

check: tests
	@cp -f ../materials/linters/clang-format clang-format
	@cp -f ../materials/linters/suppression.cfg suppression.cfg
	clang-format -n ./back_calc/back_calc.cpp ./controller_calc/controllerCalc.cpp ./view_calc/viewCalc.cpp
	@cp -f ../materials/linters/suppression.cfg suppression.cfg
	cppcheck --language=c++ --enable=all --suppressions-list=suppression.cfg ./back_calc/back_calc.cpp ./controller_calc/controllerCalc.cpp ./view_calc/viewCalc.cpp
	$(leaks_util) ./build_tests/tests
	@rm -f suppression.cfg
	@rm -f clang-format

clean:
	@rm -rf *.o *.gcda *.gcno *.info clang-format suppression.cfg
	@rm -rf ./build/*
	@rm -rf ./build_tests/*
	@rm -rf my_calc.tar.gz

rebuild: clean all

push:
	git add .
	git commit -m"from_make"
	git push origin develop
