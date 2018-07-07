
all: a.out clean


a.out: main.cpp window.o shader.o
	g++ -std=c++17 main.cpp window.o shader.o src/glad/glad.c -lSDL2

window.o : Window/window.cpp Window/window.h
	g++ -c -std=c++17 Window/window.cpp src/glad/glad.c -lSDL2

shader.o : Shader/shader.cpp Shader/shader.h
	g++ -c -std=c++17 Shader/shader.cpp src/glad/glad.c



clean:
	rm -rf *.o
