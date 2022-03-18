from abc import ABC, abstractmethod
from random import randint


class Sorter(ABC):
    def __init__(self):
        super().__init__()

    @abstractmethod
    def sort(self):
        pass

    @abstractmethod
    def explain(self):
        pass

# BubbleSort algorithm taken from realpython.com/sorting-algorithms-python/
class BubbleSort(Sorter):
    def sort(self, data):
        n = len(data)
        for i in range(n):
            already_sorted = True
            for j in range(n - i - 1):
                if data[j] > data[j+1]:
                    data[j], data[j+1] = data[j+1], data[j]
                    already_sorted = False
            if already_sorted:
                break
        return data
    
    def explain(self):
        print("Bubble Sort is a straightforward sorting algorithm that bubbles elements to the top of the list one by one. It is inefficient so is not often practically used but is often taught to new programmers due to its simplicity.")

# InsertionSort algorithm taken from realpython.com/sorting-algorithms-python/
class InsertionSort(Sorter):
    def sort(self, data):
        for i in range(1, len(data)):
            key_item = data[i]
            j = i - 1
            while j >= 0 and data[j] > key_item:
                data[j+1] = data[j]
                j -= 1
            data[j+1] = key_item
        return data

    def explain(self):
        print("Insertion Sort is a simple and slightly inefficient sorting algorithm with a worst case time complexity of O(n^2). It works by pushing smaller values to the left of the list until the list is sorted.")

# SelectionSort algorithm taken from stackabuse.com/sorting-algorithms-in-python
class SelectionSort(Sorter):
    def sort(self, data):
        for i in range(len(data)):
            lowest_value_index = i
            for j in range(i+1, len(data)):
                if data[j] < data[lowest_value_index]:
                    lowest_value_index = j
            data[i], data[lowest_value_index] = data[lowest_value_index], data[i]
        return data

    def explain(self):
        print("Selection Sort works by creating a new empty array and selecting the largest value in the old array and pushing it to the front of the new array. In practice no new array is actually created though, and the larger values are just moved to the end of the array to be more efficient with space.")

