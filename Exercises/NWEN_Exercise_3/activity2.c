#include <stdio.h>

int main(void)
{
    int a, b;
    FILE *in;  // use for handling input file
    FILE *out; // use for handling output file

    // Open raw.txt for reading
    in = fopen("raw.txt", "r");

    // Open processed.txt for writing
    out = fopen("processed.txt", "w");

    // Go thru raw.txt file and generate processed.txt file accordingly

    for (int i = 0; i < 4; i++)
    {
        fscanf(in, "%d %d", &a, &b);
        fprintf(out, "%d %d %d\n", a, b, a + b);
    }

    return 0;
}
