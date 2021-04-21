#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>

#define ENLARGE_STACK
using std::cout;
using std::endl;
using std::mt19937;
using std::pair;
using std::shuffle;
using std::sort;
using std::swap;
using std::uniform_int_distribution;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;
using ll = int64_t;

const int maxn = 1e6 + 5;
const int n = 1e6;
const int roundNumber = 10;
int a[maxn], b[maxn];
steady_clock::time_point x, y;
mt19937 gen(time(nullptr));

template <typename T>
int RandPartition(T A[], int p, int r) {
    int i = uniform_int_distribution<int>(p, r)(gen);
    swap(A[r], A[i]);
    int x = A[r];
    i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

void QuickSort(int A[], int p, int r) {
    if (p < r) {
        int q = RandPartition(A, p, r);
        QuickSort(A, p, q - 1);
        QuickSort(A, q + 1, r);
    }
}

template <typename T>
void InsertionSort(T A[], int p, int r) {
    for (int i = p + 1; i <= r; i++) {
        int j;
        T tmp = A[i];
        for (j = i - 1; j >= p && A[j] > tmp; j--) {
            A[j + 1] = A[j];
        }
        A[j + 1] = tmp;
    }
}

template <typename T>
pair<int, int> ThreeMidPartitionAndGathering(T A[], int p, int r) {
    int q = (p + r) >> 1;
    if (A[p] > A[r]) {
        swap(A[p], A[r]);
    }
    if (A[q] > A[r]) {
        swap(A[q], A[r]);
    }
    if (A[p] > A[q]) {
        swap(A[p], A[q]);
    }
    swap(A[q], A[r]);
    T x = A[r];
    q = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] < x) {
            q++;
            swap(A[q], A[j]);
        }
    }
    swap(A[q + 1], A[r]);
    int s = r;
    for (int j = r; j > q + 1; j--) {
        if (A[j] > x) {
            A[s--] = A[j];
        }
    }
    for (int j = q + 1; j <= s; j++) {
        A[j] = x;
    }
    return {q + 1, s};
}

template <typename T>
void QuickSortKai(T A[], int p, int r) {
    if (r - p >= 15) {
        while (p < r) {
            pair<int, int> equals = ThreeMidPartitionAndGathering(A, p, r);
            int q = equals.first - 1, s = equals.second;
            QuickSortKai(A, p, q);
            p = s + 1;
        }
    } else {
        InsertionSort(A, p, r);
    }
}

void generate(int A[], int n, int percentage) {
    int m = n * percentage / 100;
    for (int i = 1; i <= n; i++) {
        A[i] = i;
    }
    shuffle(A + 1, A + n + 1, gen);
    for (int i = 2; i <= m; i++) {
        A[i] = A[1];
    }
    shuffle(A + 1, A + n + 1, gen);
}

void compare() {
    for (int percentage = 0; percentage <= 100; percentage += 10) {
        ll myTimeCount = 0, stdTimeCount = 0;

        for (int round = 1; round <= roundNumber; round++) {
            generate(a, n, percentage);
            for (int i = 1; i <= n; i++) {
                b[i] = a[i];
            }

            x = steady_clock::now();
            QuickSortKai(a, 1, n);
            y = steady_clock::now();
            myTimeCount += duration_cast<milliseconds>(y - x).count();

            x = steady_clock::now();
            sort(b + 1, b + n + 1);
            y = steady_clock::now();
            stdTimeCount += duration_cast<milliseconds>(y - x).count();

            // check if elements are sorted and no extra numbers are inserted.
            for (int i = 1; i <= n; i++) {
                assert(a[i] == b[i]);
            }
        }

        cout << "QuickSortKai() sorting " << n << " numbers with " << percentage
             << " % duplicate numbers cost " << myTimeCount * 1.0 / roundNumber
             << " ms." << endl;
        cout << "std::sort() sorting " << n << " numbers with " << percentage
             << " % duplicate numbers cost " << stdTimeCount * 1.0 / roundNumber
             << " ms." << endl;
        cout << endl;
    }
}

void test() {
    for (int percentage = 80; percentage <= 100; percentage += 10) {
        generate(a, n, percentage);
        x = steady_clock::now();
        QuickSort(a, 1, n);
        y = steady_clock::now();
        cout << "Sorting " << n << " numbers with " << percentage
             << " % duplicate numbers cost "
             << duration_cast<milliseconds>(y - x).count() << " ms" << endl;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cout.tie(nullptr);

#ifdef ENLARGE_STACK
    const int stack_size = 128 << 20;
    __asm__("movl %0, %%esp\n" ::"r"((char*)malloc(stack_size) + stack_size));
#endif
    // compare();
    test();
    return 0;
}

