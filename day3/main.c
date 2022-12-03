#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int UPPER_CASE_DIFF = 38;
int LOWER_CASE_DIFF = 96;

int clearArray(char *buffer, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        *(buffer + i) = 0;
    }
    return 0;
}

int contains(char c, char *buff, size_t size)
{
    for (int i = 0; i < size && *(buff + i) != 0; i++)
    {
        if (*(buff + i) == c)
        {
            return 1;
        }
    }
    return 0;
}

int convert_char_to_value(char c)
{
    int return_val = -1;
    if (c > 64 && c < 91)
    {
        return_val = c - UPPER_CASE_DIFF;
    }
    else if (c > 97 && c < 123)
    {
        return_val = c - LOWER_CASE_DIFF;
    }

    return return_val;
}

int count_doubles(char *buff, size_t size)
{
    int len = strlen(buff);
    char already_counted[size];

    clearArray(already_counted, size);

    int a_counted_index = 0;

    int half = len >> 1;
    int counter = 0;
    char current = 0;
    for (int i = 0; i < size && i < half; i++)
    {
        current = *(buff + i);
        for (int j = half; j < size && j < len; j++)
        {
            if (*(buff + j) == current && !contains(current, already_counted, size))
            {
                counter += convert_char_to_value(current);
                *(already_counted + a_counted_index) = current;
                a_counted_index++;
            }
        }
    }

    return counter;
}

int count_till_plus(char *buff, size_t size)
{
    int counter = 0;
    int len = strlen(buff);
    for (int i = 0; i < size && i < len; i++)
    {
        if (*(buff + i) != '+')
        {
            counter++;
        }
        else
        {
            return counter;
        }
    }
    return -1;
}

int count_doubles_in_3_lines(char *buff, size_t size)
{

    char already_counted[size];

    clearArray(already_counted, size);

    int a_counted_index = 0;
    int first = count_till_plus(buff, size);
    int second = count_till_plus((buff + first + 1), size);
    int third = count_till_plus((buff + first + second + 2), size);
    int counter = 0;
    char current = 0;
    for (int i = 0; i < size && i < first; i++)
    {
        current = *(buff + i);
        for (int j = first + 1; j < size && j < (first + second + 1); j++)
        {
            if (*(buff + j) == current)
            {
                for (int k = first + second + 1; k < size && k < (first + second + third + 2); k++)
                {
                    if (*(buff + k) == current && !contains(current, already_counted, size))
                    {
                        counter += convert_char_to_value(current);
                        *(already_counted + a_counted_index) = current;
                        a_counted_index++;
                    }
                }
            }
        }
    }

    return counter;
}

int load_lines_and_count(char *file_name, char *buff, size_t size)
{
    char current = 0;
    FILE *input = fopen(file_name, "r");

    if (!input)
    {
        exit(1);
    }

    int count = 0;
    for (int i = 0; i < size && current != EOF;)
    {
        current = getc(input);

        if ((current > 64 && current < 91) || (current > 97 && current < 123))
        {
            *(buff + i) = current;
            i++;
        }

        if (current == '\n' || current == EOF)
        {
            count += count_doubles(buff, size);
            clearArray(buff, size);
            i = 0;
        }
    }
    return count;
}

int load_3_lines_and_count(char *file_name, char *buff, size_t size)
{
    char current = 0;
    FILE *input = fopen(file_name, "r");

    if (!input)
    {
        exit(1);
    }

    int count = 0;
    int flag = 0;
    for (int i = 0; i < size && current != EOF;)
    {
        current = getc(input);

        if ((current > 64 && current < 91) || (current > 97 && current < 123))
        {
            *(buff + i) = current;
            i++;
        }

        if (current == '\n' || current == EOF)
        {
            *(buff + i) = '+';
            i++;
            flag++;
        }

        if ((current == '\n' || current == EOF) && flag == 3)
        {
            count += count_doubles_in_3_lines(buff, size);
            clearArray(buff, size);
            flag = 0;
            i = 0;
        }
    }
    return count;
}

int main()
{
    size_t ALLOC_SIZE = 500;
    char *PATH_NAME = "input";
    char *buff = malloc(ALLOC_SIZE);
    if (!buff)
    {
        exit(1);
    }
    clearArray(buff, ALLOC_SIZE);
    int count = load_lines_and_count(PATH_NAME, buff, ALLOC_SIZE);
    int count_3 = load_3_lines_and_count(PATH_NAME, buff, ALLOC_SIZE);
    fprintf(stdout, "First part: %d\n", count);
    fprintf(stdout, "Second part: %d\n", count_3);
    free(buff);

    return 0;
}