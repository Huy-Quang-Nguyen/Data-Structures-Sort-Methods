compile:
	g++ -c -Wall -std=c++1y -pedantic-errors -g -O0 main.cpp
	g++ -o main main.cpp

run ordered:
	./main ordered.txt

run reverse:
	./main reverse.txt

run random:
	./main random.txt

clean:
	rm main.o
