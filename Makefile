LINK_SFML=-lsfml-graphics -lsfml-window -lsfml-system

ifeq ($(OS),Windows_NT)
	INCLUDE= -ISFML/include
	LIB = -LSFML/lib
	LINKER_FLAGS = -lmingw32 -lsfml-main $(LINK_SFML)
else
	LINKER_FLAGS = $(LINK_SFML)
endif

all : GameManager.o
	g++ $(INCLUDE) -c src/main.cpp -o obj/main.o obj/GameManager.o
	g++ $(LIB) -o bin/main.exe -g obj/main.o obj/GameManager.o $(LINKER_FLAGS)

GameManager.o : Component.o Observer.o
	g++ $(INCLUDE) -c src/gameManager/gameManager.cpp -o obj/GameManager.o -g obj/Component.o obj/Observer.o

Component.o :
	g++ $(INCLUDE) -c src/gameManager/component.cpp -o obj/Component.o $(LINKER_FLAGS)

Observer.o :
	g++ $(INCLUDE) -c src/gameManager/Observer.cpp -o obj/Observer.o $(LINKER_FLAGS)
