all: build/game.o build/intro.o build/termfunk.o build/main.o bin/termlink bin/PasswordTable.txt run

debug:
	CXXFLAGS += "-DDEBUG -g"
debug: all

clean:
	rm -f build/*.o bin/*

run:
	./bin/termlink

build/game.o: src/game.cpp
	$(CXX) $(CXXFLAGS) -c src/game.cpp -o build/game.o

build/intro.o: src/intro.cpp
	$(CXX) $(CXXFLAGS) -c src/intro.cpp -o build/intro.o
	
build/termfunk.o: src/termfunk.cpp
	$(CXX) $(CXXFLAGS) -c src/termfunk.cpp -o build/termfunk.o

build/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o build/main.o

bin/PasswordTable.txt: PasswordTable.txt
	cp PasswordTable.txt bin/PasswordTable.txt

bin/termlink: build/game.o build/intro.o build/termfunk.o build/main.o
	$(CXX) $(CXXFLAGS) build/*.o -o bin/termlink