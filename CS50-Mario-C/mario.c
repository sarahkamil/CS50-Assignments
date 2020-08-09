#include <cs50.h>
#include <stdio.h>

int main(void)
{
   int height;
    do
    {
        height = get_int("Size: ");
    }
    while (height < 1 || height > 8);

    for(int i = height; i > 0; i--)
    {
        for(int j = 1; j < i; j++)
        {
            printf(" ");
        }
        int num_hash = height + 1 - i;

        for(int k = 0; k < num_hash; k++)
        {
            printf("#");
        } 
            
        printf("\n");
    }
}  
