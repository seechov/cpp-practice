#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main()
{
    char* str_end;
    char input[10000];
    long number_of_elements(0);
    int int_array[1000];

    while (fgets(input, sizeof(input), stdin))
    {
        number_of_elements = strtol(input, &str_end, 10);
        if (str_end == input || *str_end != '\n')
        {
            printf("Please enter an integer: ");
        }
        else break;
    }

    fgets(input, sizeof(input), stdin);
    char* str_start = input;
    int i = 0;
    do
    {
        int next_number = strtol(str_start, &str_end, 10);
        str_start = str_end;
        int_array[i] = next_number;
        i += 1;
        // printf("%d", next_number);
    }
    while (str_end != input && *str_end != '\n');
    for (int i = number_of_elements - 1; i >= 0; --i)
    {
        if (i != 0)
        {
            printf("%d ", int_array[i]);
        }
        else
        {
            printf("%d\n", int_array[i]);
        }
    }

    return 0;
}
