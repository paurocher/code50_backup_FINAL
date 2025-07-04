#include <cs50.h>
#include <stdio.h>

bool validate_card(long card_number);
void get_card_company(long card_number);

int main(void)
{
    long card_number = get_long("Card number: ");
    if (validate_card(card_number))
    {
        get_card_company(card_number);
    }
}

bool validate_card(long card_number)
{
    bool is_pair = false; // used to discern odd and pairs in the loop
    int pairs = 0;
    int odds = 0;
    int number_length = 0;

    // loops through all the digits of card_number
    while (card_number > 0)
    {
        number_length++;
        int num = (card_number % 10);   // last digit
        card_number = card_number / 10; // remove last digit
        // if pair double it and add it to pairs_doubled
        if (is_pair)
        {
            int doubled = num * 2;
            // split digits and add
            if (doubled > 9)
            {
                pairs += doubled % 10;
                doubled = doubled / 10;
            }
            pairs += doubled;
        }
        // if not pair do not double it and add it to odds
        else
        {
            // printf("  odd %i\n", num);
            odds += num;
        }
        is_pair = !is_pair;
    }

    if (number_length != 13)
    {
        if (number_length != 15)
        {
            if (number_length != 16)
            {
                printf("INVALID\n");
                return false;
            }
        }
    }

    // add the results to get the number of truth
    int result = pairs + odds;

    // the veredict
    if (result % 10 == 0)
    {
        return true;
    }
    else
    {
        printf("INVALID\n");
        return false;
    }
}

void get_card_company(long card_number)
{
    long header = card_number;
    int number_length = 2;
    while (header > 99) // get the first 2 digits
    {
        number_length++;
        header = header / 10;
    }

    // assign the card to a company based on the first 2 digits
    if (header == 34 || header == 37)
    {
        if (number_length == 15)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (header >= 51 && header <= 55)
    {
        if (number_length == 16)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (header / 10 == 4)
    {
        if (number_length == 13 || number_length == 16)
        {
            printf("VISA\n");
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
