#pragma once

#ifndef SORT_H_
#define SORT_H_

#include <random>
#include <stack>
#include <vector>

int random_partition(std::vector<int> &A, int p, int r) {
    static std::mt19937_64 gen(std::random_device{}());
    int index = std::uniform_int_distribution<int>{p, r}(gen);
    std::swap(A[r], A[index]);
    int x = A[r];
    index = p - 1;
    for (int i = p; i < r; i++) {
        if (A[i] <= x) {
            index++;
            std::swap(A[index], A[i]);
        }
    }
    std::swap(A[index + 1], A[r]);
    return index + 1;
}

void naive_quicksort(std::vector<int> &A, int p, int r) {
    if (p < r) {
        int q = random_partition(A, p, r);
        naive_quicksort(A, p, q - 1);
        naive_quicksort(A, q + 1, r);
    }
}

void insertion_sort(std::vector<int> &A, int p, int r) {
    for (int i = p + 1; i <= r; i++) {
        int j, temp = A[i];
        for (j = i - 1; j >= p && A[j] > temp; j--) {
            A[j + 1] = A[j];
        }
        A[j + 1] = temp;
    }
}

std::pair<int, int> three_mid_partition_with_gathering(std::vector<int> &A,
                                                       int p, int r) {
    int q = p + (r - p) / 2;
    if (A[p] > A[r]) {
        std::swap(A[p], A[r]);
    }
    if (A[q] > A[r]) {
        std::swap(A[q], A[r]);
    }
    if (A[p] > A[q]) {
        std::swap(A[p], A[q]);
    }
    std::swap(A[q], A[r]);
    int x = A[r];
    q = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] < x) {
            q++;
            std::swap(A[q], A[j]);
        }
    }
    std::swap(A[q + 1], A[r]);
    int s = r;
    for (int j = r; j > q + 1; j--) {
        if (A[j] > x) {
            A[s--] = A[j];
        }
    }
    for (int j = q + 1; j <= s; j++) {
        A[j] = x;
    }
    return std::make_pair(q, s);
}

void improved_quicksort(std::vector<int> &A, int p, int r) {
    std::stack<std::pair<int, int>> s;
    s.emplace(p, r);
    while (!s.empty()) {
        auto [x, y] = s.top();
        s.pop();
        if (y - x >= 15) {
            do {
                auto [new_x, new_y] = three_mid_partition_with_gathering(A, x, y);
                s.emplace(x, new_x);
                x = new_y + 1;
            } while (x < y);
        } else {
            insertion_sort(A, x, y);
        }
    }
}

#endif  // SORT_H_
