#import <cs50.h>
#import <ctype.h>
#import <stdio.h>

int get_score(string word);
void print_result(int score_1, int score_2);
int check_string(string word);

int main(void)
{
    // Get the 2 words
    string word_1 = get_string("Player 1: ");
    string word_2 = get_string("Player 2: ");

    // get scores
    int score_1 = get_score(word_1);
    int score_2 = get_score(word_2);

    // print result
    print_result(score_1, score_2);
}

int get_score(string word)
{
    // scrabble letter value from a to z
    int letter_value[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    int letter = 0; // holds the int value of each char

    int score = 0; // keep track of sum of each letter
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (islower(word[i]))
        {
            // solve the index of the score list
            letter = word[i] - 'a';
        }
        else if (isupper(word[i]))
        {
            // solve the index of the score list
            letter = word[i] - 'A';
        }
        else
        {
            letter = 0;
        }
        score += letter_value[letter];
    }
    return score;
}

void print_result(int score_1, int score_2)
{
    if (score_1 == score_2)
    {
        printf("Tie!\n");
    }
    else if (score_1 > score_2)
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}
