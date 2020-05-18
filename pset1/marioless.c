#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h,i,j;
    do
    {
        h = get_int("Height: ");
    }
    while (h<1 || h>8);
    for(i=1;i<=h;i++)
    {
        for(j=h-i;j>0;j--)
            printf(" ");
        for(j=1;j<=i;j++)
            printf("#");
        printf("\n");
    }
}
