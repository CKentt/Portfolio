#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (argv[1][i] < 48 || argv[1][i] > 57)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]);
    if (key <= 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    char *text = get_string("Digite o texto a ser criptografado: \n");

    char lista_cripto[strlen(text)];

    int index;
    for (index = 0; index < strlen(text); index++)
    {
        if (text[index] >= 65 && text[index] <= 90)
        {
            int aux = text[index];
            lista_cripto[index] = ((aux - 65 + key) % 26) + 65;
        }
        else if (text[index] >= 97 && text[index] <= 122)
        {
            int aux = text[index];
            lista_cripto[index] = ((aux - 97 + key) % 26) + 97;
        }
        else
        {
            lista_cripto[index] = text[index];
        }
    }
    printf("ciphertext: %s\n", lista_cripto);
    return 0;
}
