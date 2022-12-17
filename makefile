build:
	rm -f program.exe
	g++ -g -std=c++11 -Wall main.cpp hashmap.cpp -o program.exe
	
run:
	./program.exe

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./program.exe

a:
	rm -f program.exe
	g++ -g -std=c++11 -Wall main.cpp hashmap.cpp -o program.exe
	./program.exe
	
v:
	rm -f program.exe
	g++ -g -std=c++11 -Wall main.cpp hashmap.cpp -o program.exe
	valgrind --tool=memcheck --leak-check=yes ./program.exe