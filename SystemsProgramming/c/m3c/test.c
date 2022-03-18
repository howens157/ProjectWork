#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *buf = malloc(1000 * sizeof(char));
    FILE *testfile = fmemopen(buf, 1000, "wb");
    char testvals[] = {'a', 'b', 'c', 'd', 'e'};
    int i;
    for(i = 0; i < 5; i++)
    {
        printf("%c\n", testvals[i]);
        fwrite(&testvals[i], sizeof(char), 1, testfile);
    }
    char c;
    fclose(testfile);
    testfile = fmemopen(buf, 1000, "rb");
    for(i = 0; i < 5; i++)
    {
        fread(&c, sizeof(char), 1, testfile);
        printf("%c\n", c);
    }
    fclose(testfile);
    return 0;
}
