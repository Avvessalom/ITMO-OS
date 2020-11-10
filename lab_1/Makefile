SRC = lab1.c
CC = gcc
DELETE = rm -rf
OUT = a.out
THREADFLAG = -lpthread
all:
	$(CC) -Wall -Werror -Wpedantic $(SRC) $(THREADFLAG) 
	./$(OUT)
clear:
	$(DELETE) $(OUT) *.txt
