#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/UefiBootServicesTableLib.h>
#include <Protocol/SimpleTextIn.h>
#include "sh.h"
#include "console.h"
#include "graphic.h"

void sh_init(struct graphic_config *conf){
  console_init(conf);
  console_clear();
  console_cursor_enable();
}

EFI_STATUS sh_cmd(){
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
  console_puts(">");
  while(1){
    gBS->WaitForEvent(1,&(input->WaitForKey),&index);
    input->ReadKeyStroke(input,&key);
    if(key.UnicodeChar == 0xD){
      console_puts("\n>");
    }else{
      console_putc(key.UnicodeChar);
    }
  }
}
