#makefile

main: main.o eprintf.o play.o os_priority.o 
	gcc main.o os_priority.o eprintf.o play.o -o main

eprintf.o: eprintf.h
play.o: play.h
os_priority.o: os_priority.h eprintf.h


main.o: main.c
	gcc -c main.c -o main.o


.PHONY: clean

clean:
	@echo cleaning project
	-del *.exe *.o
	@echo clean complete

