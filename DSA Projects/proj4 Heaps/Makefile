#
all: Driver.o PinHit.o Heap.o 
	g++ -Wall -std=c++11 Driver.o PinHit.o Heap.o -o Proj4.out

Driver.o : Driver.cpp PinHit.h Heap.h MinHeap.h MaxHeap.h
	g++ -Wall -std=c++11 -c Driver.cpp

PinHit.o : PinHit.cpp PinHit.h
	g++ -Wall -std=c++11 -c PinHit.cpp

Heap.o : Heap.cpp Heap.h
	g++ -Wall -std=c++11 -c Heap.cpp

# -f removes any error messages if the file is not present
clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

run:
	./Proj4.out $(FILE) $(TYPE)
