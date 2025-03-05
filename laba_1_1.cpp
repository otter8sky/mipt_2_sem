#include <iostream>
#include <chrono>
#include <fstream>
#include <random>

using namespace std;

typedef bool(func_name)(unsigned int *, int, int);

bool binar_search(unsigned int *arr, int N, int value) {
    int left = 0, right = N - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == value) {
            return true;
        }
        if (arr[mid] > value) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return false;
}

bool linear_search(unsigned int *arr, int N, int value) {
    for (int i = 0; i < N; ++i) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}


int time(func_name *func, int N, unsigned int *arr, int size) {
    unsigned seed = 1001;
    default_random_engine rng(seed);
    uniform_int_distribution<unsigned> dstr(0, 1'000'000);

    auto begin = chrono::steady_clock::now();
    for (unsigned cnt = N; cnt != 0; --cnt) {
        // func(arr, size, dstr(rng));
        func(arr, size, 1'000'001); // числа точно нет в массиве
    }

    auto end = chrono::steady_clock::now();
    auto time_span = chrono::duration_cast<chrono::microseconds>(end - begin);

    return time_span.count();
}

void print_array(unsigned int*& ptr_array, unsigned int size) {
    for (unsigned int idx = 0; idx != size; ++idx) {
      cout << ptr_array[idx] << ' ';
    }
    cout << endl;
  }
  
void swap_value(unsigned int& lha, unsigned int& rha) {
    unsigned int t = lha;
    lha = rha;
    rha = t;
}
 
void my_sort(unsigned int*& ptr_array, int left, int right) {
    if (left > right) return;

    unsigned int mid = ptr_array[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {    
        while (ptr_array[i] < mid) ++i;
        while (ptr_array[j] > mid) --j;
        if (i <= j) {
            swap_value(ptr_array[i], ptr_array[j]);
            ++i;
            --j;
        }
    }
    my_sort(ptr_array, left, j);
    my_sort(ptr_array, i, right);
}

unsigned int* generate_random_array(default_random_engine& rng, uniform_int_distribution<unsigned>& dstr, unsigned int size) {
    unsigned int* ptr_array = new unsigned int[size];
    for (unsigned int idx = 0; idx != size; ++idx) {
      ptr_array[idx] = dstr(rng);
    }
    return ptr_array;
  }
  
void delete_array(unsigned int*& ptr_array) { delete[] ptr_array; }
  
int main() {
    ofstream f0("out_linear_worst1.txt");
    ofstream f1("out_binar_worst1.txt");
    
    unsigned seed = 1001;
    default_random_engine rng(seed);
    uniform_int_distribution<unsigned> dstr(0, 1'000'000);
    
    for (unsigned int size = 10'000; size <= 1'000'000; size += 50'000) {
        unsigned int* ptr_array = generate_random_array(rng, dstr, size);

        f0 << time(linear_search, 1'000, ptr_array, size) << '\t' << size << endl;
        
        my_sort(ptr_array, 0, size);
        f1 << time(binar_search, 1'000'000, ptr_array, size) << '\t' << size << endl;

        if (size % 10'000 == 0) cout << size/10'000 << ' ';
        delete_array(ptr_array);
    }
    return 0;
}
