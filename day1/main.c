#include <stdlib.h>
#include <stdio.h>

int clearArray(char* buffer, size_t size)
{
    for(size_t i = 0; *(buffer + i) != 0 && i < size; i++)
    {
        *(buffer + i) = 0;
    }
    return 0;
}


int initializeArray(char* name_of_file, int* buffer)
{
    FILE* input = fopen(name_of_file, "r");
    if(!input)
    {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }
    char current = 0;
    size_t ALLOC_SIZE = 100;
    char* elves = malloc(ALLOC_SIZE);
    if(!elves)
    {
        fprintf(stderr, "Error allocating memory\n");
        exit(1);
    }
    clearArray(elves, ALLOC_SIZE);

    int currentInt = 0;
    size_t j = 0;
    int flag = 0;
    for(size_t i = 0; current != EOF; i++)
    {
        current = getc(input);
        if(current == '\n' && flag)
        {
            *(buffer + j) = currentInt;
            j++;
            currentInt = 0;                                  
            i = -1;
            continue;
        }
        flag = 0;
        
        if(current > 47 && current < 58)
        {
            
            *(elves + i) = current;
        }
        else if(current == '\n')
        {
            currentInt += atoi(elves);
            
            clearArray(elves, ALLOC_SIZE);
            i = -1;
            flag = 1;
            
        }
        
    }
    if(*(buffer + j) == 0)
    {
        currentInt += atoi(elves);
    }

    *(buffer + j) = currentInt;

    fclose(input);

    free(elves);

    return 0;
}

int findMax(int *buffer, size_t size_buffer)
{
    int max = 0;

    for(int i = 0; i < size_buffer; i++)
    {
        if(*(buffer + i) > max)
        {
            max = *(buffer + i);
        }
    }
    return max;
}

int findTopThree(int *buffer, size_t size_buffer)
{
    int max1 = 0;
    int max1_index = 0;

    int max2 = 0;
    int max2_index = 0;

    int max3 = 0;


    for (int i = 0; i < size_buffer; i++)
    {
        if (*(buffer + i) > max1)
        {
            max1 = *(buffer + i);
            max1_index = i;
        }
    }

    for (int i = 0; i < size_buffer; i++)
    {
        if (*(buffer + i) > max2 && i != max1_index)
        {
            max2 = *(buffer + i);
            max2_index = i;
        }
    }

    for (int i = 0; i < size_buffer; i++)
    {
        if (*(buffer + i) > max3 && i != max1_index && i != max2_index)
        {
            
            max3 = *(buffer + i);
        }
        
    }
    
    return (max1 + max2 + max3);
}




int main()
{
    size_t ALLOC_SIZE = 500;
    
    int* list = malloc(ALLOC_SIZE * sizeof(int));
    if(!list)
    {
        fprintf(stderr, "Error allocating memory\n");
        exit(1);
    }
    initializeArray("input", list);
    
    int max = findMax(list, ALLOC_SIZE);

    fprintf(stdout, "Max: %d\n", max);

    int maxTopThree = findTopThree(list, ALLOC_SIZE);
    fprintf(stdout, "Top Three: %d\n", maxTopThree);
    free(list);
    return 0;
}

