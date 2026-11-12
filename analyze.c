#define _POSIX_C_SOURCE 200809L

#include "analyze.h"
#include "algorithm.h"
#include "debug.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

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
    // Fill ascending first to avoid duplicate entries
    fill_ascending(values, size);

    // Shuffle values to random order
    for (int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        int temp = values[i];
        values[i] = values[j];
        values[j] = temp;
    }
}

static void prepare_input(algorithm_t algoritm, case_t test_case, int *values, int size)
{
    // Each algorithm needs different data to be best/worst/average,
    // pick appropriate helper function for each algorithm
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
        
        case linear_search_t:
            fill_ascending(values, size);
            break;

        default:
            break;
    }    
}

static void print_array_overview(const char *message, const int *values, int size)
{
    printf("%s", message);

    const int displayCount = 5;

    if (size <= displayCount * 2)
    {
        for (int i = 0; i < size; i++)
        {
            printf("%d ", values[i]);
        }
    }
    else
    {
        for (int i = 0; i < displayCount; i++)
        {
            printf("%d ", values[i]);
        }

        printf("... ");

        for (int i = size - displayCount; i < size; i++)
        {
            printf("%d ", values[i]);
        }
    }

    printf("\n");
}

//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n)
{    
    int elementCount = SIZE_START;
    
    // Generate test data for the amount of results expected,
    // double element count for each new iteration
    for(int i=0; i<n; i++)
    {
        double totalTime = 0;
        int *testValues = malloc(elementCount * sizeof(*testValues));
        
        if(testValues == NULL)
        {
            return;
        }

        struct timespec start, end;

        for(int j=0; j<ITERATIONS; j++)
        {
            prepare_input(a, c, testValues, elementCount);

            if(debug_is_enabled())
            {
                print_array_overview("Unsorted array : ", testValues, elementCount);
            }

            switch (a) 
            {
                case bubble_sort_t:
                {
                    clock_gettime(CLOCK_MONOTONIC, &start);
                    bubble_sort(testValues, elementCount);
                    clock_gettime(CLOCK_MONOTONIC, &end);

                    break;
                }

                case insertion_sort_t:
                {
                    clock_gettime(CLOCK_MONOTONIC, &start);
                    insertion_sort(testValues, elementCount);
                    clock_gettime(CLOCK_MONOTONIC, &end);

                    break;
                }

                case quick_sort_t:
                {
                    clock_gettime(CLOCK_MONOTONIC, &start);
                    quick_sort(testValues, elementCount);
                    clock_gettime(CLOCK_MONOTONIC, &end);
                    
                    break;
                }

                case linear_search_t:
                {
                    int searchValue;
                    switch(c)
                    {
                        case best_t:
                            searchValue = testValues[0];
                            break;

                        case average_t:
                            searchValue = testValues[rand() % elementCount];
                            break;

                        case worst_t:
                            searchValue = -1;
                            break;

                        default:
                            break;
                    }
            
                    clock_gettime(CLOCK_MONOTONIC, &start);
                    linear_search(testValues, elementCount, searchValue);
                    clock_gettime(CLOCK_MONOTONIC, &end);
                    
                    break;
                }

                case binary_search_t:
                {
                    //binary_search(values, n, v);
                    continue;
                }
                    
                default:
                    continue;
            }

            if(debug_is_enabled())
            {
                print_array_overview("Sorted array : ", testValues, elementCount);
            }

            const double seconds = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) / 1e9;
            totalTime += seconds;
        }

        buf[i].size = elementCount;
        buf[i].time = totalTime/ITERATIONS;

        free(testValues);

        elementCount *= 2;
    }
}