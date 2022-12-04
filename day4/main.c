#include <stdio.h>
#include <stdlib.h>

int clearArray(char *buffer, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        *(buffer + i) = 0;
    }
    return 0;
}

int check_for_double_assingment(int* int_buff)
{
    int first1 = *(int_buff);
    int second1 = *(int_buff + 1);
    int first2 = *(int_buff + 2);
    int second2 = *(int_buff + 3);

    
    if(first1 <= first2 && second1 >= second2)
    {
        return 1;
    }

    if(first2 <= first1 && second2 >= second1)
    {
        return 1;
    }

    return 0;
}

int check_for_double_assignemnt2(int* int_buff)
{
    
    int first1 = *(int_buff);
    int second1 = *(int_buff + 1);
    int first2 = *(int_buff + 2);
    int second2 = *(int_buff + 3);
    
    for(int i = first1; i <= second1; i++)
    {
        if(i >= first2 && i <= second2)
        {
            return 1;
        }
    }

    for(int i = first2; i <= second2; i++)
    {
        if(i >= first1 && i <= second1)
        {
            return 1;
        }
    }

    return 0;
}


int count_double_assignment(char *path_name, int *int_buff, char* char_buff, size_t size, int (*f)(int*))
{
    FILE* input = fopen(path_name, "r");
    
    int counter = 0;
    char current = 0;

    int j = 0;
    
    for(int i = 0; i < size && current != EOF;)
    {
        current = getc(input);

        if(current == '-' || current == ',')
        {
            *(int_buff + j) = atoi(char_buff);
            j++;
            i = 0;
            clearArray(char_buff, size);
        }

        if((current == '\n' || current == EOF) && j == 3)
        {
            *(int_buff + j) = atoi(char_buff);
            counter += f(int_buff);
            j = 0;
            clearArray((char*) int_buff, size);
            i = 0;
            clearArray(char_buff, size);
        }

        if(current > 47 && current < 58)
        {
            *(char_buff + i) = current;
            i++;
        }
    }
    return counter;
}



int main()
{
    size_t ALLOC_SIZE = 100;
    char *PATH_NAME = "input";

    int* buff = malloc(ALLOC_SIZE);

    if(!buff)
    {
        exit(1);
    }

    char* char_buff = malloc(ALLOC_SIZE);

    if(!char_buff)
    {
        exit(1);
    }

    clearArray((char*)buff, ALLOC_SIZE);

    int count = count_double_assignment(PATH_NAME, buff, char_buff, ALLOC_SIZE, check_for_double_assingment);
    fprintf(stdout, "Count: %d\n", count);

    int count2 = count_double_assignment(PATH_NAME, buff, char_buff, ALLOC_SIZE, check_for_double_assignemnt2);
    fprintf(stdout, "Count2: %d\n", count2);
    free(buff);
    free(char_buff);
}