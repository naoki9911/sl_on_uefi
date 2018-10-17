#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/UefiBootServicesTableLib.h>
#include  <Protocol/BlockIo.h>
#include  <Protocol/LoadedImage.h>
#include  <Protocol/SimpleFileSystem.h>
#include <Protocol/SimpleTextIn.h>
#include  <Library/DevicePathLib.h>
#include  <Guid/FileInfo.h>
#include  <Library/MemoryAllocationLib.h>
#include  <Library/BaseMemoryLib.h>
#include "graphic.h"
#include "font.h"
#include "console.h"
#include "timer.h"
#include "sh.h"

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

  console_init(&conf);
  console_clear();
  console_puts("ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
  console_puts("abcdefghijklmnopqrstuvwxyz\n");
  sh_init(&conf);
  sh_cmd();

  EFI_STATUS Status;
  EFI_SIMPLE_TEXT_INPUT_PROTOCOL *input;
  Status = gBS->LocateProtocol(
      &gEfiSimpleTextInProtocolGuid,
      NULL,
      (VOID **)&input);
  if(EFI_ERROR(Status)){
    Print(L"Failed to Locate Simple Text Output Protocol\n");
    return Status;
  }
  UINTN index;
  EFI_INPUT_KEY key;
  while(1){
    gBS->WaitForEvent(1,&(input->WaitForKey),&index);
    input->ReadKeyStroke(input,&key);
    if(key.UnicodeChar == 0xD){
      console_puts("\n");
    }else{
      console_putc(key.UnicodeChar);
    }
  };
  asm("hlt");
}
