SRC = lab1.c
CC = gcc
DELETE = rm -rf
OUT = a.out
THREADFLAG = -lpthread
FLAGS = -Wall -Werror -Wpedantic
all:
	$(CC) $(FLAGS) $(SRC) $(THREADFLAG) 
	./$(OUT)
clear:
	$(DELETE) $(OUT) *.txt
