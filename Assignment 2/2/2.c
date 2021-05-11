#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int additiveInverse(int inp, int mod)
{
    for(int i=0; i<mod; i++)
    {
        if((inp + i) % mod == 0)
            return i;
    }
    return 0;
}

int multiplicativeInverse(int inp, int mod)
{

    for(int i=0; i<mod; i++)
    {
        if((inp * i) % mod == 1)
            return i;
    }
    return 0;

}

void shiftCipher()
{
    char* plainText = (char*)malloc(100*sizeof(char));;
    char *cipherText;
    size_t bufsize = 100;
    size_t characters;


    cipherText = (char *)malloc(bufsize * sizeof(char));

    for(int i=0; i<100; i++)
        plainText[i] = '\0';

    printf("Enter the Cipher Text.\n");
    characters = getline(&cipherText, &bufsize, stdin);
    
    int mod = 26;
    //printf("Enter the value of mod.\n");
    //scanf("%d", &mod);

    printf("Plain Texts corresponding to keys...\n");
    for(int key = 0; key<mod; key++)
    {
        int inv = additiveInverse(key, mod);

        for(int i=0; i<characters-1; i++)
        {
            if(cipherText[i] == ' ')
            {
                plainText[i] = ' ';
                continue;
            }
            
            plainText[i] = (char)((cipherText[i] - 65 + inv)% mod + 97);
        }
        printf("Key = %d : %s\n\n", key, plainText);
    }
}

void multiplicativeCipher()
{
    char* plainText = (char*)malloc(100*sizeof(char));;
    char *cipherText;
    size_t bufsize = 100;
    size_t characters;


    cipherText = (char *)malloc(bufsize * sizeof(char));

    for(int i=0; i<100; i++)
        plainText[i] = '\0';

    printf("Enter the Cipher Text.\n");
    characters = getline(&cipherText, &bufsize, stdin);
    
    int mod = 26;
    //printf("Enter the value of mod.\n");
    //scanf("%d", &mod);

    printf("Plain Texts corresponding to keys...\n");
    for(int key = 0; key<mod; key++)
    {
        int inv = multiplicativeInverse(key, mod);
        if(inv == 0)
            continue;
        for(int i=0; i<characters-1; i++)
        {
            if(cipherText[i] == ' ')
            {
                plainText[i] = ' ';
                continue;
            }
            plainText[i] = (char)(((cipherText[i] - 65) * inv)% mod + 97);
        }
        printf("Key = %d : %s\n\n", key, plainText);
    }
}

void affineCipher()
{
    int mod, key1, key2;
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

    for(int key1 = 0; key1<mod; key1++)
    {
        for(int key2 = 0; key2<mod; key2++)
        {
            int addInv = additiveInverse(key2, mod);
            int mulInv = multiplicativeInverse(key1, mod);
            if(mulInv == 0)
                continue;
            for(int i=0; i<characters-1; i++)
            {
                if(cipherText[i] == ' ')
                {
                    plainText[i] = ' ';
                    continue;
                }
                
                plainText[i] = (char)((((cipherText[i] - 65) + addInv) * mulInv)% mod + 97);
            }
            printf("Key 1 = %d Key 2 = %d : %s\n", key1, key2, plainText);
        }
    }
    
}

int main()
{
    int ch = 0;
    while(ch != 4)
    {
        printf("\n************* Demonstration of Exhaustive Key Search Attack *************\n");
        printf("1. Shift Cipher\n");
        printf("2. Multiplicative Cipher\n");
        printf("3. Affine Cipher\n");
        printf("4. Exit\n");
        scanf("%d", &ch);
        fflush(stdin);
        fflush(stdin);

        switch(ch)
        {
            case 1 :
                shiftCipher();
                break;
            case 2 :
                multiplicativeCipher();
                break;
            case 3 :
                affineCipher();
                break;
            case 4 :
                printf("Thank You!\n\n");
                break;
            default:
                printf("Enter a Valid Choice.\n");
        }
    }
    return 0;
}