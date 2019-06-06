#########################################################################################
# LEVEL ENCODER                                                                         #
# This tool converts a level statically-defined with 2D arrays into a RDL-encoded array #
#########################################################################################

from _levels import *

#----------CLASSES----------

class Cell:
    def __init__(self, number, count):
        self.number = number
        self.count = count

    def __str__(self):
        return "{{{0},{1}}}".format(self.number, self.count)
    def __repr__(self):
        return self.__str__()

#----------FUNCTIONS----------

def encode_level(level):

    encoded_level = []
    encoded_string = ""

    for j in range(len(level)):

        count = 0
        number = -1
        for i in range(len(level[j])):
            if level[j][i] != number:

                if(number != -1) :
                    encoded_level.append(Cell(number, count))
                    encoded_string += str(Cell(number, count))
                    encoded_string += ", "

                number = level[j][i]
                count = 1
            else:
                count += 1

        encoded_level.append(Cell(number, 0xFF))
        encoded_string += "{{{0},0xFF}}\n".format(number)

    return encoded_level, encoded_string




#----------MAIN---------------

encoded_str = encode_level(LEVEL1)[1]
print ("level1:")
print (encoded_str)





