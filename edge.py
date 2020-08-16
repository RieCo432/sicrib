from compass import DataFlow

class Edge:

    def __init__(self, length, direction, data_flow):

        self.length = length
        self.direction = direction
        self.data_flow = data_flow
        self.leds = []

    def allocate_leds(self, first):

        last = first + self.length

        for i in range(first, last):
            self.leds.append(i)

        return last