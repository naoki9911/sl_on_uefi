#ifndef CONSOLE_H
#define CONSOLE_H
#include "graphic.h"

void console_init(struct graphic_config *graphic_config);
void console_putc(char string);
void console_puts(char *string);
void console_scroll();
void console_clear();
void console_cursor_enable();
#endif
