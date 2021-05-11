#include <stdio.h>
int main()
{
    int n, inp;
    printf("Enter the value of mod.\n");
    scanf("%d", &n);
    printf("Enter the number.\n");
    scanf("%d", &inp);
    for(int i=0; i<n; i++)
    {
        if((inp * i) % n == 1)
        {
            printf("Multiplicative Inverse of %d mod %d is %d.\n\n", inp, n, i);
            return 0;
        }
    }
    printf("Multiplicative Inverse of %d does not exist for the given value of 'mod'.\n\n", inp);
    return 0;
}