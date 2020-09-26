INCLUDE = -ISFML/include
LIB = -LSFML/lib
LINK_SFML = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main

ifeq ($(OS),Windows_NT)
	LINKER_FLAGS = -lmingw32 $(LINK_SFML)
else
	LINKER_FLAGS = $(LINK_SFML)
endif

all : GameManager.o
	g++ $(INCLUDE) -c src/main.cpp -o obj/main.o obj/GameManager.o
	g++ $(LIB) -o bin/main.exe -g obj/main.o obj/GameManager.o $(LINKER_FLAGS)

GameManager.o :
	g++ $(INCLUDE) -c src/gameManager/gameManager.cpp -o obj/GameManager.o
