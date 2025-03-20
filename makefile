all: main.exe
	@echo "Kompilacja zakończona!"

main.o : main.cpp
	@echo "Kompiluję main.cpp do main.o...
	g++ -std=c++14 -pthread -c main.cpp

main.exe: main.o
	@echo "Linkuję main.o do main.exe..."
	g++ -std=c++14 -pthread main.o -o main.exe

clean:
	@echo "Czyszczę pliki..."
	rm -f main.o main.exe
	@echo "Czyszczenie zakończone!"

run: main.exe
	@echo "Uruchamiam program z 5 filozofami..."
	./main.exe 5
