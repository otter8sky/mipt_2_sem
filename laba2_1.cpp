#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;

struct Linear_allocator {
    int* ptr = nullptr;
    size_t size = 0;

    void add(int val) {
        int* new_ptr = new int[size + 1];
        for (size_t i = 0; i < size; i++) {
            new_ptr[i] = ptr[i];
        }
        new_ptr[size] = val;
        size++;
        delete[] ptr;
        ptr = new_ptr;
    }

    void print() const {
        for (size_t i = 0; i < size; i++) {
            cout << ptr[i] << " ";
        }
        cout << endl;
    }

    ~Linear_allocator() {
        delete[] ptr;
    }
};

struct Block_allocator {

    int* ptr = nullptr;
    size_t block_size = 100, size = 0;
    size_t cur_block_size = 100;

    Block_allocator() {
        ptr = new int[block_size];
    }

    void add(int val) {
        if (size == cur_block_size) {
            cur_block_size += block_size;
            int* new_ptr = new int[cur_block_size];
            for (size_t i = 0; i < size; ++i) {
                new_ptr[i] = ptr[i];
            }
            delete[] ptr;
            ptr = new_ptr;
        }
        ptr[size++] = val;
    }

    void print() const {
        for (size_t i = 0; i < size; i++) {
            cout << ptr[i] << " ";
        }
        cout << endl;
    }

    ~Block_allocator() {
        delete[] ptr;
    }
};

struct Exp_allocator {

    int* ptr = nullptr;
    size_t block_size = 100, size = 0;

    Exp_allocator() {
        ptr = new int[block_size];
    }

    void add(int val) {
        if (size >= block_size) {
            block_size *= 2;
            int* new_ptr = new int[block_size];
            for (size_t i = 0; i < size; ++i) {
                new_ptr[i] = ptr[i];
            }
            delete[] ptr;
            ptr = new_ptr;
        }
        ptr[size++] = val;
    }

    void print() const {
        for (size_t i = 0; i < size; i++) {
            cout << ptr[i] << " ";
        }
        cout << endl;
    }

    ~Exp_allocator() {
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
    ofstream f0("1_strategy_1.txt");
    ofstream f1("1_strategy_2.txt");
    ofstream f2("1_strategy_3.txt");

    Linear_allocator lin;
    Block_allocator blc;
    Exp_allocator exp;

    for (unsigned int n = 0; n <= 1'000; n++) {
        f0 << time([&](int val) { lin.add(val); }, 100) << '\t' << n << endl;
        f1 << time([&](int val) { blc.add(val); }, 100) << '\t' << n << endl;
        f2 << time([&](int val) { exp.add(val); }, 10000)/100 << '\t' << n << endl;
    }
    cout << "---------OK---------" << endl;

    f0.close();
    f1.close();
    f2.close();

    return 0;
}
