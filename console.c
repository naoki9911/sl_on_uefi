#include "console.h"
#include "font.h"
#include "graphic.h"
#include <Library/BaseMemoryLib.h>
#define FONT_X 15
#define FONT_Y 30
struct graphic_config conf;
UINTN cursor_x;
UINTN cursor_y;
UINTN cursor_pos;
int cursor_state = 0;
void console_init(struct graphic_config *graphic_conf){
  conf.frame_base = graphic_conf->frame_base;
  conf.horizontal_resolution = graphic_conf->horizontal_resolution;
  conf.vertical_resolution = graphic_conf->vertical_resolution;
  conf.pixels_per_scan_line = graphic_conf->pixels_per_scan_line;
  conf.frame_size = graphic_conf->frame_size;

  cursor_x = (conf.horizontal_resolution-10)/FONT_X;
  cursor_y = (conf.vertical_resolution-10)/FONT_Y;
}

void console_putc(char string){
  UINTN x = (cursor_pos%cursor_x)*FONT_X+5;
  UINTN y = (cursor_pos/cursor_x)*FONT_Y+5;
  if(cursor_pos >= cursor_y * cursor_x){
    console_scroll();
  }
  if(string == '\n'){
    cursor_pos += cursor_x - cursor_pos%cursor_x;
    font_render(x,y,0x20,&conf);
  }else{
    font_render(x+FONT_X,y,0x20,&conf);
    font_render(x,y,string,&conf);
    cursor_pos++;
    if(cursor_state){
      font_render(x+FONT_X,y,'_',&conf);
    }
  }
}

void console_puts(char *string){
  int i=0;
  while(string[i]){
    console_putc(string[i]);
    i++;
  }
}

void console_scroll(){
  UINTN addr_diff = conf.pixels_per_scan_line*FONT_Y*4;
  CopyMem((VOID *)conf.frame_base,(VOID *)(conf.frame_base+addr_diff),conf.frame_size-addr_diff);
  SetMem((VOID *)conf.frame_base+conf.frame_size-addr_diff,addr_diff,0);
  cursor_pos -= cursor_x;
}

void console_clear(){
  SetMem((VOID *)conf.frame_base,conf.frame_size,0);
  cursor_pos=0;
}

void console_cursor_enable(){
  cursor_state = 1;
}

void console_cursor_clear(){

}
