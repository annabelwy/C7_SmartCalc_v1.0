CC = -Wall -Werror -Wextra -std=c11 -pedantic
OS := $(shell uname)

ifeq ($(OS),Linux)
FLAGS = -lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
else
FLAGS = -lcheck -lm -lpthread -fprofile-arcs -ftest-coverage
endif

all: clean s21_parser.a uninstall install gcov_report

open:
	open ./build/calc.app

install:
	make clean
	mkdir build
	cd calc && qmake && make && make clean && rm Makefile && cd ../ && mv Calc/Calc.app build

uninstall:
	rm -rf build*

dist:
	rm -rf Archive_Calc_v1.0/
	mkdir Archive_Calc_v1.0/
	mkdir Archive_Calc_v1.0/src
	mv ./build/Calc.app Archive_Calc_v1.0/src/
	tar cvzf Archive_Calc_v1.0.tgz Archive_Calc_v1.0/
	rm -rf Archive_Calc_v1.0/

dvi:
	open description.md

clean:
	rm -rf *.o *.a unit_test
	rm -rf *.gcno *gcda *.gcov gcov
	rm -rf report report.info
	rm -rf *.dSYM

test: clean s21_parser.a
	gcc unit_test.c s21_parser.a $(FLAGS) -o unit_test
	./unit_test

gcov_report: clean
	gcc unit_test.c s21_parser.c $(FLAGS) -o unit_test
	./unit_test
	lcov -t "./unit_test" -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html
	rm -rf *.gcno *gcda *.gco

s21_parser.a:
	gcc $(CC)  -c s21_parser.c
	ar -crs s21_parser.a s21_parser.o 

clang:
	cp ../materials/linters/.clang-format ./
	cp ../materials/linters/.clang-format ./calc/
	clang-format -n *.c *.h
	clang-format -n ./calc/*.cpp ./calc/*.h
	rm -rf .clang-format
	rm -rf ./calc/.clang-format

leak: test
	leaks --atExit -- ./unit_test
	leaks --atExit -- open ./build/calc.app