CFLAGS = -Wall -Wextra -std=c++11

monopoly: main.o Property.o Utility.o
	g++ $^ $(CFLAGS) -o $@

main.o: main.cpp Property.hpp Utility.hpp
	g++ -c $< $(CFLAGS)
	
Property.o: Property.cpp Property.hpp
	g++ -c $< $(CFLAGS)
	
Utility.o: Utility.cpp Utility.hpp
	g++ -c $< $(CFLAGS)
	
.PHONY: clean

clean: 
	rm *.o monopoly