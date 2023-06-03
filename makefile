termlink:
	g++ *.cpp -o termlink

debug:
	g++ *.cpp -DDEBUG

cleanup:
	rm *.s *.o a.out termlink