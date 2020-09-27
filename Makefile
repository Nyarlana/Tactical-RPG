INCLUDE = -ISFML/include
LIB = -LSFML/lib
LINK_SFML = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main

ifeq ($(OS),Windows_NT)
	LINKER_FLAGS = -lmingw32 $(LINK_SFML)
else
	LINKER_FLAGS = $(LINK_SFML)
endif

all :
	g++ $(INCLUDE) -c src/main.cpp -o obj/main.o
	g++ $(LIB) -o bin/main.exe obj/main.o $(LINKER_FLAGS)
