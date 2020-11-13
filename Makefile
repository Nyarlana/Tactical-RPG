LINK_SFML=-lsfml-graphics -lsfml-window -lsfml-system

ifeq ($(OS),Windows_NT)
	INCLUDE= -ISFML/include
	LIB = -LSFML/lib
	LINKER_FLAGS = -lmingw32 -lsfml-main $(LINK_SFML)
else
	LINKER_FLAGS = $(LINK_SFML)
endif

all : main

main : GameManager.o
	g++ -std=c++11 -pthread $(INCLUDE) -c src/main.cpp -o obj/main.o obj/GameManager.o
	g++ -std=c++11 -pthread $(LIB) -o bin/main.exe -g obj/*.o $(LINKER_FLAGS)

GameManager.o : Component.o Observer.o ThreadContainer.o TileMap.o UI_ProgressBar.o UI_TextBox.o UI_VisualPath.o Entity.o AlienGroup.o
	g++ -std=c++11 -pthread $(INCLUDE) -c src/gameManager/GameManager.cpp -o obj/GameManager.o -g obj/Component.o obj/Observer.o obj/ThreadContainer.o obj/TileMap.o obj/UI_ProgressBar.o obj/UI_VisualPath.o obj/UI_TextBox.o obj/Entity.o obj/AlienGroup.o

Observer.o : Component.o
	g++ $(INCLUDE) -c src/gameManager/Observer.cpp -o obj/Observer.o $(LINKER_FLAGS)

Component.o :
	g++ $(INCLUDE) -c src/gameManager/Component.cpp -o obj/Component.o $(LINKER_FLAGS)

ThreadContainer.o : Entity.o
	g++ $(INCLUDE) -c src/gameManager/ThreadContainer.cpp -o obj/ThreadContainer.o -g obj/Entity.o $(LINKER_FLAGS)

TileMap.o : FileReader.o Tile.o Component.o Observer.o
	g++ $(INCLUDE) -c src/TileMap/TileMap.cpp -o obj/TileMap.o -g obj/FileReader.o obj/Tile.o obj/Component.o obj/Observer.o

FileReader.o :
	g++ $(INCLUDE) -c src/TileMap/FileReader.cpp -o obj/FileReader.o $(LINKER_FLAGS)

Tile.o :
	g++ $(INCLUDE) -c src/TileMap/Tile.cpp -o obj/Tile.o $(LINKER_FLAGS)

AlienGroup.o : Alien.o
	g++ $(INCLUDE) -c src/entities/AlienGroup.cpp -o obj/AlienGroup.o -g obj/Alien.o $(LINKER_FLAGS)

Alien.o : Fighter.o
	g++ $(INCLUDE) -c src/entities/Alien.cpp -o obj/Alien.o -g obj/Fighter.o $(LINKER_FLAGS)

Healer.o : Fighter.o
	g++ $(INCLUDE) -c src/entities/Healer.cpp -o obj/Healer.o -g obj/Fighter.o $(LINKER_FLAGS)

Tank.o : Fighter.o
	g++ $(INCLUDE) -c src/entities/Tank.cpp -o obj/Tank.o -g obj/Fighter.o $(LINKER_FLAGS)

Raider.o : Fighter.o
	g++ $(INCLUDE) -c src/entities/Raider.cpp -o obj/Raider.o -g obj/Fighter.o $(LINKER_FLAGS)

Fighter.o : Entity.o
	g++ $(INCLUDE) -c src/entities/Fighter.cpp -o obj/Fighter.o -g obj/Entity.o $(LINKER_FLAGS)

Miner.o : Entity.o
	g++ $(INCLUDE) -c src/entities/Miner.cpp -o obj/Miner.o -g obj/Entity.o $(LINKER_FLAGS)

RoverBase.o : Entity.o
	g++ $(INCLUDE) -c src/entities/RoverBase.cpp -o obj/RoverBase.o -g obj/Entity.o $(LINKER_FLAGS)

Entity.o : Component.o Observer.o
	g++ -std=c++11 -pthread $(INCLUDE) -c src/entities/Entity.cpp -o obj/Entity.o -g obj/Component.o obj/Observer.o $(LINKER_FLAGS)

UI_Component.o : Observer.o Component.o
	g++ $(INCLUDE) -c src/UI/UI_Component.cpp -o obj/UI_Component.o -g obj/Observer.o obj/Component.o $(LINKER_FLAGS)

UI_ProgressBar.o : UI_Component.o
	g++ $(INCLUDE) -c src/UI/UI_ProgressBar.cpp -o obj/UI_ProgressBar.o -g obj/UI_Component.o $(LINKER_FLAGS)

UI_VisualPath.o : UI_Component.o
	g++ $(INCLUDE) -c src/UI/UI_VisualPath.cpp -o obj/UI_VisualPath.o -g obj/UI_Component.o $(LINKER_FLAGS)

UI_TextBox.o : UI_Component.o
	g++ $(INCLUDE) -c src/UI/UI_TextBox.cpp -o obj/UI_TextBox.o -g obj/UI_Component.o $(LINKER_FLAGS)
