CC = g++
modules = modules/UserInputHandling.cpp modules/EuclidianHashing.cpp modules/modulo_func.cpp modules/randomness.cpp modules/CosineHashing.cpp
args = -o

lsh:
	$(CC) lsh.cpp $(modules) $(args) lsh

clean:
	rm -rf lsh