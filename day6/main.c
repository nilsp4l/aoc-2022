#include <stdio.h>
#include <stdlib.h>

int clear_array(char *buffer, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        *(buffer + i) = 0;
    }
    return 0;
}


int parse_input(char *path_name, char *buff, size_t buff_size)
{
    FILE* input = fopen(path_name, "r");
    if(!input)
    {
        exit(1);
    }
    char current = 0;
    for(int i = 0; i < buff_size && current != EOF;)
    {
        current = getc(input);
        if(current < 123 && current > 96)
        {
            *(buff + i++) = current;
        }
    }
}

int check_for_clone(char* buff, int left_border, int difference, size_t size)
{
    for(int i = left_border; i < size && i < (left_border + difference); i++)
    {
        for(int j = left_border; j < size && j < (left_border + difference); j++)
        {
            if(j != i && *(buff + j) == *(buff + i))
            {
                return 1;
            }
        }
    }
    return 0;
}


int find_marker(char* buff, int difference,  size_t size)
{
    
    for(int i = 0; i < size - 4 && *(buff + i); i++)
    {
        if(!check_for_clone(buff, i, difference, size))
        {
            return (i + difference);
        }
    }
    return 0;
}


int main()
{
    size_t ALLOC_SIZE = 5000;
    char* path_name = "input";
    char* buff = malloc(ALLOC_SIZE);
    clear_array(buff, ALLOC_SIZE);

    parse_input(path_name, buff, ALLOC_SIZE);
    int marker1 = find_marker(buff, 4,  ALLOC_SIZE);
    fprintf(stdout, "Marker1: %d\n", marker1);
    int marker2 = find_marker(buff, 14, ALLOC_SIZE);
    fprintf(stdout, "Marker2: %d\n", marker2);
}