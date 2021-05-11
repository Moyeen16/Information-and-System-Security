#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void findRowCol(char t1, char t2, char** key, int* r1, int* c1, int* r2, int* c2, char ch)
{
    int t1r, t1c, t2r, t2c;
    if(t1 == 'j')
        t1 = 'i';
    if(t2 == 'j')
        t2 ='i';
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            if(key[i][j] == t1)
            {
                t1r = i;
                t1c = j;
            }
            if(key[i][j] == t2)
            {
                t2r = i;
                t2c = j;
            }
        }
    }
    if(ch == 'e')
    {
        if(t1c == t2c)
        {
            *r1 = (t1r + 1) % 5;
            *r2 = (t2r + 1) % 5;
            *c1 = t1c;
            *c2 = t2c;
        }
        else if(t1r == t2r)
        {
            *c1 = (t1c + 1) % 5;
            *c2 = (t2c + 1) % 5;
            *r1 = t1r;
            *r2 = t2r;
        }
        else
        {
            *c1 = t2c;
            *r1 = t1r;
            *c2 = t1c;
            *r2 = t2r;
        }
    }
    else if(ch == 'd')
    {
        if(t1c == t2c)
        {
            *r1 = (5 + (t1r - 1)) % 5;
            *r2 = (5 + (t2r - 1)) % 5;
            *c1 = t1c;
            *c2 = t2c;
        }
        else if(t1r == t2r)
        {
            *c1 = (5 + (t1c - 1)) % 5;
            *c2 = (5 + (t2c - 1)) % 5;
            *r1 = t1r;
            *r2 = t2r;
        }
        else
        {
            *c1 = t2c;
            *r1 = t1r;
            *c2 = t1c;
            *r2 = t2r;
        }
    }
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
    
    char** key = (char **)malloc(5 * sizeof(char*));
    for(int i=0; i<5; i++)
        key[i] = (char *)malloc(5 * sizeof(char));

    printf("Enter the Key Matrix in Row Order\n");
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            scanf("%c", &key[i][j]);
            fflush(stdin);
            fflush(stdin);
        }
    }

    //printf("Enter the value of mod.\n");
    //scanf("%d", &mod);
    mod = 26;

    for(int i=1; i<characters-1; i += 2)
    {
        int r1 = -1, r2 = -1;
        int c1 = -1, c2 = -1;
        findRowCol(cipherText[i-1], cipherText[i], key, &r1, &c1, &r2, &c2, 'd');
    
        plainText[i-1] = (char)(key[r1][c1] - 65 + 97);
        plainText[i] = (char)(key[r2][c2] - 65 + 97);
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
    
    char** key = (char **)malloc(5 * sizeof(char*));
    for(int i=0; i<5; i++)
        key[i] = (char *)malloc(5 * sizeof(char));

    printf("Enter the Key Matrix in Row Order\n");
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            scanf("%c", &key[i][j]);
            fflush(stdin);
            fflush(stdin);
        }
    }


    //printf("Enter the value of mod.\n");
    //scanf("%d", &mod);
    mod = 26;

    for(int i=1; i<characters-1; i += 2)
    {
        int r1 = -1, r2 = -1;
        int c1 = -1, c2 = -1;
        findRowCol((char)(plainText[i-1] - 97 + 65), (char)(plainText[i] - 97 + 65), key, &r1, &c1, &r2, &c2, 'e');
    
        cipherText[i-1] = key[r1][c1];
        cipherText[i] = key[r2][c2];
    }
    if(characters % 2 == 0)
    {
        int i = (int)characters-1;
        int r1 = -1, r2 = -1;
        int c1 = -1, c2 = -1;
        findRowCol((char)(plainText[i-1] - 97 + 65), 'Z', key, &r1, &c1, &r2, &c2, 'e');
    
        cipherText[i-1] = key[r1][c1];
        cipherText[i] = key[r2][c2];
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
        printf("\n************* Demonstration of Playfair Cipher *************\n");
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

/*
A
B
C
D
E
F
G
H
I
K
L
M
N
O
P
Q
R
S
T
U
V
W
X
Y
Z
*/