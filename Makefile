COMPONENTS = window.o shader.o camera.o model.o


all: a.out clean


a.out: main.cpp $(COMPONENTS)
	g++ -std=c++17 main.cpp $(COMPONENTS) src/glad/glad.c -lSDL2 -lassimp -Wall

window.o : Window/window.cpp
	g++ -c -std=c++17 Window/window.cpp src/glad/glad.c -lSDL2 -Wall

shader.o : Shader/shader.cpp
	g++ -c -std=c++17 Shader/shader.cpp src/glad/glad.c -Wall

camera.o : Camera/camera.cpp
	g++ -c -std=c++17 Camera/camera.cpp -Wall

model.o : Model/model.cpp
	g++ -c -std=c++17 Model/model.cpp -Wall



clean:
	rm -rf *.o
