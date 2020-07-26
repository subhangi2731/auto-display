#include <windows.h>
#include <time.h>
#include <stdio.h>
#define TRUE 1

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Hides the console window which appears at program execution.
	FreeConsole();
	// The time at which the display is switched off. 1830 hours.
	const int off_hour = 18;
	const int off_min = 30;
	// The time at which the display is switched on. 0845 hours.
	const int on_hour = 8;
	const int on_min = 45;
	while(TRUE)
	{
		// Getting the current hour and minutes.
		time_t timer;
		time(&timer);
        struct tm *timeinfo;
		timeinfo = localtime(&timer);
		
		// Represents the current hour.
		int hr = timeinfo->tm_hour;
		// Represents the current minute.
		int min = timeinfo->tm_min;
		
		// Turn the display off if the current time is more than off time and less than on time.
		if((hr == off_hour && min >= off_min) || (hr > off_hour && (hr < on_hour)) || (hr == on_hour && min < on_min))
		{
			SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 2);
		}
		
		// Turn the display on if the current time is more than on time and less than off time.
		if((hr == on_hour && min >= on_min) || (hr > on_hour && (hr < off_hour)) || (hr == off_hour && min < off_min))
		{
			SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) -1);
		}
		// Sleep the thread for 30 seconds.
		Sleep(30000);
	}
	
	return 0;
}