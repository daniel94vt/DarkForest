edit: adventure.o
	cc -o edit adventure.o

adventure.o: adventure.cpp action.h actionclass.h
	cc -c adventure.cpp

.PHONY: clean
clean:
	rm edit adventure.o
