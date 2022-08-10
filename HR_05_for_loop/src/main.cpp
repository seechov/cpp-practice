#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    // Complete the code.
    int i1, i2;
    scanf("%d", &i1);
    scanf("%d", &i2);

    for (int i = i1; i <= i2; i++)
    {
        if (i == 1)
        {
            printf("one\n");
        }
        else if (i == 2)
        {
            printf("two\n");
        }
        else if (i == 3)
        {
            printf("three\n");
        }
        else if (i == 4)
        {
            printf("four\n");
        }
        else if (i == 5)
        {
            printf("five\n");
        }
        else if (i == 6)
        {
            printf("six\n");
        }
        else if (i == 7)
        {
            printf("seven\n");
        }
        else if (i == 8)
        {
            printf("eight\n");
        }
        else if (i == 9)
        {
            printf("nine\n");
        }
        else if (i % 2 == 0)
        {
            printf("even\n");
        }
        else
        {
            printf("odd\n");
        }
    }
    // printf("%d, %d\n", i1, i2);
    return 0;
}
