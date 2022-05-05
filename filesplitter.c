#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <malloc.h>

int main(int argc, char* argv[]) 
{
    if (argc == 3) {
        char name_buffer[255] = "";
        char* path = argv[1];
        int splitted_files_count = atoi(argv[2]), file_size, part_size, i;
        long splitted_size;

        FILE* origin = fopen(path, "rb");
        if (origin && splitted_files_count > 0) {
            fseek(origin, 0L, SEEK_END);
            file_size = ftell(origin);
            rewind(origin);
            
            splitted_size = (int)ceil((double)file_size / splitted_files_count);

            printf("Splitting %d bytes...\n", file_size);

            char* buffer = malloc(splitted_size);

            for (i = 1; i <= splitted_files_count; i++) 
            {
                sprintf(name_buffer, "%s.file%03d", path, i);
                FILE* splitted_file = fopen(name_buffer, "wb");

                fread(buffer, splitted_size, 1, origin);
                fwrite(buffer, splitted_size, 1, splitted_file);

                fclose(splitted_file);
                printf("Created %s.\n", name_buffer);
            }

            free(buffer);
            fclose(origin);
        }
    }
}