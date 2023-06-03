termlink:
	g++ *.cpp -o termlink

clean:
	@if [ -x "termlink" ]; then\
		rm termlink;\
	fi