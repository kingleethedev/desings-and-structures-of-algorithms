#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

int binary_search(const vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void analyzeSearchPerformance() {
    // Create a sorted array of random integers
    vector<int> arr(100000);
    for (int i = 0; i < 100000; ++i) {
        arr[i] = rand() % 100000 + 1;
    }
    sort(arr.begin(), arr.end());
    
    // Best-case scenario: Target is at the middle
    int best_case_target = arr[arr.size() / 2];
    clock_t start_time = clock();
    binary_search(arr, best_case_target);
    cout << "Best case execution time: " << (clock() - start_time) / (double)CLOCKS_PER_SEC << " seconds" << endl;

    // Worst-case scenario: Target is not present
    int worst_case_target = -1;
    start_time = clock();
    binary_search(arr, worst_case_target);
    cout << "Worst case execution time: " << (clock() - start_time) / (double)CLOCKS_PER_SEC << " seconds" << endl;

    // Average-case scenario: Randomly selected target
    int average_case_target = arr[rand() % arr.size()];
    start_time = clock();
    binary_search(arr, average_case_target);
    cout << "Average case execution time: " << (clock() - start_time) / (double)CLOCKS_PER_SEC << " seconds" << endl;
}

int main() {
    analyzeSearchPerformance();
    return 0;
}
