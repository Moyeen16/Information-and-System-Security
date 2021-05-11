#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void compute(int* a, int* b, int q)
{
    int tmp = *b;
    *b = *a - q * (*b);
    *a = tmp;
}
int multiplicativeInverse(int a, int b)
{
    int tmp, idx=0;
    int r1=a,r2=b,s1=1,s2=0, t1=0,t2=1;
    while(r2!=0)
    {
        int q=r1/r2;
        compute(&r1,&r2,q);
        compute(&s1,&s2,q);
        compute(&t1,&t2,q);
    }
    if(r1==1)
        return (s1%b+b)%b ; 
    else
        return 0;
}

void getCofactor(int** arr, int** temp, int p, int q, int m) 
{ 
    
    int i = 0, j = 0; 
    

    for (int row = 0; row < m; row++) 
    { 
        for (int col = 0; col < m; col++) 
        { 
            if (row != p && col != q) 
            { 
                temp[i][j++] = arr[row][col]; 
                if (j == m - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
} 

int determinant(int** A, int n) 
{ 
    
    int D = 0; // Initialize result 
  
    
    if (n == 1) 
        return A[0][0]; 
  
    
    int **temp = (int**)malloc(n*sizeof(int*));
    for(int i=0; i<n; i++)
        temp[i] = (int*)malloc(n*sizeof(int));


    int sign = 1;
  
    for (int f = 0; f < n; f++) 
    { 
        getCofactor(A, temp, 0, f, n); 
        D += sign * A[0][f] * determinant(temp, n-1); 
        sign = -sign; 
    } 
  
    return D; 
}   

void adjoint(int** A, int** adj, int n) 
{ 
    if (n == 1) 
    { 
        adj[0][0] = 1; 
        return; 
    } 

    int sign = 1;
    int **temp = (int**)malloc(n*sizeof(int*));
    for(int i=0; i<n; i++)
        temp[i] = (int*)malloc(n*sizeof(int));

    for (int i=0; i<n; i++) 
    { 
        for (int j=0; j<n; j++) 
        { 
            getCofactor(A, temp, i, j, n); 
            sign = ((i+j)%2==0)? 1: -1; 
            adj[j][i] = (sign)*(determinant(temp, n-1)); 
        } 
    }
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
            for(int k=0;k<rows;k++)
            {
                c[i][j] += a[i][k]*(b[k][j]-norm);
                if(c[i][j] < 0)
                    c[i][j] = mod - abs(c[i][j])%mod;
                else
                    c[i][j] = c[i][j] % mod;
                c[i][j] = c[i][j] % mod;
            }
        }    
    } 
}

void matrixInverse(int** arr, int** adj, int m)
{
    int mod = 26;
    adjoint(arr, adj, m);

    int det = determinant(arr, m);
    
    int inv = multiplicativeInverse(det, mod);
    if(inv == -1)
    {
        printf("Inverse does not exist.");
        return;
    }
    
    //printf("---------------Inverse Matrix---------------\n");
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(adj[i][j]<=0)
                adj[i][j] = mod - abs(adj[i][j]) % mod;
            else
                adj[i][j] = adj[i][j] % mod;
            adj[i][j] = adj[i][j] * inv;
            adj[i][j] = adj[i][j] % mod;
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

    printf("Enter the Block Size\n");
    scanf("%d", &blockSize);
    
    int rows = blockSize;
    float columns = ceil((characters-1)*1.0/rows);
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
    for(int i=0; i<columns; i++)
    {
        for(int j=0; j<rows; j++)
        {
            if(pos < characters-1)
                plainTextMatrix[j][i] = plainText[pos++];
            else
                break;
        }
    }
    fflush(stdin);
    fflush(stdin);
    int** key = (int**)malloc(rows * sizeof(int*));
    printf("Enter the Key Matrix (%d x %d)\n", (int)rows, (int)rows);
    char ch;
    for(int i=0; i<rows; i++)
    {
        key[i] = (int*)malloc(rows * sizeof(int));
        for(int j=0; j<rows; j++)
        {
            scanf("%c", &ch);
            key[i][j] = (int)ch-65;
            fflush(stdin);
            fflush(stdin);
        }
    }
    int det = determinant(key, rows);
    
    int mulInv = multiplicativeInverse(det, mod);
    if(mulInv == 0)
    {
        printf("Key is Not Invertible.\n");
        return;
    }
    
    matrixMultiply(key, plainTextMatrix, cipherTextMatrix, rows, columns, 'e');
    printf("Encrypted Text : ");
    for(int i=0; i<columns; i++)
    {
        for(int j=0; j<rows; j++)
            printf("%c", cipherTextMatrix[j][i]+65);
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
    
    printf("Enter the Block Size\n");
    scanf("%d", &blockSize);
    
    int rows = blockSize;
    float columns = ceil((characters-1)*1.0/rows);
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
    for(int i=0; i<columns; i++)
    {
        for(int j=0; j<rows; j++)
        {
            if(pos < characters-1)
                cipherTextMatrix[j][i] = cipherText[pos++];
            else
                break;
        }
    }
    fflush(stdin);
    fflush(stdin);

    int** key = (int**)malloc(rows * sizeof(int*));
    printf("Enter the Key Matrix (%d x %d)\n", (int)rows, (int)rows);
    char ch;
    for(int i=0; i<rows; i++)
    {
        key[i] = (int*)malloc(rows * sizeof(int));
        for(int j=0; j<rows; j++)
        {
            scanf("%c", &ch);
            key[i][j] = (int)ch-65;
            fflush(stdin);
            fflush(stdin);
        }
    }

    int det = determinant(key, rows);
    
    int mulInv = multiplicativeInverse(det, mod);
    if(mulInv == 0)
    {
        printf("Key is Not Invertible.\n");
        return;
    }

    int** keyInverse = (int**)malloc(rows * sizeof(int*));
    for(int i=0; i<rows; i++)
    {
        keyInverse[i] = (int*)malloc(rows * sizeof(int));
        for(int j=0; j<rows; j++)
            keyInverse[i][j] = 0;
    } 

    matrixInverse(key, keyInverse, rows);
    matrixMultiply(keyInverse, cipherTextMatrix, plainTextMatrix, rows, columns, 'd');

    printf("Plain Text : ");
    for(int i=0; i<columns; i++)
    {
        for(int j=0; j<rows; j++)
            printf("%c", plainTextMatrix[j][i]+97);
    }
    printf("\n");
}

int main()
{
    int ch = 0;
    while(ch != 3)
    {
        printf("\n************* Demonstration of Hill Cipher *************\n");
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