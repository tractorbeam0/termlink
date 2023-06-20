termlink:
	g++ *.cpp -o termlink

debug:
	g++ *.cpp -g -DDEBUG
	./a.out

clean:
	rm *.s *.o a.out termlink