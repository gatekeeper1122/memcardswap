#include <stdio.h>
#include <stdlib.h>

#include <psp2/kernel/processmgr.h>
#include <psp2/io/fcntl.h>

int main()
{
    sceIoRemove("ux0:/id.dat");

    SceUID id;
    id = sceIoOpen("ux0:/id.dat", SCE_O_WRONLY|SCE_O_CREAT, 0777);

    sceIoWrite(id, NULL, 0x0);

	sceKernelExitProcess(0);

    return 0;
}
