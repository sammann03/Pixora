#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *f = fopen("test_p6.ppm", "wb");
    if (!f) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    int width = 16;
    int height = 16;

    if (fprintf(f, "P6\n%d %d\n255\n", width, height) < 0) {
        perror("Failed to write header");
        fclose(f);
        return EXIT_FAILURE;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char r = (unsigned char)(x * 16);
            unsigned char g = (unsigned char)(y * 16);
            unsigned char b = (unsigned char)((x + y) * 8);

            if (fwrite(&r, 1, 1, f) != 1 ||
                fwrite(&g, 1, 1, f) != 1 ||
                fwrite(&b, 1, 1, f) != 1) {
                perror("Failed to write pixel data");
                fclose(f);
                return EXIT_FAILURE;
                }
        }
    }

    if (fclose(f) != 0) {
        perror("Failed to close file");
        return EXIT_FAILURE;
    }

    printf("P6 test image generated: test_p6.ppm\n");
    return EXIT_SUCCESS;
}