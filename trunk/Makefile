LIBS=-lboost_system -lpthread
OBJ=main.o rules.o
FLAGS=-O3 -p
NAME=sokoban

all: main
main: $(OBJ)
	g++ -Wall $(FLAGS) $(LIBS) $(OBJ) -o $(NAME)
main.o: main.cpp node.hpp
	g++ -c $(FLAGS) main.cpp
rules.o: rules.cpp boxlocks.hpp
	g++ -c $(FLAGS) rules.cpp
clean:
	rm $(NAME) *.o
force: clean all
