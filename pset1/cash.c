#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main()
{
    float amount;
    int dom[4]={25,10,5,1} ,num[4]={0,0,0,0}, coins = 0;
    do
    {
    amount = get_float("Change owed : ");
    } while (amount < 0);
    int x = round(amount * 100);
    for(int i=0;i<4;i++){
        while(x>=dom[i]){
            x-=dom[i];
            num[i]++;
        }
        coins += num[i];
    }
    printf("%i\n",coins);
    return 0;
}
