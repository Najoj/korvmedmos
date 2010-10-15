LIBS=-lboost_system -lpthread
OBJ=main.o rules.o
FLAGS=-O3 -p

all: main
main: $(OBJ)
	g++ -Wall $(FLAGS) $(LIBS) $(OBJ) -o $@
main.o: main.cpp node.hpp
	g++ -c $(FLAGS) main.cpp
rules.o: rules.cpp boxlocks.hpp
	g++ -c $(FLAGS) rules.cpp
clean:
	rm main *.o
force: clean all
