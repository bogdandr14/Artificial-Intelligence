#include "generator.h"

int random(int minValue, int maxValue){/// generates a number in a given range
    int counter = maxValue - minValue, number = 0;
    while (counter) {/// this will repeat until the number has a chance to get the max value of range
        number += number * RAND_MAX + rand();
        counter /= RAND_MAX;
    }
    return number % (maxValue - minValue + 1) + minValue;/// creates the number in the given range
}

void generator(int tests)/// generates the input data for a given test
{
    int testIterator, initial, target;
    char tempNameOut[20];
    for (testIterator = 1; testIterator <= tests; ++testIterator)
    {
        sprintf(tempNameOut, "data\\test_%d.in", testIterator);
        std::ofstream fout(tempNameOut);
        initial = random(3, 1000000000);/// generates the starting number
        target = random(1, 200);/// generates the ending number
        fout << initial << "\n" << target;///writes the numbers in the input file
    }
}
