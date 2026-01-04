CC = g++
FLAGS = -O3 -Iinclude
INC_SFML_FLAG = -lsfml-system -lsfml-window -lsfml-graphics
OBJS = src/Animation.o \
	   src/Assets.o \
	   src/Entity.o \
	   src/EntityManager.o \
	   src/GameEngine.o \
	   src/main.o \
	   src/Scene.o \
	   src/SceneMenu.o \
	   src/ScenePlay.o \
	   src/Vec2.o

game.out : $(OBJS)
	${CC} $^ -o $@ ${INC_SFML_FLAG}

src/EntityManager.o : src/EntityManager.cpp
	${CC} ${FLAGS}  -c $^ -o $@ 

src/Animation.o : src/Animation.cpp 
	${CC} ${FLAGS}  -c $^ -o $@

src/Assets.o : src/Assets.cpp 
	${CC} ${FLAGS}  -c $^ -o $@

src/Scene.o : src/Scene.cpp 
	${CC} ${FLAGS}  -c $^ -o $@

src/SceneMenu.o : src/SceneMenu.cpp 
	${CC} ${FLAGS}  -c $^ -o $@

src/ScenePlay.o : src/ScenePlay.cpp 
	${CC} ${FLAGS}  -c $^ -o $@

src/Entity.o : src/Entity.cpp 
	${CC} ${FLAGS}  -c $^ -o $@

src/Vec2.o : src/Vec2.cpp
	${CC} ${FLAGS}  -c $^ -o $@

src/GameEngine.o : src/GameEngine.cpp
	${CC} ${FLAGS}  -c $^ -o $@

src/main.o : src/main.cpp
	${CC} ${FLAGS}  -c $^ -o $@

clean :
	rm -f src/*.o game.out
