#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/UefiBootServicesTableLib.h>
#include  <Protocol/BlockIo.h>
#include  <Protocol/LoadedImage.h>
#include  <Protocol/SimpleFileSystem.h>
#include  <Library/DevicePathLib.h>
#include  <Guid/FileInfo.h>
#include  <Guid/Acpi.h>
#include  <Library/MemoryAllocationLib.h>
#include  <Library/BaseMemoryLib.h>
#include "graphic.h"
#include "font.h"

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  Print(L"Hello World!");
  struct graphic_config conf;
//  Print(L"Getting Graphic Node\n");
  GetGraphicMode(ImageHandle,&conf);

  graphic_draw_white(10,10,&conf);
  graphic_draw_white(11,10,&conf);
  graphic_draw_white(12,10,&conf);
  graphic_draw_white(13,10,&conf);
  for(UINTN i=0;i<48;i++){
    font_render(20+i*15,20,0x21+i,&conf);
  }
  while(1){
    asm("hlt");
  };
}
