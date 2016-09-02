#include <stdio.h>
#include <stdlib.h>

#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>

#include "graphics.h"

void menu() {
	psvDebugScreenClear(COLOR_BLACK);
	psvDebugScreenSetFgColor(COLOR_WHITE);
	psvDebugScreenPrintf("memcardswap by SMOKE\n\n");
	psvDebugScreenSetFgColor(COLOR_RED);
	psvDebugScreenPrintf("WARNING! do not use the temporary and semi-permanent methods\n");
	psvDebugScreenPrintf("at the same time! You WILL be forced to format!\n\n");
	psvDebugScreenSetFgColor(COLOR_WHITE);
	psvDebugScreenPrintf("Making id.dat read only is useful for swapping memcard\n");
	psvDebugScreenPrintf("between 3.60 & 3.61 Vitas. This way, it won't be able to\n");
	psvDebugScreenPrintf("update the SVR field and you can swap back without formatting\n\n");
	psvDebugScreenPrintf("Press CROSS to remove id.dat.. (temporary)\n");
	psvDebugScreenPrintf("Press CIRCLE to make id.dat RO.. (semi-permanent)\n");
	psvDebugScreenPrintf("Press SQUARE to make id.dat RW.. (undo semi-permanent)\n");
	psvDebugScreenPrintf("Press START to exit..\n");
}

int main()
{
	psvDebugScreenInit();

	menu();

	SceCtrlData pad;
	SceIoStat stat;

	while (1) {
		sceCtrlPeekBufferPositive(0, &pad, 1);

		if (pad.buttons == SCE_CTRL_START) {
			break;
		}

		if (pad.buttons == SCE_CTRL_CROSS) {
			// deletes the id.dat file and recreates a new, empty one
			sceIoRemove("ux0:/id.dat");

			SceUID id;
			id = sceIoOpen("ux0:/id.dat", SCE_O_WRONLY|SCE_O_CREAT, 0777);

			sceIoWrite(id, NULL, 0x0);

			psvDebugScreenSetFgColor(COLOR_GREEN);
			psvDebugScreenPrintf("Completed!\n");
			sceKernelDelayThread(2 * 1000 * 1000);
			menu();
		}

		if (pad.buttons == SCE_CTRL_CIRCLE) {
			// Changes permissions to read only
			stat.st_mode = 0444;
			sceIoChstat("ux0:/id.dat", &stat, 1);

			psvDebugScreenSetFgColor(COLOR_GREEN);
			psvDebugScreenPrintf("Completed!\n");
			sceKernelDelayThread(2 * 1000 * 1000);
			menu();
		}

		if (pad.buttons == SCE_CTRL_SQUARE) {
			// Changes permissions to read & write
			stat.st_mode = 0777;
			sceIoChstat("ux0:/id.dat", &stat, 1);

			psvDebugScreenSetFgColor(COLOR_GREEN);
			psvDebugScreenPrintf("Completed!\n");
			sceKernelDelayThread(2 * 1000 * 1000);
			menu();
		}
	}

	sceKernelExitProcess(0);

    return 0;
}
