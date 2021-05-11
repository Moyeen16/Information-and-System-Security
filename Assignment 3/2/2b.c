#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int* permutation_invert(int* key, int key_size, int* inv)
{
    for(int i=0; i<key_size; i++)
        inv[key[i]-1] = i+1;
    return inv;
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

    int* key = (int*)malloc(key_size * sizeof(int));

    printf("Enter the of Permutation Key.\n");
    printf(" ");
    for(int i=0; i<key_size; i++)
        printf("%d ", i+1);
    printf("\n ");
    for(int i=0; i<key_size; i++)
        scanf("%d", &key[i]);
    int* inv = (int*)malloc(key_size * sizeof(int));
    permutation_invert(key, key_size, inv);
    for(int i=0; i<characters-1; i++)
    {
        if(cipherText[i] == ' ')
        {
            plainText[i] = ' ';
            continue;
        }
        int new_pos = inv[i%key_size] - 1;
        plainText[i] = (char)(cipherText[(i/key_size)*key_size + new_pos] - 65 + 97);
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

    int* key = (int*)malloc(key_size * sizeof(int));
    int req_size = key_size * (int)ceil((characters-1)*1.0/key_size);
    //printf("check %d\n", req_size);
    for(int i=0; i<req_size-characters+1; i++)
        plainText[characters-1+i] = 'z';
    printf("Enter the of Permutation Key.\n");
    printf(" ");
    for(int i=0; i<key_size; i++)
        printf("%d ", i+1);
    printf("\n ");
    for(int i=0; i<key_size; i++)
        scanf("%d", &key[i]);
    
    characters = req_size+1;
    for(int i=0; i<characters-1; i++)
    {
        if(plainText[i] == ' ')
        {
            cipherText[i] = ' ';
            continue;
        }
        int new_pos = key[i%key_size] - 1;
        cipherText[i] = (char)(plainText[(i/key_size)*key_size + new_pos] - 97 + 65);
    }
    printf("\nPlain Text : %s\n", plainText);
    printf("Cipher Text : %s\n", cipherText);
    printf("\n");
}

int main()
{
    int ch = 0;
    while(ch != 3)
    {
        printf("\n************* Demonstration of Keyed Transposition Cipher *************\n");
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