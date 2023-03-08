#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{

float troco;

do
{
troco = get_float("Qual o valor do troco?: ");
} while(troco < 0.01);

int trocoEmCentavos = troco * 100;
int contaMoedas = 0;

while(trocoEmCentavos > 1)
{
    while(trocoEmCentavos >= 25)
    {
        trocoEmCentavos -= 25;
        contaMoedas++;
    }
    while(trocoEmCentavos >= 10)
    {
        trocoEmCentavos -= 10;
        contaMoedas++;
    }
    while(trocoEmCentavos >= 5)
    {
        trocoEmCentavos -= 5;
        contaMoedas++;
    }
    while(trocoEmCentavos < 5 && trocoEmCentavos > 0)
    {
        trocoEmCentavos--;
        contaMoedas++;
    }

}

printf("Total de moedas: %d\n", contaMoedas);
return 0;

}