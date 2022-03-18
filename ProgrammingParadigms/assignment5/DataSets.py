from DataSet import *
from random import shuffle, randint

class DataSets:
    def __init__(self):
        self.myDataSets = []
        
    def create_datasets(self):
        squares = list(n * n for n in range(100))
        shuffle(squares)
        self.myDataSets.append(DataSet(BubbleSort, RemoveAllAbove, Mean, squares))

        evens = list(n * 2 for n in range(50))
        shuffle(evens)
        self.myDataSets.append(DataSet(InsertionSort, RemoveAllBelow, Median, evens))

        ints = list(randint(1, 20) for n in range(50))
        self.myDataSets.append(DataSet(SelectionSort, RemoveAllAbove, Mode, ints))

    def print_report(self):
        i = 1
        for item in self.myDataSets:
            print(f"Dataset {i}:")
            print(f"Sorter used: {item.sorter}")
            item.sorter.explain(0)
            print(f"Filterer used: {item.filterer}")
            print(f"Averager used: {item.averager}")
            print("I could not get the timing to work")
            item.sort()
            item.filter(10)
            print(f"Average after sort and filter: {item.average()}")
            print("First 50 (or less) elements of sorted and filtered data:")
            print(item.data[0:min(len(item.data)-1, 50)])
            print("\n\n")
            i += 1
