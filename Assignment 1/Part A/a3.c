#include <stdio.h>
#include <stdlib.h>

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

int mulInv(int inp, int n)
{
    for(int i=0; i<n; i++)
    {
        if((inp * i) % n == 1)
        {
            printf("Multiplicative Inverse of %d is %d.\n", inp, i);
            return i;
        }
    }
    return -1;
}

int main()
{
    int m;
    printf("Enter the dimension of the matrix.\n");
    scanf("%d", &m);

    int **arr = (int**)malloc(m*sizeof(int*));
    for(int i=0; i<m; i++)
        arr[i] = (int*)malloc(m*sizeof(int));

    printf("Enter the Elements into the array. \n");
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<m; j++)
            scanf("%d", &arr[i][j]);
    }

    printf("---------------Given Matrix---------------\n");
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<m; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
    printf("------------------------------------------\n");

    int mod;
    printf("Enter the mod value.\n");
    scanf("%d", &mod);

    int **adj = (int**)malloc(m*sizeof(int*));
    for(int i=0; i<m; i++)
        adj[i] = (int*)malloc(m*sizeof(int));
    adjoint(arr, adj, m);

    int det = determinant(arr, m);
    
    int inv = mulInv(det, mod);
    
    if(inv == -1)
    {
        printf("Inverse does not exist.\n");
        return 0;
    }
    
    printf("---------------Inverse Matrix---------------\n");
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
            
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
    printf("---------------------------------------------\n");
    return 0;
}