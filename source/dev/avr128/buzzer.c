#include "buzzer.h"
#include <inavr.h>
#include "osapi.h"


void Buzzer_Open(void)
{
	// temp
}

void Buzzer_Close(void)
{
	// temp
}

#define FORDELAY_1MSEC 0x09C0
void Beep(U8 val)
{
	Buzzer_Open();
	
	// temp
	
	Buzzer_Close();
}

void StartBuzzer(void)
{
	Beep(5);
	Beep(5);
	Beep(6);
	Beep(6);
	
}


