#include <vector>
#include <algorithm>
using namespace std;

void countingSortForRadix(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);  // output array to store sorted order temporarily
    int count[10] = {0};    // digit range for base 10 numbers (0 to 9)

    // Count occurrences of each digit at the current position
    for (int i = 0; i < n; i++) {
        int index = (arr[i] / exp) % 10;
        count[index]++;
    }

    // Modify count so that it contains the actual positions in output
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        int index = (arr[i] / exp) % 10;
        output[count[index] - 1] = arr[i];
        count[index]--;
    }

    // Copy the output array to arr
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

vector<int> radixSort(vector<int>& arr) {
    int maxNum = *max_element(arr.begin(), arr.end());
    int exp = 1;
    while (maxNum / exp > 0) {
        countingSortForRadix(arr, exp);
        exp *= 10;
    }
    return arr;
}
