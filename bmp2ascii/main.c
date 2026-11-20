/*
Read 24-bit BMP image and output the same as ASCII art.
To learn about ASCII art, read:
- https://en.wikipedia.org/wiki/ASCII_art
- https://www.asciiart.eu/
For BMP format, see:
- https://en.wikipedia.org/wiki/BMP_file_format
- https://upload.wikimedia.org/wikipedia/commons/7/75/BMPfileFormat.svg
*/

#include <basicgol.h>

#pragma pack(push, 1)
REGISTRO(BMPHeader)
    NATURAL8  type[2];    // Magic identifier: "BM"
    NATURAL   size;       // File size
    NATURAL_CURTO reserved1;
    NATURAL_CURTO reserved2;
    NATURAL   offset;     // Offset to point to pixel data
FIM_REGISTRO(BMPHeader);

REGISTRO(BMPInfoHeader)
    NATURAL   size;           // Header size
    INTEIRO            width;          // Image width
    INTEIRO            height;         // Image height
    NATURAL_CURTO planes;
    NATURAL_CURTO bits_per_pixel; // Should be 24 for RGB
    NATURAL   compression;
    NATURAL   image_size;
    INTEIRO            x_pixels_per_meter;
    INTEIRO            y_pixels_per_meter;
    NATURAL   colors_used;
    NATURAL   colors_important;
    // TODO: handle other header fields if necessary
    // We ignore these for now since we jump straight to the pixels
FIM_REGISTRO(BMPInfoHeader);
#pragma pack(pop)

ENUMERACAO(ErrCode)
    SUCCESS = 0,
    ERR_WRONG_ARGS,
    ERR_INPUT_READ,
    ERR_OUTPUT_WRITE,
    ERR_BAD_HEADER,
    ERR_MALLOC
FIM_ENUMERACAO(ErrCode);

// ASCII palette ordered from darkest visual density to brightest
// This is meant for a device or app set in a dark theme
// The following 15-char set works well but you may
// try other sets or even increase/decrease the number of characters
const CARACTERE ASCII_PALETTE[] = " .:-=+*xX#%&W@$";
//const char ASCII_PALETTE[] = " .:-=+*#%@";
const INTEIRO PALETTE_SIZE = TAMANHO_VETOR(ASCII_PALETTE) - 1;

FUNCAO INTEIRO main(INTEIRO argc, CARACTERE *argv[]) {
    INTEIRO r, c, p;
    SE argc != 2 ENTAO
        ESCREVAL("Error: expecting exactly 1 program argument, the BMP filename to process. Quitting...");
        RETORNE ERR_WRONG_ARGS;
    FIM_SE

    FILE *file = fopen(argv[1], "rb");
    SE NAO file ENTAO
        ESCREVA_FMT("Error: Could not open input file %s. Quitting...\n", argv[1]);
        RETORNE ERR_INPUT_READ;
    FIM_SE

    BMPHeader header;
    BMPInfoHeader infoHeader;

    fread(&header, sizeof(BMPHeader), 1, file);
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, file);

    // Verify it's a valid 24-bit uncompressed BMP
    // chars B = 0x42, M = 0x4D in ASCII
    SE header.type[0] != 0x42 OU header.type[1] != 0x4D OU infoHeader.bits_per_pixel != 24 ENTAO
        ESCREVAL("Error: App appears not to be a valid 24-bit BMP image.");
        fclose(file);
        RETORNE ERR_BAD_HEADER;
    FIM_SE

    INTEIRO width = infoHeader.width;
    INTEIRO height = infoHeader.height;

    // BMP rows are padded to multiples of 4 bytes in memory
    INTEIRO padding = (4 - (width * 3) % 4) % 4;

    NATURAL8 *grid = malloc(height * width * sizeof(NATURAL8));
    SE NAO grid ENTAO
        ESCREVAL("Memory allocation failed!");
        RETORNE ERR_MALLOC;
    FIM_SE

    // Read the pixels and convert to
    fseek(file, header.offset, SEEK_SET); // jump to where pixels start
    PARA(r, 0, height - 1) {
        PARA(c, 0, width - 1) {
            // RGB saved in B-G-R order due to little-endianess of BMP
            NATURAL8 b = fgetc(file);
            NATURAL8 g = fgetc(file);
            NATURAL8 r_val = fgetc(file);

            // Convert RGB to a single grayscale/brightness value
            NATURAL8 luminance = (0.2126 * r_val) + (0.7152 * g) + (0.0722 * b);
            grid[r*width+c] = luminance;
        }
        // Skip over the row padding bytes
        PARA(p, 0, padding - 1) {
            fgetc(file);
        }
    }
    fclose(file);

    // Assemble outfile filename: replace .bmp with .txt
    CARACTERE outfile[255];
    INTEIRO count = strlen(argv[1]) - 4; // ignore trailing .bmp
    strncpy(outfile, argv[1], count);
    strncpy(outfile + count, ".txt", 4);
    outfile[count+4] = '\0';

    FILE *fp = fopen(outfile, "w");
    SE NAO fp ENTAO
        ESCREVA_FMT("Error: Could not open output file %s. Quitting...\n", outfile);
        RETORNE ERR_OUTPUT_WRITE;
    FIM_SE

    // Print the ASCII Art: BMP is stored bottom row first
    for (INTEIRO r = height-1; r >= 0; r--) {
        PARA(c, 0, width - 1) {
            NATURAL8 brightness = grid[r*width+c];

            // Map 0-255 scaling down to our 0-9 palette array index
            INTEIRO palette_index = (brightness * (PALETTE_SIZE - 1)) / 255;

            // Print the mapped character twice!
            // Consoles have tall, skinny fonts. Printing twice keeps the image's aspect ratio squarish.
            fprintf(fp, "%c%c", ASCII_PALETTE[palette_index], ASCII_PALETTE[palette_index]);
        }
        fprintf(fp, "\n");
    }

    // Clean up memory allocation
    free(grid);

    RETORNE SUCCESS;
}
