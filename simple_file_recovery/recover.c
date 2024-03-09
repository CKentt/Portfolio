#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
bool isjpeg(BYTE *bytes);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Uso: ./recuperar imagem");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Uso: ./recuperar imagem");
        return 1;
    }

    int name = 0;
    char filename[8];

    BYTE buffer[512];
    bool start_jpeg = false;
    FILE *foutput;

    while (fread(&buffer, sizeof(BYTE), 512, file) == 512)
    {
        if (isjpeg(buffer))
        {
            if (start_jpeg == true)
            {
                fclose(foutput);
            }
            sprintf(filename, "%03i.jpg", name);
            foutput = fopen(filename, "w");
            name++;
            start_jpeg = true;
            fwrite(&buffer, sizeof(BYTE), 512, foutput);
        }
        else if (start_jpeg == true)
        {
            fwrite(&buffer, sizeof(BYTE), 512, foutput);
        }
    }
    fclose(file);
}

bool isjpeg(BYTE *bytes)
{
    if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff)
    {
        if (bytes[3] == 0xe0 || bytes[3] == 0xe1 || bytes[3] == 0xe2 || bytes[3] == 0xe3 || bytes[3] == 0xe4 || bytes[3] == 0xe5 ||
            bytes[3] == 0xe6 || bytes[3] == 0xe7 || bytes[3] == 0xe8 || bytes[3] == 0xe9 || bytes[3] == 0xea || bytes[3] == 0xeb ||
            bytes[3] == 0xec || bytes[3] == 0xed || bytes[3] == 0xee || bytes[3] == 0xef)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
