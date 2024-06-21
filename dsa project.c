#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRIES 6

void clearScreen();
void printMan(int);
void printWord(const char[], const char[]);
int getGuess(char[]);

int main()
{
    char words[][15] = {"banana","pomegranate","nectarine","grape","strawberry","kiwi","melon","peach","pear","watermelon","mango","papaya","cherry","blackberry","pineapple"};
    int num_of_words = sizeof(words) / sizeof(words[0]);
    srand(time(NULL));
    int i;
    int random_word = rand() % num_of_words;
    int length = strlen(words[random_word]);
    char display[length + 1];
    char used[26];
    int tries = 0;
    int correct_guesses = 0;
    for ( i = 0; i < length; i++)
    {
        display[i] = '_';
    }
    display[length] = '\0';
    for (i = 0; i < 26; i++)
    {
        used[i] = '\0';
    }
    clearScreen();
    while (tries < MAX_TRIES && correct_guesses < length)
    {
        printMan(tries);
        printWord(display, used);
        char guess = getGuess(used);
        int good_guess = 0;
        for (i = 0; i < length; i++)
        {
            if (guess == words[random_word][i])
            {
                display[i] = guess;
                ++correct_guesses;
                good_guess = 1;
            }
        }
        if (!good_guess)
        {
            ++tries;
        }
        clearScreen();
    }
    printMan(tries);
    if (correct_guesses == length)
    {
        printf("\n\nCongratulations! You won! The word was ~ *%s*\n", words[random_word]);
    }
    else
    {
        printf("\n\nSorry, you lost. The word was %s\n", words[random_word]);
    }
    return 0;
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printMan(int tries)
{
    switch (tries)
    {
    case 0:
        printf("\n\n\n\n\n\n");
        break;
    case 1:
        printf("\n\n\n\n\n O\n");
        break;
    case 2:
        printf("\n\n\n\n\n O\n |\n");
        break;
    case 3:
        printf("\n\n\n\n\n O\n/|\n");
        break;
    case 4:
        printf("\n\n\n\n\n O\n/|\\\n");
               break;
    case 5:
        printf("\n\n\n\n\n O\n/|\\\n/\n");
        break;
    case 6:
        printf("\n\n\n\n\n O\n/|\\\n/ \\\n");
        break;
    }
}

void printWord(const char display[], const char used[])
{
    printf("\n\nCurrent word: ");
    int i;
    for ( i = 0; i < strlen(display); i++)
    {
        printf("%c ", display[i]);
    }
    printf("\n\nUsed letters: ");
    for ( i = 0; i < 26; i++)
    {
        if (isalpha(used[i]))
        {
            printf("%c ", used[i]);
        }
    }
    printf("\n\n\nGuess a letter: ");
}

int getGuess( char used[])
{
    char guess;
    int i;
    int good_input = 0;
    while (!good_input)
    {
        scanf(" %c", &guess);
        guess = tolower(guess);
        if (isalpha(guess) && !strchr(used, guess))
        {
            good_input = 1;
        }
        else
        {
            printf("Invalid input, try again: ");
        }
    }
    for ( i = 0; i < 26; i++)
    {
        if (used[i] == '\0')
        {
            used[i] = guess;
            break;
        }
    }
    return guess;
}
