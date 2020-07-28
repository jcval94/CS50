#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>


int main(int argc, char *argv[])
{
    //validation
    if (argc < 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //Open Memory Card
    FILE *f = fopen(argv[1], "r"), *f2;
    //create buffer
    unsigned char buffer[512];
    //first file indicator
    bool first = false;
    //filename
    char archivos[100];
    //int to change name
    int j = 0;

    while (fread(&buffer, 512, 1, f))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 &&
            buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if there is a file (after the first), close it
            if (first)
            {
                fclose(f2);
            }
            //print jpgs
            sprintf(archivos, "%03i.jpg", j);
            //Segmentation fault indicator
            //printf("hola\n");
            f2 = fopen(archivos, "a");
            //first file has been founded
            first = true;
            //each time a file is found, sum 1
            j++;
        }

        if (first)
        {
            fwrite(&buffer, 512, 1, f2);
        }
    }

    //close files
    fclose(f);
    fclose(f2);

    return 0;
}
