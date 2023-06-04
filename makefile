termlink:
	g++ *.cpp -o termlink

debug:
	g++ *.cpp -g -DDEBUG

cleanup:
	rm *.s *.o a.out termlink