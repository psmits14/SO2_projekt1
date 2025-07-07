# Problem jedzących filozofów
**Projekt 1** realizowany w ramach przedmiotu **Systemy Operacyjne 2** na **Politechnice Wrocławskiej**.  
Celem projektu jest implementacja rozwiązania klasycznego problemu synchronizacji – **problemu jedzących filozofów** – z wykorzystaniem języka C++ oraz wielowątkowości.

## Opis problemu

Problem jedzących filozofów to klasyczny problem synchronizacji w programowaniu współbieżnym, zilustrowany jako pięciu (lub więcej) filozofów siedzących przy okrągłym stole.  

Przed każdym z filozofów znajduje się talerz, a między każdymi dwoma talerzami – widelec. Filozofowie na przemian **myślą** i **jedzą**. Aby filozof mógł jeść, musi jednocześnie posiadać **dwa widelce** – ten po lewej i ten po prawej stronie. Po zakończeniu jedzenia, odkłada oba widelce i wraca do myślenia.

Problem polega na zaprojektowaniu algorytmu, który umożliwi filozofom jedzenie i myślenie bez ryzyka wystąpienia:

- **Zakleszczenia (deadlock)** – wszyscy filozofowie trzymają jeden widelec i czekają na drugi, przez co żaden z nich nie może jeść.
- **Zagłodzenia (starvation)** – jeden z filozofów nigdy nie dostaje obu widelców, ponieważ inni zabierają je wcześniej.


## Opis rozwiązania

Program wykorzystuje:

- Wątki (`std::thread`) – każdy filozof działa jako osobny wątek.
- Muteksy (`std::mutex`) – reprezentujące widelce (obiekt Fork).

### Przebieg działania:

1. Filozof **myśli** przez losowy czas.
2. Następnie próbuje **zabrać dwa widelce** (mutexy), by móc jeść.
3. Po zjedzeniu, **odkłada widelce** i ponownie zaczyna myśleć.

### Zapobieganie zakleszczeniu

W celu uniknięcia zakleszczenia zastosowano **strategię asymetrycznego podnoszenia widelców**:

- Filozofowie o **parzystym ID** najpierw podnoszą **lewy widelec**, potem **prawy**.
- Filozofowie o **nieparzystym ID** najpierw podnoszą **prawy widelec**, potem **lewy**.

Dzięki tej strategii przynajmniej jeden z filozofów zawsze będzie mógł zająć oba widelce i jeść, co eliminuje możliwość zakleszczenia.



## Instrukcja uruchomienia


### 1. Aby uruchomić projekt lokalnie, najpierw sklonuj repozytorium:

```bash
git clone https://github.com/psmits14/SO2_projekt1.git
cd SO2_projekt1
```

> Alternatywnie możesz pobrać projekt jako `.zip` i rozpakować go lokalnie.



### 2. Skompiluj program


Projekt zawiera gotowy plik `makefile`, dlatego zalecane jest użycie komendy:

```bash
make
```

Po poprawnej kompilacji pojawi się plik wykonywalny `main`. Jeśli wolisz, możesz również skompilować program ręcznie:

```bash
g++ -std=c++14 -pthread main.cpp -o main
```


### 3. Uruchamianie symulacji

Aby uruchomić symulację, podaj liczbę filozofów jako argument:

```bash
./main <liczba_filozofów>
```

Możesz również uruchomić program z domyślną wartością 5 filozofów poleceniem:

```bash
make run
```

