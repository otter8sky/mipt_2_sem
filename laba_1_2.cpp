#include <iostream>
#include <chrono>
#include <fstream>
#include <random>

using namespace std;

typedef bool(func_name)(unsigned int *, int, int);

bool find_pair_quadratic(unsigned int *arr, int size, int value) {
    for (unsigned int i = 0; i < size; ++i) {
        for (unsigned int j = i + 1; j < size; ++j) {
            if (arr[i] + arr[j] == value) return true;
        }
    }
    return false;
}

bool find_pair_linear(unsigned int *arr, int size, int value) {
    int left = 0, right = size - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == value) return true;
        if (sum < value) ++left;
        else --right;
    }
    return false;
}

int time(func_name *func, int N, unsigned int *arr, int size) {
    unsigned seed = 1001;
    default_random_engine rng(seed);
    uniform_int_distribution<unsigned> dstr(0, 100'000);

    auto begin = chrono ::steady_clock ::now();
    for (unsigned cnt = N; cnt != 0; --cnt)
        // func(arr, size, dstr(rng));
        func(arr, size, 1'000'001); // числа точно нет в массиве
    auto end = chrono ::steady_clock ::now();
    auto time_span =chrono ::duration_cast<chrono ::microseconds>(end - begin);

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
    if (left >= right) return;
    unsigned int pivot = ptr_array[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {    
        while (ptr_array[i] < pivot) ++i;
        while (ptr_array[j] > pivot) --j;
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
    ofstream f0("out_quadric_pair_new.txt");
    ofstream f1("out_linear_pair_new.txt");
    
    unsigned seed = 1001;
    default_random_engine rng(seed);
    uniform_int_distribution<unsigned> dstr(0, 100'000);

    for (unsigned int size = 10000; size <= 100'000; size += 5000) {
        unsigned int* ptr_array = generate_random_array(rng, dstr, size);
        
        f0 << time(find_pair_quadratic, 10, ptr_array, size) << '\t' << size << endl;

        my_sort(ptr_array, 0, size - 1);
        f1 << time(find_pair_linear, 10, ptr_array, size) << '\t' << size << endl;

        delete_array(ptr_array);

        cout << "__________________________________" << ' ';
    }
    return 0;
}
