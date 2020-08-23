proj1: Driver.o Llama.o LlamaNode.o
	g++ -Wall -std=c++11 -o proj1 Driver.o Llama.o LlamaNode.o

Driver.o: Driver.cpp Llama.h
	g++ -Wall -std=c++11 -c Driver.cpp

Llama.o: Llama.cpp Llama.h LlamaNode.h
	g++ -Wall -std=c++11 -c Llama.cpp

LlamaNode.o: LlamaNode.cpp LlamaNode.h
	g++ -Wall -std=c++11 -c LlamaNode.cpp

clean: 
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

run:
	./proj1