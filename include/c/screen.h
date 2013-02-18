#ifndef KERNEL_SCREEN_H_
#define KERNEL_SCREEN_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "c/memory.h"

#define SCREEN_START    VGA_TEXT
#define SCREEN_SIZE     VGA_TEXT_SIZE
#define SCREEN_END      VGA_TEXT_END
#define SCREEN_COLUMNS  160
#define SCREEN_LINES    24

typedef enum
{
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    BRIGHTBLUE,
    BRIGHTGREEN,
    BRIGHTCYAN,
    BRIGHTRED,
    BRIGHTMAGENTA,
    BRIGHTYELLOW,
    WHITE
}   EGA_COLORS;

typedef struct
{
     short  x;
     short  y;
}           cursor;

void        screen_clear(void);
void        screen_write(const char *ptr, unsigned int size);
void        set_bg_color(EGA_COLORS color);
void        set_fg_color(EGA_COLORS color);
void        screen_init(EGA_COLORS bg, EGA_COLORS fg);
void        screen_init_default(void);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: KERNEL_SCREEN_H_ */
