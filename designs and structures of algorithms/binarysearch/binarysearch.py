import time
import random

def binary_search(arr, target):
    low, high = 0, len(arr) - 1
    while low <= high:
        mid = (low + high) // 2
        if arr[mid] == target:
            return mid  # Target found
        elif arr[mid] < target:
            low = mid + 1
        else:
            high = mid - 1
    return -1  # Target not found

def measure_performance():
    # Create a sorted list of integers
    arr = sorted([random.randint(1, 100000) for _ in range(100000)])
    target = random.choice(arr)  # Best case: target is present

    # Best-case scenario: Target is found at the middle
    best_case_arr = arr[:]
    best_case_target = best_case_arr[len(best_case_arr) // 2]
    start_time = time.time()
    binary_search(best_case_arr, best_case_target)
    print(f"Best case execution time: {time.time() - start_time:.6f} seconds")

    # Worst-case scenario: Target is not in the list
    worst_case_arr = arr[:]
    worst_case_target = -1  # Target not present
    start_time = time.time()
    binary_search(worst_case_arr, worst_case_target)
    print(f"Worst case execution time: {time.time() - start_time:.6f} seconds")

    # Average-case scenario: Target is randomly selected from the list
    average_case_arr = arr[:]
    average_case_target = random.choice(average_case_arr)
    start_time = time.time()
    binary_search(average_case_arr, average_case_target)
    print(f"Average case execution time: {time.time() - start_time:.6f} seconds")

# Measure performance
measure_performance()
