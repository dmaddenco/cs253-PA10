all: PA10

PA10: *.cpp *.h
	g++ -I. -Wall -std=c++11 *.cpp -g -o PA10
clean:
	rm -rf *.o PA10 *.tar
tar:
	tar -cvf PA10.tar *.cpp *.h makefile
