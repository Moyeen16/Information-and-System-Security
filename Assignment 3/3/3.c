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
 

void matrixMultiply(int** a, char** b, int** c, int rows, int columns, char ch)
{
    int mod = 26;
    int norm = 0;
    if(ch == 'e')
        norm = 97;
    else
        norm = 65;
    for(int i=0; i<rows; i++)    
    {    
        for(int j=0; j<columns; j++)    
        {    
            c[i][j]=0;    
            for(int k=0;k<columns;k++)
            {
                c[i][j] += a[k][j]*(b[i][k]-norm);
                if(c[i][j] < 0)
                    c[i][j] = mod - abs(c[i][j])%mod;
                else
                    c[i][j] = c[i][j] % mod;
                c[i][j] = c[i][j] % mod;
            }
        }    
    } 
}

void encrypt()
{
    printf("\n************* Encryption *************\n");
    int mod, blockSize;
    mod = 26;
    char *plainText;
    size_t bufsize = 100;
    size_t characters;

    plainText = (char *)malloc(bufsize * sizeof(char));
    printf("Enter the Plain Text.\n");
    characters = getline(&plainText, &bufsize, stdin);


    printf("Enter the Size of the Key.\n");
    int key_size;
    scanf("%d", &key_size);
    blockSize = key_size;
    int* key_text = (int*)malloc(key_size * sizeof(int));

    printf("Enter the of Permutation Key.\n");
    printf(" ");
    for(int i=0; i<key_size; i++)
        printf("%d ", i+1);
    printf("\n ");
    for(int i=0; i<key_size; i++)
        scanf("%d", &key_text[i]);

    
    int columns = blockSize;
    float rows = ceil((characters-1)*1.0/columns);
    char** plainTextMatrix = (char**)malloc(rows * sizeof(char*));
    int** cipherTextMatrix = (int**)malloc(rows * sizeof(int*));
    for(int i=0; i<rows; i++)
    {
        plainTextMatrix[i] = (char*)malloc(columns * sizeof(char));
        cipherTextMatrix[i] = (int*)malloc(columns * sizeof(int));
        for(int j=0; j<columns; j++)
        {
            plainTextMatrix[i][j] = 'z';
            cipherTextMatrix[i][j] = 0;
        }
    }
    int pos = 0;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<columns; j++)
        {
            if(pos < characters-1)
                plainTextMatrix[i][j] = plainText[pos++];
            else
                break;
        }
    }
    fflush(stdin);
    fflush(stdin);
    int** key = (int**)malloc(columns * sizeof(int*));
    char ch;
    for(int i=0; i<columns; i++)
    {
        key[i] = (int*)malloc(columns * sizeof(int));
        for(int j=0; j<columns; j++)
        {
            key[i][j] = 0;
            fflush(stdin);
            fflush(stdin);
        }
    }
    for(int i=0; i<key_size; i++)
        key[key_text[i]-1][i] = 1;

    printf("Key Matrix Formed :\n");
    for(int i=0; i<columns; i++)
    {
        for(int j=0; j<columns; j++)
            printf("%d ", key[i][j]);
        printf("\n");
    }
    
    //int det = determinant(key, columns);
    
    //int mulInv = multiplicativeInverse(det, mod);
    int mulInv = 1;
    if(mulInv == 0)
    {
        printf("Key is Not Invertible.\n");
        //return;
    }
    matrixMultiply(key, plainTextMatrix, cipherTextMatrix, rows, columns, 'e');
    printf("Encrypted Text : ");
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<columns; j++)
            printf("%c", cipherTextMatrix[i][j]+65);
    }
    printf("\n");
    
}

void decrypt()
{
    printf("\n************* Decryption *************\n");
    int mod = 26, blockSize;

    char *cipherText;
    size_t bufsize = 100;
    size_t characters;

    cipherText = (char *)malloc(bufsize * sizeof(char));
    printf("Enter the Cipher Text.\n");
    characters = getline(&cipherText, &bufsize, stdin);
    
    printf("Enter the Size of the Key.\n");
    int key_size;
    scanf("%d", &key_size);
    blockSize = key_size;
    int* key_text = (int*)malloc(key_size * sizeof(int));

    printf("Enter the of Permutation Key.\n");
    printf(" ");
    for(int i=0; i<key_size; i++)
        printf("%d ", i+1);
    printf("\n ");
    for(int i=0; i<key_size; i++)
        scanf("%d", &key_text[i]);
    
    int columns = blockSize;
    float rows = ceil((characters-1)*1.0/columns);
    char** cipherTextMatrix = (char**)malloc(rows * sizeof(char*));
    int** plainTextMatrix = (int**)malloc(rows * sizeof(int*));
    for(int i=0; i<rows; i++)
    {
        cipherTextMatrix[i] = (char*)malloc(columns * sizeof(char));
        plainTextMatrix[i] = (int*)malloc(columns * sizeof(int));
        for(int j=0; j<columns; j++)
        {
            cipherTextMatrix[i][j] = 'Z';
            plainTextMatrix[i][j] = 0;
        }
    }
    int pos = 0;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<columns; j++)
        {
            if(pos < characters-1)
                cipherTextMatrix[i][j] = cipherText[pos++];
            else
                break;
        }
    }
    fflush(stdin);
    fflush(stdin);

    int* inv = (int*)malloc(key_size * sizeof(int));
    permutation_invert(key_text, key_size, inv);

    int** key = (int**)malloc(columns * sizeof(int*));
    char ch;
    for(int i=0; i<columns; i++)
    {
        key[i] = (int*)malloc(columns * sizeof(int));
        for(int j=0; j<columns; j++)
        {
            key[i][j] = 0;
            fflush(stdin);
            fflush(stdin);
        }
    }
    for(int i=0; i<key_size; i++)
        key[inv[i]-1][i] = 1;

    //int det = determinant(key, columns);
    
    //int mulInv = multiplicativeInverse(det, mod);
    int mulInv = 1;
    if(mulInv == 0)
    {
        printf("Key is Not Invertible.\n");
        //return;
    }

    //matrixInverse(key, keyInverse, columns);
    matrixMultiply(key, cipherTextMatrix, plainTextMatrix, rows, columns, 'd');

    printf("Plain Text : ");
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<columns; j++)
            printf("%c", plainTextMatrix[i][j]+97);
    }
    printf("\n");
}

int main()
{
    int ch = 0;
    while(ch != 3)
    {
        printf("\n************* Demonstration of Transposition Cipher as Hill Cipher *************\n");
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