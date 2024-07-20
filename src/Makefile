.PHONY: all clean default install uninstall dvi dist tests check clean rebuild gcov_report

CC=gcc
OS := $(shell uname -s)

default: all

all: clean install

install:
	gcc main.c s21_smartCalc.c -o calculator -lm `pkg-config --cflags --libs gtk+-3.0`

uninstall:
	rm -f calculator

dvi:
	cd doc && texi2dvi doc.texi && cd ..

pdf:
	cd doc && texi2pdf doc.texi && cd ..

dist:
	tar --totals -cvf dist/archive.tar .

tests:
ifeq ($(OS), Darwin)
	$(CC) -o test test.c s21_smartCalc.c -lcheck
else
	$(CC) -o test test.c s21_smartCalc.c -lcheck -lm -lsubunit -lrt -lpthread
endif
	./test

gcov_report:
ifeq ($(OS), Darwin)
	$(CC) --coverage -o testresult test.c s21_smartCalc.c -lcheck
else
	$(CC) --coverage -o testresult test.c s21_smartCalc.c -lcheck -lm -lsubunit -lrt -lpthread
endif
	./testresult
	lcov -t "testresult" -o testresult.info -c -d .
	genhtml -o report testresult.info
 
test:
	gcc -o calculator main.c s21_smartCalc.c -lm `pkg-config --cflags --libs gtk+-3.0`
	./calculator

clean:
	rm -Rf *.cfg calculator test testresult* report test.gcda test.gcno s21_smartCalc.gc* dist/*.tar
	rm -f doc/*.dvi doc/*.cps doc/*.cp doc/*.aux doc/*.log doc/*.toc doc/*.pdf
 
rebuild: clean all