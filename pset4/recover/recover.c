#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    BYTE *buffer;
    char name[10];
    int n = 0, open = 0, am;
    FILE *img;
    if(argc == 1)
    {
        printf("Usage: ./recover image");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error Opening File");
        return 1;
    }
    do
    {
        buffer = malloc(512 * sizeof(BYTE));
        am = fread(buffer, sizeof(BYTE), 512, file);
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (open == 0)
            {
                sprintf(name, "%03i.jpg", n);
                img = fopen(name, "w");
                open = 1;
                fwrite(buffer, sizeof(BYTE), am, img);
            }
            else
            {
                fclose(img);
                open = 0;
                n++;
                sprintf(name, "%03i.jpg", n);
                img = fopen(name, "w");
                open = 1;
                fwrite(buffer, sizeof(BYTE), am, img);
            }
        }
        else
        {
            if (open == 1)
            {
                fwrite(buffer, sizeof(BYTE), am, img);
            }
        }
        free(buffer);
    }while(!feof(file));
    fclose(img);
    fclose(file);

}
