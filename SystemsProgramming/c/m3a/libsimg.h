typedef struct {
    char c;
    int r;
} simg_pixel;

typedef struct {
    int height;
    int width;
    simg_pixel ***data;
} simg_img;

typedef struct {
    int cx;
    int cy;
    char c;
    int r;
} simg_cursor;

enum simg_color_list {
    SIMG_RESET,
    SIMG_RED,
    SIMG_GREEN,
    SIMG_YELLOW,
    SIMG_BLUE,
    SIMG_MAGENTA,
    SIMG_CYAN
};

extern const char *simg_colors[7];

int simg_create(simg_img *img, int height, int width, char bg);
int simg_setpixel(simg_img *img, int x, int y, int color, char c);
int simg_write(simg_img *img, char *fn);
int simg_read(simg_img *img, char *fn);
int simg_print(simg_img *img, simg_cursor *cur);
