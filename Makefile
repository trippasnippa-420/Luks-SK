CC = g++
LIBRARIES = -lyubikey -lykpers-1
OPTS = -std=c++20 -Wall -g


thething:
	$(CC) $(OPTS) main.cpp $(LIBRARIES) -o ok-luks