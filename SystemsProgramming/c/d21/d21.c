#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// your code here (define the dino struct)
// use typedef struct, not just struct
typedef struct dino{
    double lat;
    double lng;
    int nm_len;
    char *name;
} dino;

void save_dino(dino *d, char *ofn)
{
    // your code here
    FILE *ofp = fopen(ofn, "wb");
    fwrite(&d->lat, sizeof(double), 1, ofp);
    fwrite(&d->lng, sizeof(double), 1, ofp);
    fwrite(&d->nm_len, sizeof(int), 1, ofp);
    fwrite(d->name, sizeof(char), d->nm_len, ofp);
    fclose(ofp);
}

void load_dino(dino *d, char *ifn)
{
    // your code here
    FILE *ifp = fopen(ifn, "rb");
    fread(&d->lat, sizeof(double), 1, ifp);
    fread(&d->lng, sizeof(double), 1, ifp);
    fread(&d->nm_len, sizeof(int), 1, ifp);
    d->name = malloc(d->nm_len*sizeof(char));
    fread(d->name, sizeof(char), d->nm_len, ifp);
    fclose(ifp);
}

int main(int argc, char **argv)
{
    if(argc != 2)
        return 1;
    
    char *fn = argv[1];
    
    // create a dino struct and give it the following values:
    // latitude = 51.083332
    // longitude = -1.166667
    // name = "Aves indet."
    // do NOT hardcode the string length, get it with strlen() instead
    dino d0;
    d0.lat = 51.083332;
    d0.lng = -1.166667;
    d0.name = "Aves indet.";
    d0.nm_len = strlen(d0.name);
    
    // call save_dino() and save d0 to the given filename (fn)
    save_dino(&d0, fn);
    
    dino d1;
    
    // call load_dino() and load the file you just saved into d1 (NOT d0)
    load_dino(&d1, fn);    

    printf("d1.lat %f\n", d1.lat);
    printf("d1.lng %f\n", d1.lng);
    printf("d1.name %s\n", d1.name);
    
    return 0;
}
