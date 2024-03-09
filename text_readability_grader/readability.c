#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    char* letras = get_string("Digite o texto a ser avaliado: \n");

    int qtd_letras = 0;
    int qtd_palavras = 1;
    int qtd_sentencas = 0;
    int index = 0;
    while (index < strlen(letras))
    {
        if (( (char) letras[index] >= 65 && (char) letras[index] <= 90) || ((char) letras[index] >= 97 && (char) letras[index] <= 122))
        {
            qtd_letras ++;
        }
        if ((char) letras[index] == ' ')
        {
            qtd_palavras ++;
        }
        if ((char) letras[index] == '.' || (char) letras[index] == '?' || (char) letras[index] == '!')
        {
            qtd_sentencas ++;
        }
        index ++;
    }

    float l = qtd_letras * 100 / (float) qtd_palavras;
    float s = qtd_sentencas * 100 / (float) qtd_palavras;
    float indice = 0.0588 * l - 0.296 * s - 15.8;
    
    if ((int) round(indice) >= 16)
    {
        printf("Grade 16+\n");
    }
    else if ((int) round(indice) < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(indice));
    }
}

