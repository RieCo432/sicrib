from abc import abstractmethod
from collections import MutableSequence


class CircularList(MutableSequence):

    def __delitem__(self, i):
        pass

    def __len__(self):
        return len(self._data)

    def __init__(self, data=None):
        super(CircularList, self).__init__()
        if data is not None:
            self._data = list(data)
        else:
            self._data = list()

    def __getitem__(self, item):
        return self._data[item]

    def insert(self, index, val):
        self._data[index] = val

    def append(self, val):
        self._data.append(val)

    def __setitem__(self, key, value):
        self._data[key] = value

    def shift_forward(self):  # shift all elements one index up, with wrap around
        last = self[-1]
        for i in range(len(self)).__reversed__():
            self[i] = self[i-1]
        self[0] = last

    def shift_forward_n(self, n):  # shift all elements n index up, with wrap around
        for i in range(n):
            self.shift_forward()

    def shift_backward(self):  # shift all elements one index down, with wrap around
        first = self[0]
        for i in range(len(self)-1):
            self[i] = self[i+1]
        self[-1] = first

    def shift_backward_n(self, n):  # shift all elements n index down, with wrap around
        for i in range(n):
            self.shift_backward()


if __name__ == "__main__":
    ca = CircularList((1, 2, 3))
    print(ca)
    ca.shift_backward_n(2)
    print(ca)
