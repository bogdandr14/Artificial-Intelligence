#include <time.h>
#include "AStar.h"
#include "generator.h"
#define TESTS_NO 10
#define FILENAME_SIZE 20
ifstream fin;
ofstream fout;
int main()
{
    char tempNameIn[FILENAME_SIZE], tempNameOut[FILENAME_SIZE];
    clock_t start, finish;
    srand(time(0));/// use the internal clock of the processor for the seed of random number generator
    ///uncomment the next line to generate new input
    ///generator(TESTS_NO);/// generates the input for TESTS_NO tests

    for (int testIterator = 1; testIterator <= TESTS_NO; ++testIterator)
    {
        sprintf(tempNameIn, "data\\test_%d.in", testIterator);
        sprintf(tempNameOut, "data\\test_%d.out", testIterator);
        fin.open(tempNameIn, std::ios_base::in);
        fout.open(tempNameOut, std::ios_base::out);

        start = clock();/// store time before running
        AStar(fin, fout);/// calculate and print the answer for the current test
        finish = clock();/// store time after measured block ends

        double duration = (double)(finish - start) / CLOCKS_PER_SEC;/// calculate the duration of the algorithm for the current test
        printf("Duration for Test no.%d: %.3f\n", testIterator, duration);

        fin.close();
        fout.close();
    }
	return 0;
}
