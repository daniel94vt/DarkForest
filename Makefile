CXX=g++

Forest: adventure.o
	${CXX} -o Forest $<

adventure.o: adventure.cpp actionclass.h action.h
	${CXX} -c -o $@ $<

.PHONY: clean
clean:
	rm Forest adventure.o
