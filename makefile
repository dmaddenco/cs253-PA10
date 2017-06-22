all: PA10

PA10: *.cpp *.h
	g++ -I. -Wall -std=c++11 -pthread *.cpp -O3 -g -o PA10
clean:
	rm -rf *.o PA10 *.tar
tar:
	tar -cvf PA10.tar *.cpp *.h makefile
