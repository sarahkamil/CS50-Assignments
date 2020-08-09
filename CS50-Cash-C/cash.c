#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);

    int cents = round(change * 100);
    int rem_change = cents;
    int coins_used = 0;

    while (rem_change > 0) {
        if (rem_change >= 25) {
            rem_change = rem_change - 25;
            coins_used++;
        } else if (rem_change >= 10) {
            rem_change = rem_change - 10;
            coins_used++;
        } else if (rem_change >= 5) {
            rem_change = rem_change - 5;
            coins_used++;
        } else if (rem_change >= 1) {
            rem_change = rem_change - 1;
            coins_used++;
        }     
    }
    printf("%i \n", coins_used);
}
