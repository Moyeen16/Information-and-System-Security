#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

void decrypt()
{
    printf("\n************* Decryption *************\n");
    int mod;
    char* plainText = (char*)malloc(100*sizeof(char));

    char *cipherText;
    size_t bufsize = 100;
    size_t characters;

    cipherText = (char *)malloc(bufsize * sizeof(char));

    for(int i=0; i<100; i++)
        plainText[i] = '\0';

    printf("Enter the Cipher Text.\n");
    characters = getline(&cipherText, &bufsize, stdin);
 
    char* key = (char*)malloc(characters-1 * sizeof(char));

    printf("Enter the key.\n");
    for(int i=0; i<characters-1; i++)
        scanf("%c", &key[i]);

    for(int i=0; i<characters-1; i++)
        plainText[i] = (char)(((int)(cipherText[i]) - 48)^((int)key[i]-48))+48;

    printf("\nCipher Text :\t%s", cipherText);
    printf("Plain Text :\t%s\n", plainText);
    printf("\n");
}

void encrypt()
{
    printf("\n************* Encryption *************\n");
    int mod;
    char* cipherText = (char*)malloc(100*sizeof(char));

    char *plainText;
    size_t bufsize = 100;
    size_t characters;

    plainText = (char *)malloc(bufsize * sizeof(char));

    for(int i=0; i<100; i++)
        cipherText[i] = '\0';

    printf("Enter the Plain Text.\n");
    characters = getline(&plainText, &bufsize, stdin);

    srand(time(0));
    int* key = (int*)malloc(characters-1 * sizeof(int));
    for(int i=0; i<characters-1; i++)
    {
        int num = (rand() % 2);
        key[i] = num;
        cipherText[i] = (char)(((int)(plainText[i]) - 48)^key[i])+48;
    }
    printf("\nPlain Text :\t%s", plainText);
    printf("Generated Key :\t");
    for(int i=0; i<characters-1; i++)
        printf("%d", key[i]);
    printf("\n");
    printf("Cipher Text :\t%s\n", cipherText);
}

int main()
{
    int ch = 0;
    while(ch != 3)
    {
        printf("\n************* Demonstration of OTP *************\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
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
                printf("Thank You!\n\n");
                break;
            default:
                printf("Enter a Valid Choice.\n");
        }
    }
    return 0;
}