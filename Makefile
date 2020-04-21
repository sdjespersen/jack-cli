default:
	mkdir -p .build
	g++ -std=c++11 -O3 -W -Wall -Wextra -pedantic -o .build/jackc_main.o -c src/jackc_main.cpp
	g++ -std=c++11 -O3 -W -Wall -Wextra -pedantic -ljack -o jackc .build/jackc_main.o

clean:
	rm jackc
	rm -r .build
