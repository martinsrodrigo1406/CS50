#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>


int main(int argc, char *argv[])
{

    int input = 0;
    char subKey[26];
    int diff[26];
    if(argc != 2)
    {
        printf("Uso: ./substitution chave_de_substituição\n");
        return 1;
    }
    else
    {
        if(strlen(argv[1]) != 26)
        {
            printf("A chave deve conter 26 caracteres.\n");
            return 1;
        }
        else
        {
            int ascNumCmp = 65;
            for(int i = 0; i < 26; i++)
            {
                if(isalpha(argv[1][i]) == 0) //se o char não representa apenas letras
                {
                    printf("A chave deve conter somente letras.\n");
                    return 1;
                }
                else
                {
                    int repeatedLetter = 0;
                    subKey[i] = toupper(argv[1][i]);
                    for(int z = 0; z < 26; z++)
                    {
                        if(subKey[i] == toupper(argv[1][z]))
                        {
                            repeatedLetter++;
                            if(repeatedLetter == 2)
                            {
                                printf("A chave não pode conter a mesma letra mais de uma vez.\n");
                                return 1;
                            }
                        }
                    }

                    diff[i] = (int)subKey[i] - ascNumCmp;
                    ascNumCmp++;
                }
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
                ciphertext[i] = toupper(pci) + (diff[toupper(pci) - 65]);
                if(islower(pci) != 0)  //se for letra minúscula
                {
                    ciphertext[i] = tolower(ciphertext[i]);
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








