CC = g++
LIBRARIES = -lykpers-1 -lyubikey -lusb-1.0 -pthread
OPTS = -static -std=c++20 -Wall -g


thething:
	$(CC) $(OPTS) main.cpp -o ok-luks $(LIBRARIES)