CXX=g++

Forest: action.o main.o authentication.o
<<<<<<< HEAD
        ${CXX} action.o main.o authentication.o -o Forest

action.o: action.cpp action.h
        ${CXX} -c $<

main.o: main.cpp action.h authentication.h
        ${CXX} -c $<

authentication.o: authentication.cpp authentication.h
        ${CXX} -c $<

.PHONY: clean
clean:
        rm Forest authentication.o main.o action.o

=======
	${CXX} action.o main.o authentication.o -o Forest

action.o: action.cpp action.h
	${CXX} -c $<

main.o: main.cpp action.h authentication.h
	${CXX} -c $<

authentication.o: authentication.cpp authentication.h
	${CXX} -c $<

.PHONY: clean
clean:
	rm Forest authentication.o main.o action.o
>>>>>>> 16856cd61e51943d93fd9127140280c93844964f
