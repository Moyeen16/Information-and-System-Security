#include<stdio.h>

void compute(int* a, int* b, int q)
{
    int tmp = *b;
    *b = *a - q * (*b);
    *a = tmp;
}
int main()
{
    int a, b, tmp, idx=0;
    printf("Enter values of 'a' and 'b' :\n");
    scanf("%d %d",&a,&b);
    int r1=a,r2=b,s1=1,s2=0,t1=0,t2=1;
    while(r2!=0)
    {
        int q=r1/r2;
        compute(&r1,&r2,q);
        compute(&s1,&s2,q);
        compute(&t1,&t2,q);
    }
    printf("GCD : %d,  s : %d,  t:%d\n", r1, s1, t1);
    if(r1==1)
        printf("Multiplicative Inverse of %d mod %d is : %d.\n\n", a, b, (s1%b+b)%b);
    else
        printf("Multiplicative Inverse does not exist as a and b are not co-prime.\n\n");
    return 0;
}