#include<stdio.h>
#include<stdlib.h>

int compute(int g,int a,int p)
{
    int ans=1;
    while(a != 0) 		
	{
        if(a&1) 	//if a is odd
		{
            ans = ans * g;		//multiply with g 
            ans = ans % p;		//mod with p 
        }
		a = a >> 1;				//divide a by 2
        g = g * g; 				//square g
        g = g % p;				//mod with p
        
    }
    return ans;					//return g^a mod p
}


int main(){

    int g,p,a,b;
    printf("\nHello! ALICE here\n");
    printf("Please enter Alice's secret parameter (a) and public parameters (g,p) :\n");
    scanf("%d %d %d",&a,&g,&p);
    printf("\nAlice's Secret parameter(a) is : %d. \n",a);
    printf("Public parameters (g and p) are : %d and %d. \n",g,p);

    printf("Please enter the secret parameter(b) of Bob :\n");
    scanf("%d",&b);

    int B=compute(g,b,p);
    printf("\nShared key received from Bob, i.e. (g^b) mod p :  %d.\n",B);
    printf("Shared secret i.e. (g ^ ab) mod p : %d.\n",compute(B,a,p));

    return 0;
}