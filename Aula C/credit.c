#include <stdio.h>
#include <cs50.h>

int main(void)
{

      long ccNumber;

      do
      {
          ccNumber = get_long("Digite o número do cartão: ");
      } while(ccNumber <= 0);

     //definindo bandeira do cartão
     string bandeira = "";

     long testNumDig = ccNumber;
     long divisor = 10;
     int contaDig = 1;

     while(testNumDig > 10)
     {
         testNumDig = ccNumber;
         testNumDig = testNumDig / divisor;
         divisor = divisor * 10;
         contaDig++;
     }

     testNumDig = ccNumber;
     int checksum = 0;
     int rest = 0;
     while(testNumDig > 10)
     {

         rest = testNumDig % 10;
         checksum += rest;
         testNumDig = testNumDig / 10;
         rest = testNumDig % 10;
         rest = rest * 2;
         if(rest > 9)
         {
             checksum = checksum + (rest % 10);
             checksum = checksum + (rest / 10);
         }
         else
         {
             checksum += rest;
         }

         testNumDig = testNumDig / 10;

     }
     printf("Quantidade de dígitos do cartão: %d\n", contaDig);
     if((checksum % 10) == 0)
         printf("Cálculo de Luhn: %d\n", checksum);
     else
     {
         printf("INVALID \n");
         printf("%d\n", checksum);
     }

     return 0;


}