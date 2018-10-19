#ifndef SH_H
#define SH_H
#include "graphic.h"

void sh_init(struct graphic_config *conf);
EFI_STATUS sh_cmd();
void sh_parse();
int sh_cmdcmp(const char* s1,const char* s2);
#endif
