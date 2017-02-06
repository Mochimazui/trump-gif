
all:
	g++ `pkg-config --cflags opencv` --std=c++11 trump-gif/trump-gif.cpp trump-gif/shared.cpp `pkg-config --libs opencv`

