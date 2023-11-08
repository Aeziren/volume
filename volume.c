// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Declara um buffer para o header. UM BUFFER É NECESSÁRIO POIS É UM ARMAZENAMENTO TEMPORÁRIO DOS ARQUIVOS. Movendo do HD > RAM > HD.
    uint8_t header[HEADER_SIZE];
    // Coloca todo o conteúdo do header do input dentro do buffer.
    fread(&header, HEADER_SIZE, 1, input);
    // Escreve o que está dentro do buffer para o output.
    fwrite(&header, HEADER_SIZE, 1 , output);

    // Declara um buffer para os samples.
    int16_t buffer;
    // Copia todo o contéudo do input para o buffer, multiplica o buffer pelo fator, e move do buffer para o output.
    // É importante lembrar que fread retorna o a quantidade de dados movida. Sendo assim dá para usá-la como condição!
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
