#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int clearArray(char *buffer, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        *(buffer + i) = 0;
    }
    return 0;
}

int initialize_both_arrays(char *pathname, char *buff1, char *buff2, size_t size)
{
    char current = 0;
    FILE *input = fopen(pathname, "r");

    if (!input)
    {
        exit(1);
    }

    for (int i = 0; i < size && current != EOF;)
    {
        current = getc(input);

        if (current == 'A' || current == 'B' || current == 'C')
        {
            *(buff1 + i) = current;
        }

        if (current == 'X' || current == 'Y' || current == 'Z')
        {
            *(buff2 + i) = current;
            i++;
        }
    }
    return 0;
}

int calculate_score(char *buff1, char *buff2, size_t size)
{
    uint64_t score = 0;

    for (int i = 0; i < size && *(buff1 + i) != 0 && *(buff2 + i) != 0; i++)
    {
        switch (*(buff2 + i))
        {
        case 'X':
        {
            score++;
            switch (*(buff1 + i))
            {
            case 'A':
            {
                score += 3;
                break;
            }
            case 'C':
            {
                score += 6;
                break;
            }
            default:;
            }
            break;
        }
        case 'Y':
        {
            score += 2;
            switch (*(buff1 + i))
            {
            case 'A':
            {
                score += 6;
                break;
            }
            case 'B':
            {
                score += 3;
                break;
            }
            default:;
            }
            break;
        }
        case 'Z':
        {
            score += 3;
            switch (*(buff1 + i))
            {
            case 'B':
            {
                score += 6;
                break;
            }
            case 'C':
            {
                score += 3;
                break;
            }
            default:;
            }
            break;
        }
        }
    }

    return score;
}


int calculate_secret_score(char *buff1, char *buff2, size_t size)
{
    uint64_t score = 0;

    for (int i = 0; i < size && *(buff1 + i) != 0 && *(buff2 + i) != 0; i++)
    {
        switch (*(buff1 + i))
        {
        case 'A':
        {
            switch (*(buff2 + i))
            {
            case 'X':
            {
                score += 3; //scissor
                break;
            }
            case 'Y':
            {
                score += 1; //rock
                score += 3; //draw
                break;
            }
            case 'Z':
            {
                score += 2; //paper
                score += 6; //win
                break;
            }
            default:;
            }
            break;
        }
        case 'B':
        {
            switch (*(buff2 + i))
            {
            case 'X':
            {
                score += 1; //rock
                break;
            }
            case 'Y':
            {
                score += 2; //paper
                score += 3; //draw
                break;
            }
            case 'Z':
            {
                score += 3; //scissor
                score += 6; //win
                break;
            }
            default:;
            }
            break;
        }
        case 'C':
        {
            switch (*(buff2 + i))
            {
            case 'X':
            {
                score += 2; //paper
                break;
            }
            case 'Y':
            {
                score += 3; //scissor
                score += 3; //draw
                break;
            }
            case 'Z':
            {
                score += 1; // rock
                score += 6; //win
                break;
            }
            default:;
            }
            break;
        }
        }
    }
    return score;
}

int main()
{
    size_t ALLOC_SIZE = 5000;
    char *INPUT_NAME = "input";
    char *buff1 = malloc(ALLOC_SIZE);
    char *buff2 = malloc(ALLOC_SIZE);

    if (!buff1 || !buff2)
    {
        exit(1);
    }

    clearArray(buff1, ALLOC_SIZE);
    clearArray(buff2, ALLOC_SIZE);

    initialize_both_arrays(INPUT_NAME, buff1, buff2, ALLOC_SIZE);

    fprintf(stdout, "Score: %u\n", calculate_score(buff1, buff2, ALLOC_SIZE));
    fprintf(stdout, "Secret Score: %u\n", calculate_secret_score(buff1, buff2, ALLOC_SIZE));
    free(buff1);
    free(buff2);
    return 0;
}