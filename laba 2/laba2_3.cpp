#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;

template <typename T> struct Queue {
    T* ptr = nullptr;
    // size_t capacity = 100, size = 0;
    size_t capacity = 3, size = 0;

    size_t read = 0, write = 0;

    Queue() {
        ptr = new T[capacity];
    }

    bool push_front(T element) {
        if (size == capacity) {
            resize();
        }
        if (read == 0) {
            read = capacity - 1;
           } else {
            read--;
           }
        ptr[read] = element;
        size++;
        return true;
    }

    bool push_back(T element) {
        if (size == capacity) {
            resize();
        }
        ptr[write] = element;
        write = (write + 1) % capacity;
        size++;
        return true;
    }

    bool poll_front() {
        if (size == 0)
            return false;
        T element = ptr[read];
        read = (read + 1) % capacity;
        size--;
        return true;
    }


    bool poll_back() {
        if (size == 0)
            return false;
        if (write == 0) {
            write = capacity - 1;
            }
        else {
            write--;
            }        
        T element = ptr[write];
        size--;
        return true;
    }

    void resize() {
        size_t old_capacity = capacity;
        capacity *= 2;
        T* new_ptr = new T[capacity];

        for (size_t i = 0; i < size; ++i)
            new_ptr[i] = ptr[(read + i) % old_capacity];

        delete[] ptr;
        ptr = new_ptr;
        read = 0;
        write = size;
    }

    void print() const {
        for (size_t i = 0; i < size; i++) {
            cout << ptr[i] << " ";
        }
        cout << endl;
    }

    ~Queue() {
        delete[] ptr;
    }
};

template <typename Func> int time(Func func, int N) {
    auto begin = chrono::steady_clock::now();
    for (int i = 0; i < N; i++) {
        func(37);
    }
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - begin).count();
}

int main() {
    // ofstream f0("3_poll_front.txt");
    // ofstream f1("3_poll_back.txt");
    // ofstream f2("3_push_back.txt");
    // ofstream f3("3_push_front.txt");

    // Queue<int> q;

    // for (unsigned int n = 0; n <= 1'000; n++) {
    //     f0 << time([&](int val) { q.poll_front(val); }, 1000) << '\t' << n << endl;
    // }
    // for (unsigned int n = 0; n <= 1'000; n++) {
    //     f1 << time([&](int val) { q.poll_back(val); }, 1000) << '\t' << n << endl;
    // }
    // for (unsigned int n = 0; n <= 1'000; n++) {
    //     f2 << time([&](int val) { q.push_back(val); }, 1000) << '\t' << n << endl;
    // }
    // for (unsigned int n = 0; n <= 1'000; n++) {
    //     f3 << time([&](int val) { q.push_front(val); }, 1000) << '\t' << n << endl;
    // }
    // cout << "---------OK---------" << endl;

    // f0.close();
    // f1.close();
    // f2.close();
    // f3.close();

    // вообще, мы что-то странное делаем, ведь функции действуют независимо... читать нечего... :(

    Queue<int> intQueue;

    cout << "Добавляем в конец:" << endl;
    intQueue.push_back(2);
    intQueue.print();
    intQueue.push_back(3);
    intQueue.print();
    intQueue.push_back(4);
    intQueue.print();

    cout << "Переполнение -> увеличиваем размер!" << endl;
    intQueue.push_back(5);
    intQueue.print();

    cout << "Читаем элементы с начала:" << endl;
    intQueue.poll_front();
    intQueue.print();

    cout << "Добавляем элементы в начало:" << endl;
    intQueue.push_front(6);
    intQueue.print();

    cout << "Читаем элементы с конца:" << endl;
    intQueue.poll_back();
    intQueue.print();
    intQueue.poll_back();
    intQueue.print();
    intQueue.poll_back();
    intQueue.print();
    intQueue.poll_back();
    intQueue.print();

    // Теперь попробуем со строками!
    Queue<string> stringQueue;

    stringQueue.push_back("УРА");
    stringQueue.push_back("лаба");
    stringQueue.push_front("кончилась!");
    stringQueue.print();

    stringQueue.poll_front();
    stringQueue.print();

    stringQueue.poll_back();
    stringQueue.print();
    
    stringQueue.poll_back();
    stringQueue.print();
    cout << "---------OK---------" << endl;

    return 0;
}