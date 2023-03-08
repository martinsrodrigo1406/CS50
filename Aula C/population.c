#include <stdio.h>
#include <cs50.h>

int main(void)
{

    int initPopulation;
    int finPopulation;
    int anos = 0;
      do
      {
          initPopulation = get_int("Informe o numero inicial da população: ");
      }
      while(initPopulation < 9);

      do
      {
          finPopulation = get_int("Informe o numero final da população: ");
      }
      while(finPopulation < initPopulation);

     while(finPopulation > initPopulation)
     {
         int deadPopulation = initPopulation / 4;
         int bornPopulation = initPopulation / 3;
         initPopulation -= deadPopulation;
         initPopulation += bornPopulation;
         anos++;
     }
      printf("Anos necessários: %d\n", anos);

return 0;
}