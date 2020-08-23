# YOU NEED TO CHANGE THIS FOR LECTURER!!!
# YOU NEED TO CHANGE THIS FOR LECTURER!!!
# YOU NEED TO CHANGE THIS FOR LECTURER!!!

all: driver.o AugmentedBinarySearchTree.o 
	g++ -Wall -std=c++11 driver.o AugmentedBinarySearchTree.o -o Proj2.out

driver.o : driver.cpp Proj2Aux.h AugmentedBinarySearchTree.h
	g++ -Wall -std=c++11 -c driver.cpp

AugmentedBinarySearchTree.o : AugmentedBinarySearchTree.cpp AugmentedBinarySearchTree.h
	g++ -Wall -std=c++11 -c AugmentedBinarySearchTree.cpp

# -f removes any error messages if the file is not present
clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

run:
	./Proj2.out $(FILE) $(COMMANDS) 2>error.txt
