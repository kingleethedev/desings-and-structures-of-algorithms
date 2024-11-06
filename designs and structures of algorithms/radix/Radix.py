from typing import List

def counting_sort_for_radix(arr: List[int], exp: int) -> List[int]:
    n = len(arr)
    output = [0] * n  # output array to store sorted order temporarily
    count = [0] * 10  # digit range for base 10 numbers (0 to 9)

    # Count occurrences of each digit at the current position
    for i in arr:
        index = (i // exp) % 10
        count[index] += 1

    # Modify count so that it contains the actual positions in output
    for i in range(1, 10):
        count[i] += count[i - 1]

    # Build the output array
    i = n - 1
    while i >= 0:
        index = (arr[i] // exp) % 10
        output[count[index] - 1] = arr[i]
        count[index] -= 1
        i -= 1

    # Copy the output array to arr
    for i in range(n):
        arr[i] = output[i]

    return arr

def radix_sort(arr: List[int]) -> List[int]:
    max_num = max(arr)
    exp = 1
    while max_num // exp > 0:
        counting_sort_for_radix(arr, exp)
        exp *= 10
    return arr
