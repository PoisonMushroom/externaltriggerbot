#include "Hprocess.h"
#include <Windows.h>
#include <iostream>

using namespace std;

CHackProcess fProcess;

//NEED TO FIND OFFSET DUMPER
DWORD PlayerBase;
DWORD LocalPlayer = 0xA9ADEC; 
//DWORD LocalPlayerBase = 0xAA9AB4; 
DWORD CrosshairId = 45732;
int id;


void sendkeypress()
{

	//KEYBOARD EVENTS
	INPUT ip;

	//INPUT STRUCTURE
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.wVk = 0; 
	ip.ki.dwExtraInfo = 0;

	//HARDWARE SCAN
	ip.ki.dwFlags = KEYEVENTF_SCANCODE;
	ip.ki.wScan = 0x12; //Initialize
	SendInput(1, &ip, sizeof(INPUT)); //SEND
	Sleep(25);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT)); //RELEASE

}

int main()
{
	fProcess.RunProcess();
	while (true)
	{
		ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordClient + LocalPlayerBase), &PlayerBase, sizeof(DWORD), 0);
		ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(PlayerBase + CrosshairId), &id, sizeof(int), 0);

		if (GetAsyncKeyState(VK_MBUTTON) && id > 0) 
		{
			sendkeypress();
		}

		Sleep(1);
	}
	
}