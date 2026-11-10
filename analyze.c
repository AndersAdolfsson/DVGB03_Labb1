#define _POSIX_C_SOURCE 200809L

#include "analyze.h"
#include "algorithm.h"

#include <stdlib.h>
#include <time.h>

//
// Private
//

static void fill_ascending(int *values, int size)
{
    for(int i=0; i<size; i++)
    {
        values[i] = i;
    }
}

static void fill_descending(int *values, int size)
{
    for(int i=0; i<size; i++)
    {
        values[i] = size - 1 - i;
    }
}

static void fill_random(int *values, int size)
{
    for(int i=0; i<size; i++)
    {
        values[i] = rand() % (size + 1);
    }
}

static void prepare_input(algorithm_t algoritm, case_t test_case, int *values, int size)
{
    switch (algoritm) 
    {
        case bubble_sort_t:
            switch (test_case)
            {
                case best_t:
                    fill_ascending(values, size);
                    break;

                case worst_t:
                    fill_descending(values, size);
                    break;

                case average_t:
                    fill_random(values,size);
                    break;

                default: 
                    break;
            }
            break;
        
        default:
            
            break;
    }    
}

//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n)
{    
    int elementCount = SIZE_START;

    for(int i=0; i<n; i++)
    {
        int *testValues = malloc(elementCount * sizeof(*testValues));
        
        if(testValues == NULL)
        {
            return;
        }

        prepare_input(a, c, testValues, elementCount);

        struct timespec start, end;

        clock_gettime(CLOCK_MONOTONIC, &start);

        switch (a) 
        {
            case bubble_sort_t:
                bubble_sort(testValues, elementCount);
                break;

            case insertion_sort_t:
                insertion_sort(testValues, elementCount);
                break;

            case quick_sort_t:
                quick_sort(testValues, elementCount);
                break;

            case linear_search_t:
                //linear_search(values, n, v);
                break;

            case binary_search_t:
                //binary_search(values, n, v);
                break;
            
            default:
                
                break;
        }

        clock_gettime(CLOCK_MONOTONIC, &end);

        double seconds = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) / 1e9;

        buf[i].size = elementCount;
        buf[i].time = seconds;

        free(testValues);

        elementCount *= 2;
    }
}