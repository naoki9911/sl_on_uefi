#include <Uefi.h>
#include <Library/UefiLib.h>
#include "font.h"
#include "font_bin.h"
#include "graphic.h"

void font_render(UINTN x,UINTN y,UINTN code,struct graphic_config *graphic_config){
  for(UINTN i=0;i<30;i++){
    UINT16 bin = font_bin[code-0x20][i];
    for(INTN j=14;j>-1;j--){
      if(bin&1){
        graphic_draw_font(x+j,y+i,graphic_config);
      }else{
      }
      bin = bin >> 1;
    }
  }
}
