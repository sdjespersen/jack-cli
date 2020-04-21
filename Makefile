default: src/jackc_main.cpp src/JackCli.cpp src/JackCli.h
	g++ -std=c++17 -O3 -W -Wall -Wextra -pedantic -ljack -o jackc src/jackc_main.cpp

