#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    FILE *f;
        FILE *img;
    if(argc == 2)
    {
        f = fopen(argv[1], "r");
    }
    else{
        return 1;
    }


        BYTE *buffer = malloc(sizeof(BYTE) * 512);
        size_t bytesRead = 0;

        char *filename = malloc(sizeof(char) * 8);
        int counter = 0;

    while((bytesRead = fread(buffer, 512, 1, f)) > 0)
    {
       // printf("É uma imagem\n");
        for(int j = 0; j < 512; j++)
        {
            if(*(buffer + j) == 0xff)
            {
                if(*(buffer + j + 1) == 0xd8)
                {
                    if(*(buffer + j + 2) == 0xff)
                    {
                        if((*(buffer + j + 3) & 0xf0) == 0xe0)
                        {
                            if(img != NULL)
                            {
                                fclose(img);
                            }
                            sprintf(filename, "%03i.jpg", counter);
                            counter++;
                            img = fopen(filename, "w");
                        }
                    }
                }
            }
                if(img != NULL)
                {
                    BYTE *singleByte = (buffer + j);
                    fwrite(singleByte, 1, 1, img);
                }

        }

    }
    if(img != NULL)
                            {
                                fclose(img);
                            }

    free(buffer);
    free(filename);

    }


