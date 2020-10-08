LINK_SFML=-lsfml-graphics -lsfml-window -lsfml-system

ifeq ($(OS),Windows_NT)
	INCLUDE= -ISFML/include
	LIB = -LSFML/lib
	LINKER_FLAGS = -lmingw32 -lsfml-main $(LINK_SFML)
else
	LINKER_FLAGS = $(LINK_SFML)
endif

all : main testTilemap

main : GameManager.o
	g++ $(INCLUDE) -c src/main.cpp -o obj/main.o obj/GameManager.o
	g++ $(LIB) -o bin/main.exe -g obj/main.o obj/GameManager.o $(LINKER_FLAGS)

testTilemap : TileMap.o
	g++ $(INCLUDE) -c src/main/testTilemap.cpp -o obj/testTilemap.o obj/TileMap.o
	g++ $(LIB) -o bin/testTilemap.exe -g obj/testTilemap.o obj/TileMap.o obj/FileReader.o obj/Tile.o $(LINKER_FLAGS)

GameManager.o : Component.o Observer.o
	g++ $(INCLUDE) -c src/gameManager/GameManager.cpp -o obj/GameManager.o -g obj/Component.o obj/Observer.o

Observer.o : Component.o
	g++ $(INCLUDE) -c src/gameManager/Observer.cpp -o obj/Observer.o $(LINKER_FLAGS)

Component.o :
	g++ $(INCLUDE) -c src/gameManager/Component.cpp -o obj/Component.o $(LINKER_FLAGS)

TileMap.o : FileReader.o Tile.o
	g++ $(INCLUDE) -c src/TileMap/TileMap.cpp -o obj/TileMap.o -g obj/FileReader.o obj/Tile.o

FileReader.o :
	g++ $(INCLUDE) -c src/TileMap/FileReader.cpp -o obj/FileReader.o $(LINKER_FLAGS)

Tile.o :
	g++ $(INCLUDE) -c src/TileMap/Tile.cpp -o obj/Tile.o $(LINKER_FLAGS)
