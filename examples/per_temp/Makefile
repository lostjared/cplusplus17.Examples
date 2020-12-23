all:
	g++ -std=c++17 per.cpp -c -o per.o
	g++ -std=c++17 main.cpp -c -o main.o
	g++ per.o main.o -o per.test
clean:
	rm -f *.o per.test
