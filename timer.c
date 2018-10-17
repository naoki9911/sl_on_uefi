#include <Uefi.h>
#include <Library/UefiLib.h>
#include  <Library/UefiBootServicesTableLib.h>

EFI_EVENT tevent;
UINT8 init = 0;
UINTN index;
EFI_STATUS delay_init(){
  EFI_STATUS Status;
  Status = gBS->CreateEvent(EVT_TIMER,0,NULL,NULL,&tevent);
  if(EFI_ERROR(Status)){
    Print(L"Failed to Create Event\n");
    return Status;
  }
  init = 1;
  return Status;
}

EFI_STATUS delay(int ms){
  if(!init){
    delay_init();
  }
  EFI_STATUS Status;
  Status = gBS->SetTimer(tevent,TimerRelative,ms*10000);
  if(EFI_ERROR(Status)){
    Print(L"Failed to Set Timer\n");
    return Status;
  }
  
  Status = gBS->WaitForEvent(1,&tevent,&index);
  if(EFI_ERROR(Status)){
    Print(L"Failed to Wait For Event\n");
    return Status;
  }
  return Status;
}
