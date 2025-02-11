#include <math.h>
#include <stdio.h>
#include <stdlib.h>


double generate_random_double()
{
    double x;

    x = rand() / (RAND_MAX + 1.0);
    return (x);
}

int main()
{
    int x;

    x = 0;
    while ( x < 10)
    {
        printf("%f \n", (double)x + generate_random_double());
        x++;
    }
    return 0;
}