default:
	mkdir -p .build
	g++ -std=c++11 -O3 -W -Wall -Wextra -pedantic -o .build/jmess_main.o -c src/jmess_main.cpp
	g++ -std=c++11 -O3 -W -Wall -Wextra -pedantic -ljack -o jmess .build/jmess_main.o

clean:
	rm jmess
	rm -r .build
