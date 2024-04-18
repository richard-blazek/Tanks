#ifndef __IO_H__
#define __IO_H__

#include <stdbool.h>

void io_init(int w, int h);
void io_quit(void);
int io_dialog(const char *message, const char *options);
void io_message(const char *message);

bool io_click(void);
void io_mouse_position(int *x, int *y);
void io_arrows(int *x, int *y);

void io_draw_clear(void);
void io_draw_update(void);
void io_draw_fighter(int x, int y, int w, int h, int r, int g, int b, float life);
void io_draw_xp(int level, float xp);

#endif