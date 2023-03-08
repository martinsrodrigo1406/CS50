#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>


int main(int argc, char *argv[])
{

    int input = 0;

    if(argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        for(int n = strlen(argv[1]), decimalMultiplier = 1; n > 0; n--)
        {
            if(isdigit(argv[1][n - 1]) == 0) //se o char não representa um digito
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
            else
            {
                input += ((int)argv[1][n - 1] - 48) * decimalMultiplier;
               // printf("%i\n", (int)argv[1][n - 1]);
                decimalMultiplier *= 10;
            }

        }

        string plaintext = "";

        do
        {
            plaintext = get_string("plaintext: ");
        }
        while ((strcmp(plaintext, "") == 0) || (strcmp(plaintext, " ") == 0));

        long textLen = strlen(plaintext);
        char ciphertext[textLen];

        for (long i = 0, n = textLen; i < n; i++)
        {
            char pci = plaintext[i];

            if(isalpha(pci) != 0)
            {
                if(isupper(pci) == 0) //se não for letra maiúscula
                {

                    int calc = (int)pci - 97;
                    calc = (calc + input) % 26;
                    calc += 97;

                    int cco = (char)calc;

                    ciphertext[i] = (char)cco;
                    ciphertext[i] = tolower(ciphertext[i]);
                }
                else
                {

                    int calc = (int)pci - 65;
                    calc = (calc + input) % 26;
                    calc += 65;
                    int cco = (char)calc;
                    printf("%d\n", calc);
                    ciphertext[i] = (char)cco;
                    ciphertext[i] = toupper(ciphertext[i]);
                }

            }
            else
            {
                ciphertext[i] = pci;
            }

        }


printf("ciphertext: ");
    for (int i = 0; i < strlen(ciphertext); i++)
    {
        printf("%c", ciphertext[i]);
    }
printf("\n");

    return 0;
    }
}








