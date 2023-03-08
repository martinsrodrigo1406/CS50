#include <stdio.h>
#include <cs50.h>

int main(void)
{
int qtdBlocos = get_int("Tamanho: ");

while(qtdBlocos < 1)
{
printf("%s", "Tamanho deve ser maior que 0");
qtdBlocos = get_int("Tamanho: ");
}

int contadorlinhas = qtdBlocos;
int contadorespacos = 0;
int contadorblocos = 0;

while(contadorlinhas > 0)
{
    contadorespacos = qtdBlocos;
    //printf("%d\n", contadorespacos);
    contadorespacos -= contadorblocos;
   // printf("%d\n", contadorespacos);
    while(contadorespacos > 1)
    {
        printf("%s", " ");
        contadorespacos--;
    }

    contadorblocos++;

    for(int i = 1; i <= contadorblocos; i++)
    {
        printf("%s", "#");
    }
    printf("%s", " ");
    for(int j = 1; j <= contadorblocos; j++)
    {
        printf("%s", "#");
    }
    printf("%s\n", "");
    contadorlinhas--;
}

return 0;

}