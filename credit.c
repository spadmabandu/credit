#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    //AMEX 15 digit; start with 34 or 37
    //MasterCard 16 digit; start with 51, 52, 53, 54, or 55
    //VISA 13 and 16 digit; start with 4

    long credit = get_long("Credit Card Number:\n");

    char str[256];
    sprintf(str, "%ld", credit);

    int length = strlen(str);
    //printf("Length: %i\n", length);

    int validation = 0;
    int validation_two = 0;
    int validation_final = 0;

    for (int i = 0; i < length; i = i + 2) //iterate by 2 to obtain every other digit
    {
        long r = credit / pow(10, i + 1); //divide the credit card number by 10^(i+1) to get the first (i+1) digits
        r = r % 10; //Compute the modular of that to isolate the (i+1)th digit
        if (r * 2 >= 10 && r * 2 < 100) //if the digit doubled is greater than 10, compute the sum of the digits
        {
            int x = r * 2 / 10;
            int y = r * 2 % 10;
            validation = validation + x + y;
        }
        else
        {
            validation = validation + 2 * r; //otherwise add the digit to the validation sum
        }
    }

    for (int j = 0; j < length; j = j + 2)
    {
        long s = credit / pow(10, j); //divide the credit card number by 10^j to get the first j digits
        s = s % 10; //compute the modular of the result to isolate the jth digit
        validation_two = validation_two + s; //add the digit to the validation sum
    }
    //printf("Validation: %i\n", validation);
    //printf("Validation_Two: %i\n", validation_two);
    validation_final = validation + validation_two;
    //printf("Validation_Final: %i\n", validation_final);

    int first_digit = credit / pow(10, length - 1);
    int first_two_digits = credit / pow(10, length - 2);

    // printf("First Digit: %i\n", first_digit);
    // printf("First Two Digits: %i\n", first_two_digits);

    if (validation_final % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        if (length == 16)
        {
            if (first_digit == 4)
            {
                printf("VISA\n");
            }
            else if (first_two_digits == 51 || first_two_digits == 52 || first_two_digits == 53 || first_two_digits == 54
                     || first_two_digits == 55)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (length == 13 && first_digit == 4)
        {
            printf("VISA\n");
        }
        else if (length == 15)
        {
            if (first_two_digits == 34 || first_two_digits == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
