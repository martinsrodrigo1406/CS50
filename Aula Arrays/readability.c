#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int main(void)
{
    string text;
    do
    {
        text = get_string("Insira o texto: ");
    } while(strlen(text) <= 0);


    long letras = 0;
    int palavras = 1;
    int frases = 0;



    for(int i = 0, n = strlen(text); i <= n; i++)
    {
        if(isalpha(text[i]) != 0)
        {
            letras++;
        }
        if(((int)text[i] == 33) || ((int)text[i] == 46) || ((int)text[i] == 63))
        {
            frases++;
        }
        if((int)text[i] == 32)
        {
            palavras++;
        }

    }

    float l;
    float s;
    float grade;

    double averageWordsN = 0;
    averageWordsN = palavras / 100.0;

    l = letras / averageWordsN;
    s = frases / averageWordsN;

    grade = (0.0588 * l) - (0.296 * s) - 15.8;

    if(grade >= 16.0)
    {
        printf(" Letras: %ld\n Frases: %d\n Palavras: %d\n Letras por cada 100 palavras: %.2f\n Frases por cada 100 palavras: %.2f\n Grade: 16+\n", letras, frases, palavras, l, s);
    }
    else if(grade < 1.0)
    {
        printf(" Letras: %ld\n Frases: %d\n Palavras: %d\n Letras por cada 100 palavras: %.2f\n Frases por cada 100 palavras: %.2f\n Before Grade 1\n", letras, frases, palavras, l, s);

    }
    else
    printf(" Letras: %ld\n Frases: %d\n Palavras: %d\n Letras por cada 100 palavras: %.2f\n Frases por cada 100 palavras: %.2f\n Grade: %.0f\n", letras, frases, palavras, l, s, round(grade));


    return 0;
}