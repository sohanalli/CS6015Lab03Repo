CXX=c++
CFLAGS= -std=c++17
CXXSOURCE= cmdline.cpp  main.cpp expr.cpp testing.cpp
OBJS = main.o cmdline.o expr.o testing.o
HEADERS= cmdline.hpp expr.hpp
CCOMPILE = -c
CLINK = -o
msdscript: $(OBJS)
	$(CXX) $(CFLAGS) main.o cmdline.o expr.o testing.o -o msdscript
main.o: main.cpp
	c++ -std=c++17 -c main.cpp
testing.o: testing.cpp
	c++ -std=c++17 -c testing.cpp
cmdline.o: cmdline.cpp cmdline.h catch.h
	c++ -std=c++17 -c cmdline.cpp
expr.o: expr.h catch.h
	c++ -std=c++17 -c expr.cpp
clean:
	rm -f *.o msdscript
.PHONY: test
test: msdscript
	./msdscript --test








