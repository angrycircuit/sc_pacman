#include <stdio.h>
#include <Windows.h>
#include <MMSystem.h>

// You must use the windows and MMsystem headers to facilitate access to the hardware audio devices.
// In the Linker, please add the additional dependency winmm.lib
// Audio files must be placed in the repos directory of VS or be placed in a linked directory

int main(void)
{
	PlaySound(TEXT("boo.wav"), NULL, SND_SYNC);

	system("pause");
	return 0;
}