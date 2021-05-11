#include<stdio.h>
#include<stdlib.h>

int compute(int g,int b,int p)
{
    int ans=1;
    while(b != 0)
	{
        if(b&1) 	//if b is odd
		{
            ans = ans * g;		//multiply with g 
            ans = ans % p;		//mod with p 
        }
		b = b >> 1;				//divide a by 2
        g = g * g; 				//square g
        g = g % p;				//mod with p
        
    }
    return ans;					//return g^a mod p
}


int main(){

    int g,p,a,b;
    printf("\nHello! BOB here... \n");
    printf("Please enter Bob's secret parameter (b) and public parameters (g,p):\n");
    scanf("%d %d %d",&a,&g,&p);
    printf("\nBob's Secret parameter (b) is: %d.\n",a);
    printf("Public parameters (g and p) are:  %d  %d.\n",g,p);
    
    printf("Please enter the secret parameter(a) of Alice :\n");
    scanf("%d",&b);

    int B=compute(g,b,p);
    printf("\nShared key received from Alice, i.e. (g^a) mod p : %d.\n",B);
    printf("Shared secret, i.e. (g ^ ab) mod p : %d.\n",compute(B,a,p));

    return 0;
}