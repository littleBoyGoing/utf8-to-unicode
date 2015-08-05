CC=gcc

default: utf8-to-unicode

utf8-to-unicode: utf8-to-unicode.c
	${CC} $+ -o $@ -g -Wall

clean:
	rm utf8-to-unicode

.PHONY: clean
