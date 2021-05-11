#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int additiveInverse(int inp, int mod)
{
    for(int i=0; i<mod; i++)
    {
        if((inp + i) % mod == 0)
        {
            //printf("(Inverse for the given key : %d)\n", i);
            return i;
        }
    }
    printf("Additive Inverse of %d does not exist for the given value of 'mod'.\n\n", inp);
    return 0;
}

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
    
    //printf("Enter the value of mod.\n");
    //scanf("%d", &mod);
    mod = 26;

    printf("Enter the Size of the Key.\n");
    int key_size;
    scanf("%d", &key_size);

    char* key = (char*)malloc(key_size * sizeof(char));
    printf("Enter the of Key.\n");
    scanf("%s", key);
    int inv;

    for(int i=0; i<characters-1; i++)
    {
        if(cipherText[i] == ' ')
        {
            plainText[i] = ' ';
            continue;
        }
        inv = additiveInverse(key[i%key_size] - 65, mod);
        plainText[i] = (char)((cipherText[i] - 65 + inv)% mod + 97);
    }

    printf("\nCipher Text : %s", cipherText);
    printf("Plain Text : %s\n", plainText);
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
    
    //printf("Enter the value of mod.\n");
    //scanf("%d", &mod);
    mod = 26;

    printf("Enter the Size of the Key.\n");
    int key_size;
    scanf("%d", &key_size);

    char* key = (char*)malloc(key_size * sizeof(char));

    printf("Enter the of Key.\n");
    scanf("%s", key);
    int prev = (int)plainText[0];

    for(int i=0; i<characters-1; i++)
    {
        if(plainText[i] == ' ')
        {
            cipherText[i] = ' ';
            continue;
        }
        cipherText[i] = (char)((plainText[i] - 97 + key[i%key_size] - 65)% mod + 65);
    }

    printf("\nPlain Text : %s", plainText);
    printf("Cipher Text : %s\n", cipherText);
    printf("\n");
}

int main()
{
    int ch = 0;
    while(ch != 3)
    {
        printf("\n************* Demonstration of Vigenere Cipher *************\n");
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