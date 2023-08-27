#include <stdio.h>
#include <stdlib.h>
#include "re_login.h"
#include"re_system_control.h"

int main()
{
   SystemCtl sysctl;
   login(&sysctl);
   
	return 0;
}