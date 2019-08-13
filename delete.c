#include "header.h"

 void delStrings(void *str)
 {
     free(str);
     str = NULL;
 }