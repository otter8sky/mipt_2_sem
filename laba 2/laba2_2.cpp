#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;

struct Queue {
    int* ptr = nullptr;
    size_t capacity = 100, size = 0;
    size_t read = 0, write = 0;

    Queue() {
        ptr = new int[capacity];
    }

    bool push(int element) {
        if (size == capacity) {
            size_t old_capacity = capacity;
            capacity *= 2;
            int* new_ptr = new int[capacity];

            for (size_t i = 0; i < size; ++i)
                new_ptr[i] = ptr[(read + i) % old_capacity];

            delete[] ptr;
            ptr = new_ptr;
            read = 0;
            write = size;
        }
        ptr[write] = element;
        write = (write + 1) % capacity;
        size++;
        return true;
    }

    bool poll(int& element) {
        if (size == 0)
            return false;
        element = ptr[read];
        read = (read + 1) % capacity;
        size--;
        return true;
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
    ofstream f0("push.txt");
    ofstream f1("poll.txt");

    Queue q;

    for (unsigned int n = 0; n <= 1'000; n++) {
        f0 << time([&](int val) { q.push(val); }, 1000) << '\t' << n << endl;
    }
    for (unsigned int n = 0; n <= 1'000; n++) {
        f1 << time([&](int val) { q.poll(val); }, 1000) << '\t' << n << endl;
    }
    cout << "---------OK---------" << endl;

    f0.close();
    f1.close();

    Queue que;
    que.push(2);
    que.print();
    que.push(3);
    que.print();
    que.push(4);
    que.print();
    que.push(5);
    que.print();
    que.poll();
    que.print();
    cout << "---------OK---------" << endl;


    return 0;
}