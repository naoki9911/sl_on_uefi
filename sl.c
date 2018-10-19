#include "sl.h"
#include "console.h"
#include "timer.h"

void sl(){
  UINTN max_x = console_get_cursor_x()*15;
  for(int i=max_x;i>-1;i = i-5){
    console_free_puts(i,7,D51STR1);
    console_free_puts(i,8,D51STR2);
    console_free_puts(i,9,D51STR3);
    console_free_puts(i,10,D51STR4);
    console_free_puts(i,11,D51STR5);
    console_free_puts(i,12,D51STR6);
    console_free_puts(i,13,D51STR7);
    console_free_puts(i,14,D51WHL11);
    console_free_puts(i,15,D51WHL12);
    console_free_puts(i,16,D51WHL13);
    delay(1);
  }
}
