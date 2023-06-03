termlink:
	g++ main.cpp *.cpp -o termlink

clean:
	@if [ -x "termlink" ]; then\
		rm termlink;\
	else\
		echo "Nothing to clean up";\
	fi