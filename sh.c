#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/SimpleTextIn.h>
#include <Library/BaseMemoryLib.h>
#include "sh.h"
#include "console.h"
#include "graphic.h"
#include "sl.h"

char buf[128]={0};
int buf_index=0;

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
      console_putc('\n');
      sh_parse();
      SetMem((VOID *)buf,128,0);
      buf_index=0;
      console_putc('>');
    }else{
      console_putc(key.UnicodeChar);
      buf[buf_index] = key.UnicodeChar;
      buf_index++;
    }
  }
}

void sh_parse(){
  if(sh_cmdcmp((const char*)buf,"sl")){
    sl();
  }
  console_putc('\n');
}

int sh_cmdcmp(const char* s1,const char* s2){
  int i=0;
  while(s1[i]&&s2[i]){
    if(s1[i] == s2[i]){
      i++;
    }else{
      return 0;
    }
  }
  return 1;
}
