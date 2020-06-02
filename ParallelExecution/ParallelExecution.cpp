// ParallelExecution.cpp : This is C task, it requires Linux environment. Implement run_in_parallel() to execute high performance sum()
//

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>  
typedef struct Data
{
    int first;
    int second;
    int third;
} Data;

void* sum(void* arg)
{
    Data* arguments = arg;
    int* result = malloc(sizeof(int));
    int i;
    *result = 0;
    for (i = arguments->first; i < arguments->second; i += arguments->third)
    {
        *result += i;
    }
    return result;
}

int* run_in_parallel(int count, const Data* params, void* (*function)(void*))
{
    static int result[10];
    int* ptr;
    int i;
    pthread_t threads[10];

    if ((count > 0) && (NULL != params) && (NULL != function))
    {
        for (i = 0; i < count; i++)
        {
            pthread_create(&threads[i], NULL, function, (void*)params);
            params++;
        }
        for (i = 0; i < count; i++)
        {
            pthread_join(threads[i], &ptr);
            result[i] = *ptr;
        }
    }

    return result;
}

#ifndef RunTests
int main()
{
    Data params[] = { {0, 1000, 2}, {6, 2000, 3} };
    int* result = run_in_parallel(2, params, sum);
    printf("%d, %d", result[0], result[1]);
}
#endif
