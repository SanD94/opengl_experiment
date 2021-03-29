LDLIBS = -lopengl32 -lglew32 -lfreeglut

.PHONY: clean cleanall

all: main

main: $(INIT_SHADER_OBJ)
	g++ -Wall -g -O2 main.cpp $(LDLIBS) -o main -std=c++2a


clean:
	rm main
