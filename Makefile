CFLAGS = -Wall -Wextra -std=c++11

monopoly: main.o Property.o Utility.o Railroad.o Board.o Card.o ActionSpace.o Game.o Player.o
	g++ $^ $(CFLAGS) -o $@

main.o: main.cpp Property.hpp Utility.hpp Railroad.hpp Card.hpp
	g++ -c $< $(CFLAGS)
	
Property.o: Property.cpp Property.hpp
	g++ -c $< $(CFLAGS)
	
Utility.o: Utility.cpp Utility.hpp Space.hpp
	g++ -c $< $(CFLAGS)
	
Railroad.o: Railroad.cpp Railroad.hpp
	g++ -c $< $(CFLAGS)
	
Card.o: Card.cpp Card.hpp
	g++ -c $< $(CFLAGS)

Space.o: Space.cpp Space.hpp
	g++ -c $< $(CFLAGS)
	
ActionSpace.o: ActionSpace.cpp ActionSpace.hpp Space.hpp
	g++ -c $< $(CFLAGS)
	
Player.o: Player.cpp Player.hpp
	g++ -c $< $(CFLAGS)

Board.o: Board.cpp Board.hpp Utility.hpp Railroad.hpp Card.hpp ActionSpace.hpp
	g++ -c $< $(CFLAGS)
	
Game.o: Game.cpp Game.hpp Board.hpp Player.hpp
	g++ -c $< $(CFLAGS)
	
.PHONY: clean

clean: 
	rm *.o monopoly
