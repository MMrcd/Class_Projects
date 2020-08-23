# YOU NEED TO CHANGE THIS FOR LECTURER!!!
# YOU NEED TO CHANGE THIS FOR LECTURER!!!
# YOU NEED TO CHANGE THIS FOR LECTURER!!!

all: driver.o Node.o Util.o 
	g++ -Wall -std=c++11 driver.o Node.o Util.o -o Proj3.out

driver.o : driver.cpp HashedSplays.h dsexceptions.h
	g++ -Wall -std=c++11 -c driver.cpp

Node.o : Node.cpp Node.h
	g++ -Wall -std=c++11 -c Node.cpp

Util.o : Util.cpp Util.h
	g++ -Wall -std=c++11 -c Util.cpp

# -f removes any error messages if the file is not present
clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

run:
	./Proj3.out $(DATA)
