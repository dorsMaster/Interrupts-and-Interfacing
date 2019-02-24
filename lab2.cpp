#include <predef.h>
#include <stdio.h>
#include <ctype.h>
#include <startnet.h>
#include <autoupdate.h>
#include <smarttrap.h>
#include <taskmon.h>
#include <NetworkDebug.h>
#include "keypad.h"
#include "error_wrapper.h"
#include "LCD.h"

extern "C" {
void UserMain(void * pd);
}

const char * AppName="Put you name here";
Keypad myKeypad;
LCD myLCD;

void UserMain(void * pd) {
	BYTE err = OS_NO_ERR;
    InitializeStack();
    OSChangePrio(MAIN_PRIO);
    EnableAutoUpdate();
    StartHTTP();
    EnableTaskMonitor();

    #ifndef _DEBUG
    EnableSmartTraps();
    #endif

    #ifdef _DEBUG
    InitializeNetworkGDB_and_Wait();
    #endif

    myKeypad.Init(KEYPAD_POLL_MODE);
    myLCD.Init();



    iprintf("Application started %s\n", AppName);
    while (1) {
    	OSTimeDly(TICKS_PER_SECOND);
    }
}
