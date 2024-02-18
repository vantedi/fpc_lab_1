#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

void calculateFactorialRange(int start, int end, vector<unsigned long long>& results) {
    results[start] = factorial(start);
    for (int i = start + 1; i <= end; ++i) {
        results[i] = results[i - 1] * i;
    }
}

int main() {
    const int number = 20;
    const int numThreads = 4;
    vector<unsigned long long> results(number + 1);
    vector<thread> threads;
    int range = number / numThreads;

    //измерение времени выполнения программы для разного количества потоков
    for (int numThreads = 1; numThreads <= 4; ++numThreads) {
        auto start = high_resolution_clock::now();

        //создание потоков и их запуск
        for (int i = 0; i < numThreads; ++i) {
            int start = i * range + 1;
            int end = (i == numThreads - 1) ? number : (i + 1) * range;
            threads.emplace_back(calculateFactorialRange, start, end, ref(results));
        }

        for (auto& t : threads) {
            t.join();
        }

        auto end = high_resolution_clock::now();

        //вычисление времени выполнения программы в миллисекундах
        auto duration = duration_cast<milliseconds>(end - start);

        //вывод результатов
        setlocale(LC_ALL, "Russian");
        cout << "Количество потоков: " << numThreads << endl;
        cout << "Факториал числа - " << number << " равен " << results[number] << endl;
        cout << "Затраченное время: " << duration.count() << " миллисекунд" << endl;
        cout << "-----------------------------" << endl;
        cout << endl;

        threads.clear();
    }

    return 0;
}

