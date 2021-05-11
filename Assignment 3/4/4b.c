#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int multiplicativeInverse(int inp)
{
    int mod = 26;
    for(int i=0; i<mod; i++)
    {
        if((inp * i) % mod == 1)
            return i;
    }
    printf("Multiplicative Inverse of %d does not exist.\n", inp);
    return -1;

}
int additiveInverse(int inp){
    for(int i = 0; i < 26 ; i++)
    {
        if((inp+i) % 26 == 0)
            return i;
    }
    return -1;
}
void to_binary(int n, char* binary)
{
    for(int i=4;i>=0;i--)    
        binary[i]='0';
    for(int i=4;n>0;i--)    
    {    
        binary[i]=(char)((n%2)+48);    
        n=n/2;    
    }    
}

void random_generator(int a, int b, int* s, int mod, char* binary)
{
    int s_new = (a*(*s) + b) % mod;
    //printf("Rand %d\n", s_new);
    char* binary_s_new = (char*)malloc(5*sizeof(char));
    to_binary(s_new, binary_s_new);
    for(int i=0; i<5; i++)
        binary[i] = binary_s_new[i];
    *s = s_new;
}

void decrypt()
{
    printf("\n************* Decryption *************\n");
    int mod = 26;
    char* plainText = (char*)malloc(100*sizeof(char));

    char *cipherText;
    size_t bufsize = 100;
    size_t characters;

    cipherText = (char *)malloc(bufsize * sizeof(char));

    for(int i=0; i<100; i++)
        plainText[i] = '\0';

    printf("Enter the Cipher Text.\n");
    characters = getline(&cipherText, &bufsize, stdin);
    
    int a, b, s0;
    printf("Enter the values of A, B, S0.\n");
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &s0);

    char* key = (char*)malloc(5 * sizeof(char));
    to_binary(s0, key);

    printf("Cipher Text :\t%s", cipherText);
    printf("Generated Key :\t");
    for(int i=0; i<characters-1; i++)
    {
        //printf("Here %s\n", key);
        int j=0;
        for(j=0; j<5; j++)
        {
            plainText[i+j] = cipherText[i+j] ^ (key[j]-48);
            printf("%c", key[j]);
        }
        i = i+j-1;
        random_generator(a, b, &s0, mod, key);
    }
    printf("\n");
    printf("Plain Text :\t%s\n", plainText);
    printf("\n");
}

void encrypt()
{
    printf("\n************* Encryption *************\n");
    int mod = 26;
    char* cipherText = (char*)malloc(100*sizeof(char));

    char *plainText;
    size_t bufsize = 100;
    size_t characters;

    plainText = (char *)malloc(bufsize * sizeof(char));

    for(int i=0; i<100; i++)
        cipherText[i] = '\0';

    printf("Enter the Plain Text.\n");
    characters = getline(&plainText, &bufsize, stdin);

    int a, b, s0;
    printf("Enter the values of A, B, S0.\n");
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &s0);
    
    printf("\nPlain Text :\t%s", plainText);
    //int* key = (int*)malloc(characters-1 * sizeof(int));
    char* key = (char*)malloc(5 * sizeof(char));
    to_binary(s0, key);
    printf("Generated Key :\t");
    for(int i=0; i<characters-1; i++)
    {
        //printf("Here %s\n", key);
        int j=0;
        for(j=0; j<5; j++)
        {
            cipherText[i+j] = plainText[i+j] ^ (key[j]-48);
            printf("%c", key[j]);
        }
        i = i+j-1;
        random_generator(a, b, &s0, mod, key);
    }
    printf("\n");
    
    //printf("Generated Key :\t");
    // for(int i=0; i<characters-1; i++)
    //     printf("%c", key[i]);
    // printf("\n");
    printf("Cipher Text :\t%s\n", cipherText);
}

void cryptanalysis()
{
    char *plainText;
    size_t bufsize = 100;
    size_t characters1;
    plainText = (char *)malloc(bufsize * sizeof(char));
    printf("Enter the Plain Text.\n");
    characters1 = getline(&plainText, &bufsize, stdin);

    char *cipherText;
    bufsize = 100;
    size_t characters2;
    cipherText = (char *)malloc(bufsize * sizeof(char));
    printf("Enter the Cipher Text.\n");
    characters2 = getline(&cipherText, &bufsize, stdin);

    int s0 = 0;
    int s1 = 0;
    int s2 = 0;
    for(int i=4; i>=0; i--)
    {
        int bit = (plainText[i]-48) ^ (cipherText[i]-48);
        s0 = s0 + (pow(2, 4-i) * bit);
    }
    for(int i=9; i>=5; i--)
    {
        int bit = (plainText[i]-48) ^ (cipherText[i]-48);
        s1 = s1 + (pow(2, 9-i) * bit);
    }
    printf("S1 = %d\n", (int)s1);
    for(int i=14; i>=10; i--)
    {
        int bit = (plainText[i]-48) ^ (cipherText[i]-48);
        s2 = s2 + (pow(2, 14-i) * bit);
    }
    printf("S2 = %d\n\n", (int)s2);
    int a, b;
    int mod = 26;
    if(multiplicativeInverse(s0 + additiveInverse(s1)) == -1)
    {
        printf("Cryptanalysis is not Possible.\n");
        return;
    }
    a = (multiplicativeInverse((s0 + additiveInverse(s1)) % 26) * ((s1 + additiveInverse(s2)) %26)) % 26;
    b = (s1 + additiveInverse(s0 * a)) % 26;
    
    printf("S0 = %d\n", (int)s0);
    printf("A = %d\n", a%26);
    printf("B = %d\n", b); 
}

int main()
{
    int ch = 0;
    while(ch != 4)
    {
        printf("\n************* Demonstration of OTP *************\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Cryptanalysis\n");
        printf("4. Exit\n");
        scanf("%d", &ch);
        fflush(stdin);
        fflush(stdin);

        switch(ch)
        {
            case 1 :
                encrypt();
                break;
            case 2 :
                decrypt();
                break;
            case 3 :
                cryptanalysis();
                break;
            case 4 :
                printf("Thank You!\n\n");
                return 0;
            default:
                printf("Enter a Valid Choice.\n");
        }
    }
    return 0;
}




/*


Plain Text :    01100 01110 11000
Generated Key : 00011 00101 00111
                  S0    S1    S2
                  3     5     7
Cipher Text :   01111 01011 11111


For 1st 5 bits (Bit 0 to Bit 4) : We get S0 = 3

Now S1 = (3A + B)
    or   3A + B = 5
Now S2 = (5A + B)
    or   3A + B = 7

Solving we get A = 1, B = 2.

*/