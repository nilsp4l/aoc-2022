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

int find_end_of_stack(char *stack, size_t size)
{
    int counter = 0;

    for (; counter < size && *(stack + counter) != 0; counter++)
        ;

    return counter;
}

int push(char *stack, char to_push, size_t size)
{

    if (!to_push)
    {
        return 1;
    }

    int end = find_end_of_stack(stack, size);

    for (int i = end + 1; i > 0; i--)
    {
        *(stack + i) = *(stack + i - 1);
    }

    *stack = to_push;
    return 0;
}

int insert(char *stack, char to_insert, size_t size)
{
    if (!stack)
    {
        exit(1);
    }

    if (!to_insert)
    {
        return 1;
    }

    int end = find_end_of_stack(stack, size);

    if (end != 0)
    {
        *(stack + end) = to_insert;
    }
    else
    {
        *stack = to_insert;
    }

    return 0;
}



char pop(char *stack, size_t size)
{

    if (!stack)
    {
        exit(1);
    }

    if (*stack == 0)
    {
        return 0;
    }

    char to_pop = *stack;

    for (int i = 0; i < (size - 1) && *(stack + i) != 0; i++)
    {
        *(stack + i) = *(stack + i + 1);
    }

    return to_pop;
}

int push_string(char *stack1, size_t size_to_push, char *stack2, size_t size_stack)
{
    for (int i = 0; i < size_to_push; i++)
    {
        push(stack1, 'a', size_stack);
    }

    for (int i = 0; i < size_to_push; i++)
    {
        *(stack1 + i) = pop(stack2, size_stack);
    }
    return 0;
}

int initialize_stack_and_instruction_array(char *path_name, char **stacks, int **instructions, size_t size_stack, size_t size_inst,
                                           int instruction_count, int stack_count)
{
    FILE *input = fopen(path_name, "r");

    if (!input)
    {
        exit(1);
    }

    char current = 0;
    int flag = 0;
    for (int i = 0; i < stack_count && current != '1';)
    {
        current = getc(input);

        if (current > 64 && current < 91)
        {
            insert(*(stacks + i), current, size_stack);
            i++;
            flag = 0;
        }

        if (current == ' ' && flag == 3)
        {
            i++;
            flag = 0;
        }

        else if (current == ' ')
        {
            flag++;
        }

        if (current == '\n')
        {
            i = 0;
        }
    }

    while (current != 'm')
    {
        current = getc(input);
    }
    char current_number[10];
    clear_array(current_number, 10);
    int number_index = 0;
    int instruction_index = 0;
    flag = 0;
    int i = 0;
    for (; i < instruction_count && current != EOF;)
    {
        current = getc(input);

        if (current < 58 && current > 47)
        {
            *(current_number + number_index++) = current;
            flag++;
        }
        if ((current == ' ' || current == '\n' || current == EOF) && flag)
        {
            instructions[i][instruction_index] = atoi(current_number);
            instruction_index++;

            clear_array(current_number, 10);
            flag = 0;
            number_index = 0;
        }

        if (current == '\n')
        {
            flag = 0;
            number_index = 0;
            instruction_index = 0;
            i++;
        }
    }
    clear_array((char *)*(instructions + i), instruction_count);

    return 0;
}

int move_crates(char **stacks, int **instructions, int stack_size, int instruction_size, int instruction_count, int stack_count)
{
    int count = 0;
    for (int i = 0; i < instruction_count && instructions[i][0] != 0; i++) // instruction[i][0] can never be 0 if valid
    {

        while (count != instructions[i][0])
        {
            char popped = pop(*(stacks + (instructions[i][1] - 1)), stack_size);
            push(*(stacks + (instructions[i][2] - 1)), popped, stack_size);
            count++;
        }
        count = 0;
    }
    return 0;
}

int move_crates2(char **stacks, int **instructions, int stack_size, int instruction_size, int instruction_count, int stack_count)
{
    int count = 0;
    for (int i = 0; i < instruction_count && instructions[i][0] != 0; i++) // instruction[i][0] can never be 0 if valid
    {
        push_string(*(stacks + instructions[i][2] - 1), instructions[i][0], *(stacks + instructions[i][1] - 1), stack_size);
        count++;
    }

    return 0;
}



int main()
{
    char *INPUT_NAME = "input";
    int stack_count = 20;
    char **stacks = malloc(stack_count * sizeof(char *));

    if (!stacks)
    {
        exit(1);
    }

    size_t stack_size = 200;

    for (int i = 0; i < stack_count; i++)
    {
        *(stacks + i) = malloc(stack_size);
        if (!*(stacks + i))
        {
            exit(1);
        }
        clear_array(*(stacks + i), stack_size);
    }

    int instruction_count = 1000;
    int **instructions = malloc(instruction_count * sizeof(int *));
    if (!instructions)
    {
        exit(1);
    }

    int instruction_size = 3 * sizeof(int);

    for (int i = 0; i < instruction_count; i++)
    {
        *(instructions + i) = malloc(instruction_size);

        if (!*(instructions + i))
        {
            exit(1);
        }
    }

    initialize_stack_and_instruction_array(INPUT_NAME, stacks, instructions, stack_size, instruction_size, instruction_count, stack_count);

    move_crates(stacks, instructions, stack_size, instruction_size, instruction_count, stack_count);
    printf("Solution1: ");
    for (int i = 0; i < stack_count; i++)
    {
        printf("%c", stacks[i][0]);
    }
    printf("\n");

    for (int i = 0; i < stack_count; i++)
    {
        clear_array(*(stacks + i), stack_size);
    }

    for (int i = 0; i < instruction_count; i++)
    {
        clear_array((char *)*(instructions + i), instruction_size);
    }

    initialize_stack_and_instruction_array(INPUT_NAME, stacks, instructions, stack_size, instruction_size, instruction_count, stack_count);

    move_crates2(stacks, instructions, stack_size, instruction_size, instruction_count, stack_count);

    printf("Solution2: ");
    for (int i = 0; i < stack_count; i++)
    {
        printf("%c", stacks[i][0]);
    }
    printf("\n");
    

    return 0;
}