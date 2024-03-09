#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Uso: ./ chave de substituição\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("A chave deve conter 26 caracteres.\n");
        return 1;
    }
    char cifra[27];

    for (int i = 0; i <= strlen(argv[1]); i++)
    {
        if (i == strlen(argv[1]))
        {
            cifra[i] = '\0';
        }
        else if (argv[1][i] < 65 || (argv[1][i] > 90 && argv[1][i] < 97) || argv[1][i] > 122)
        {
            printf("Uso: ./ chave de substituição\n");
            return 1;
        }
        else if (argv[1][i] >= 65 && argv[1][i] <= 90)
        {
            cifra[i] = argv[1][i];
            for (int ii = 0; ii < strlen(cifra) - 1; ii++)
            {
                if (cifra[i] == cifra[ii])
                {
                    printf("Uso: ./ chave de substituição\n");
                    return 1;
                }
            }
        }
        else
        {
            cifra[i] = argv[1][i] - 32;
            for (int ii = 0; ii < strlen(cifra) - 1; ii++)
            {
                if (cifra[i] == cifra[ii])
                {
                    printf("Uso: ./ chave de substituição\n");
                    return 1;
                }
            }
        }
    }

    string texto = get_string("Digite o texto a ser cifrado: \n");

    char texto_cifrado[strlen(texto)];

    for (int i = 0; i <= strlen(texto); i++)
    {
        if (i == strlen(texto))
        {
            texto_cifrado[i] = texto[i];
        }
        else if (texto[i] >= 65 && texto[i] <= 90)
        {
            texto_cifrado[i] = cifra[texto[i] - 65];
        }
        else if (texto[i] >= 97 && texto[i] <= 122)
        {
            int aux = texto[i] - 97;
            texto_cifrado[i] = (cifra[aux]) + 32;
        }
        else
        {
            texto_cifrado[i] = texto[i];
        }
    }

    printf("ciphertext: %s\n", texto_cifrado);
}
