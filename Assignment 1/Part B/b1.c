#include <stdio.h>
 
int gcd(int a, int b)
{
    if (a == 0)
        return b;
    int temp;

    printf("a = %d, b = %d ", a, b);
    while(b!=0)
    {
        printf("q = %d, r = %d\n", (a/b), (a%b));
        temp=a;
        a=b;
        b=temp%b;
        printf("a = %d, b = %d ", a, b);
    }
    return gcd(b%a, a);
}

int main()
{
    int a, b;
    printf("Enter the values of 'a' and 'b'. \n");
    scanf("%d %d", &a, &b);

    printf("\nGCD : %d\n", gcd(a, b));
    //gcd(a,b);
    return 0;
}