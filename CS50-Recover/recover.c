#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //Check for exactly one command line argument
    if (argc != 2)
    {
        printf("Usage: recover [image ...]\n");
        return 1;
    }

    //Open Memory Card
    FILE *f = fopen(argv[1], "r");

    //Check that file can be opened
    if (f == NULL)
    {
        printf("Your file can't be opened.\n");
        return 1;
    }

    //Array to store data I'm reading
    char buffer[512];
    char filename[100];
    FILE *img;
    //Check for beginning of a jpeg file
    int num_jpeg = -1; // var to keep track of how many jpegs I've found so far

    while (1)
    {
        //Read the Card
        int bytes_read = fread(buffer, 512, 1, f);
        if (bytes_read == 0)
        {
            break;
        }

        if (buffer[0] == (char) 0xff && \
            buffer[1] == (char) 0xd8 && \
            buffer[2] == (char) 0xff && \
            (buffer[3] & (char) 0xf0) == (char) 0xe0)
        {
            if (num_jpeg >= 0)
            {
                fclose(img);
            }
            num_jpeg++;
            sprintf(filename, "%03i.jpg", num_jpeg);

            img = fopen(filename, "w");
            fwrite(buffer, 512, 1, img /*outptr is the jpeg I just opened*/);

            //close file I've just been writing to
            //open new file that I'm going to continue writing to

        }
        else
        {
            if (num_jpeg >= 0)
            {
                fwrite(buffer, 512, 1, img /*outptr is the jpeg I just opened*/);
            }

        }
    }
    fclose(img);
}
