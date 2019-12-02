#########################################################################################
# LEVEL ENCODER                                                                         #
# This tool converts a level statically-defined with 2D arrays into a RLE-encoded array #
#########################################################################################

from _levels import *

#----------CLASSES----------

class Cell:
    def __init__(self, number, count):
        self.number = number
        self.count = count

    def __str__(self):
        return "{{{0},{1}}}".format(self.number, self.count)
    def tostr(self):
        return self.__str__() + ", "

#----------FUNCTIONS----------

def encode_level(level):

    encoded_string = "{\n    "

    for j in range(len(level)):

        count = 0
        number = -1
        for i in range(len(level[j])):
            if level[j][i] != number:

                if(number != -1) :
                    encoded_string += Cell(number, count).tostr()

                number = level[j][i]
                count = 1
            else:
                count += 1

        if(count > 1):
            encoded_string += Cell(number, count).tostr()
           
        encoded_string += "{{{0},0xFF}}".format(number)

        if j == len(level) - 1:
            encoded_string += "\n"
        else:
            encoded_string += ",\n    "

    return encoded_string + "};"




#----------MAIN---------------

encoded_str = encode_level(LEVEL0)
print ("PROGMEM static const Cell LEVEL_0[] =")
print (encoded_str)

encoded_str = encode_level(LEVEL1)
print ("PROGMEM static const Cell LEVEL_1[] =")
print (encoded_str)

encoded_str = encode_level(LEVEL2)
print ("PROGMEM static const Cell LEVEL_2[] =")
print (encoded_str)

encoded_str = encode_level(LEVEL3)
print ("PROGMEM static const Cell LEVEL_3[] =")
print (encoded_str)

encoded_str = encode_level(LEVEL4)
print ("PROGMEM static const Cell LEVEL_4[] =")
print (encoded_str)




