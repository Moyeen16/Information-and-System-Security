#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void key_mixing(int* inputText, int* outputText, int* key, int round, int block_size)
{
    int start = 4*round - 3 - 1;
    int end = 4*round + 1 - 1;
    for(int i=0; i<block_size; i++)
        outputText[i] = inputText[i] ^ key[start+i];
}

void s_box(int* inputText, int* outputText, int* substitution_func, int start, int end)
{
    int temp=0;
    int temp2=0;

    for(int i=end; i>=start; i--)
        temp += inputText[i] * (int)pow(2,end-i);
    for(int i=end; i>=start;i--)
        outputText[i] = 0;
    temp2 = substitution_func[temp];
    for(int i=end;temp2>0;i--)    
    {    
        outputText[i] = temp2%2;    
        temp2 = temp2/2;    
    }

    
}

void p_box(int* inputText, int* outputText, int* permutation_func, int block_size)
{
    for(int i=0; i<block_size; i++)
        outputText[i] = inputText[permutation_func[i]-1];
}

void compute(int* permutation_key, int*substitution_func, char ch)
{
    printf("\n************* SP Module *************\n");
    int inputText_size = 0;
    int block_size = 8;
    int* inputText = (int*)malloc(8*sizeof(int));
    int* inputText_copy = (int*)malloc(8*sizeof(int)); 
    int* outputText = (int*)malloc(8*sizeof(int));
    int* interText1 = (int*)malloc(8*sizeof(int));
    int* interText2 = (int*)malloc(8*sizeof(int));
    int* interText3 = (int*)malloc(8*sizeof(int));

    char *inputText_str;
    size_t bufsize = inputText_size+1;
    inputText_str = (char *)malloc(bufsize * sizeof(char));
    size_t characters;
    printf("Enter the Input Text.\n");
    characters = getline(&inputText_str, &bufsize, stdin);
    inputText_size = characters-1;

    char *key_str;
    int key_size = 24;
    bufsize = 25;
    key_str = (char *)malloc(bufsize * sizeof(char));
    size_t characters2;
    printf("Enter the Key (%d bit key)\n", key_size);
    characters2 = getline(&key_str, &bufsize, stdin);

    int* key = (int*)malloc(key_size * sizeof(int));
    for(int i=0; i<key_size; i++)
        key[i] = (int)key_str[i]-48;

    int number_of_rounds = 4;
    int number_of_blocks = (int)ceil(inputText_size * 1.0 / block_size);
    int* full_inputText = (int*)malloc(number_of_blocks*8*sizeof(int));
    int* full_outputText = (int*)malloc(number_of_blocks*8*sizeof(int));
    int number_of_bogus = number_of_blocks*8 - inputText_size;
    
    for(int i=0; i<number_of_blocks*8; i++)
    {
        full_inputText[i] = 0;
        full_outputText[i] = 0;
    }
    for(int i=0; i<=inputText_size; i++)
        full_inputText[number_of_bogus+i] = inputText_str[i]-48;

    //For each Block
    for(int bl=1; bl<=number_of_blocks; bl++)
    {
        printf("\n*****Block Number %d*****\n", bl);
        for(int i=0; i<block_size; i++)
        {
            inputText[i] = full_inputText[8*(bl-1)+i];
            inputText_copy[i] = inputText[i];
            inputText_copy[i] = 0; 
            outputText[i] = 0;
            interText1[i] = 0;
            interText2[i] = 0;
            interText3[i] = 0;
        }
        for(int j=0; j<8; j++)
            printf("%d ", inputText[j]);
        printf("\n");
        
        //Encryption
        if(ch == 'e')
        {
            for(int i=1; i<=number_of_rounds; i++)
            {
                key_mixing(inputText, interText1, key, i, block_size);
                s_box(interText1, interText2, substitution_func, 0, 3);
                s_box(interText1, interText2, substitution_func, 4, 7);
                if(i != number_of_rounds)
                {
                    p_box(interText2, inputText, permutation_key, block_size);
                    
                    printf("*****Round %d*****\n", i);
                    for(int j=0; j<8; j++)
                        printf("%d ", inputText[j]);
                    printf("\n");
                }
            }
            key_mixing(interText2, outputText, key, number_of_rounds+1, block_size);
            printf("*****Round %d*****\n", 4);
                for(int j=0; j<8; j++)
                    printf("%d ", outputText[j]);
                printf("\n");
        }
        //Encryption Ends

        //Decryption
        else if(ch == 'd')
        {
            key_mixing(inputText, outputText, key, number_of_rounds+1, block_size);
            for(int i=number_of_rounds; i>=1; i--)
            {
                
                if(i != number_of_rounds)
                {
                    p_box(outputText, interText2, permutation_key, block_size);
                    s_box(interText2, interText3, substitution_func, 0, 3);
                    s_box(interText2, interText3, substitution_func, 4, 7);
                    key_mixing(interText3, outputText, key, i, block_size);
                }
                else
                {
                    s_box(outputText, interText1, substitution_func, 0, 3);
                    s_box(outputText, interText1, substitution_func, 4, 7);
                    key_mixing(interText1, outputText, key, i, block_size);
                }
                printf("*****Round %d*****\n", number_of_rounds - i + 1);
                for(int j=0; j<8; j++)
                    printf("%d ", outputText[j]);
                printf("\n");
                
            }
        }
        //Decryption Ends

        for(int i=0; i<block_size; i++)
            full_outputText[8*(bl-1) + i] = outputText[i];
    }
    //Block ends

    printf("\n\nInput Text :\t");
    for(int i=0; i<8*number_of_blocks; i++)
        printf("%d ", full_inputText[i]);
    printf("\n");
    printf("Output Text :\t");
    for(int i=0; i<8*number_of_blocks; i++)
        printf("%d ", full_outputText[i]); 
    printf("\n");
}

int main()
{
    int ch = 0;

    int* permutation_key = (int*)malloc(8 * sizeof(int));
    int* substitution_func = (int*)malloc(16 * sizeof(int));

    int* inv_permutation_key = (int*)malloc(8 * sizeof(int));
    int* inv_substitution_func = (int*)malloc(16 * sizeof(int));  
    
    printf("\nEnter the of Substitution Key.\n");
    printf(" ");
    for(int i=0; i<16; i++)
        printf("%d ", i);
    printf("\n ");
    for(int i=0; i<16; i++)
        scanf("%d", &substitution_func[i]);
    printf("\n");
    printf("Enter the of Permutation Key.\n");
    printf(" ");
    for(int i=0; i<8; i++)
        printf("%d ", i+1);
    printf("\n ");
    for(int i=0; i<8; i++)
        scanf("%d", &permutation_key[i]);
    printf("\n");

    for(int i=0; i<16; i++)
        inv_substitution_func[substitution_func[i]] = i; 
    for(int i=0; i<8; i++)
        inv_permutation_key[permutation_key[i]-1] = i+1;

    while(ch != 3)
    {
        printf("\n************* Demonstration of Substitution Permutation Cipher *************\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
        scanf("%d", &ch);
        fflush(stdin);
        fflush(stdin);

        switch(ch)
        {
            case 1 :
                compute(permutation_key, substitution_func, 'e');
                break;
            case 2:
                compute(inv_permutation_key, inv_substitution_func, 'd');
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