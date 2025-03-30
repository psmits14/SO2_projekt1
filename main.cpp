#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>
#include <string>

using namespace std;

struct Fork {
    mutex mtx;
};

struct Philosopher {
    int id;
    Philosopher(int _id) : id(_id) {}   // Constructor
};

class DiningPhilosophers {
private:
    int num_philosophers;
    vector<Fork> forks;                          // Vector of forks, one between each philosopher
    vector<Philosopher> philosophers;            // Vector of philosopher objects
    vector<thread> philosopher_threads;          // Threads for each philosopher
    mutex cout_mutex;                            // Mutex to synchronize cout

public:
    // Constructor initializes philosophers and forks
    DiningPhilosophers(int n) : num_philosophers(n), forks(n) {         
        for (int i = 0; i < num_philosophers; i++) {
            philosophers.emplace_back(i);
        }
    }

    void philosopher(int id) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(1, 1000);

        while (true) {
            // Thinking
            {
                lock_guard<mutex> lock(cout_mutex);
                cout << "Philosopher " << id << ": Thinking..." << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(dist(gen)));

             // Determine left and right forks
            int left_fork = id;
            int right_fork = (id + 1) % num_philosophers;

            // Preventing deadlock (asymmetric fork pickup)
            if (id % 2 == 0) {
                forks[left_fork].mtx.lock();
                forks[right_fork].mtx.lock();
            } else {
                forks[right_fork].mtx.lock();
                forks[left_fork].mtx.lock();
            }

            // Eating
            {
                lock_guard<mutex> lock(cout_mutex);
                cout << "Philosopher " << id << ": Eating." << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(dist(gen)));

            // Putting down forks
            forks[left_fork].mtx.unlock();
            forks[right_fork].mtx.unlock();
        }
    }

     // Starts the simulation by launching philosopher threads
    void start() {
        for (int i = 0; i < num_philosophers; i++) {
            philosopher_threads.emplace_back(&DiningPhilosophers::philosopher, this, i);    
        }

        // Wait for all philosopher threads to finish (in practice, they run infinitely)
        for (auto& p : philosopher_threads) {
            p.join();                               
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <number of philosophers>" << endl;
        return 1;
    }

    int num_philosophers = stoi(argv[1]);
    
    if (num_philosophers < 2) {
        cerr << "At least 2 philosophers are needed to start the simulation." << endl;
        return 1;
    }
    
    DiningPhilosophers dp(num_philosophers);  // Create simulation instance
    cout << "Dinner is served!" << endl;
    dp.start();

    return 0;
}
