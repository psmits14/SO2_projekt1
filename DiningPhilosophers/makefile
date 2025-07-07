all: main.exe
	@echo "Kompilacja zakonczona!"

main.o : main.cpp
	@echo "Kompiluje main.cpp do main.o..."
	g++ -std=c++14 -pthread -c main.cpp

main.exe: main.o
	@echo "Linkuje main.o do main.exe..."
	g++ -std=c++14 -pthread main.o -o main.exe

clean:
	@echo "Czyszcze pliki..."
	rm -f main.o main.exe
	@echo "Czyszczenie zakonczone!"

run: main.exe
	@echo "Uruchamiam program z 5 filozofami..."
	./main.exe 5
