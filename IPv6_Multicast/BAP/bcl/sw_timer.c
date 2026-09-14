/******************************************************************
 *
 *     Copyright (c) 2004-2023 Volkswagen AG, D-38436 Wolfsburg
 *
 ******************************************************************
 *
 * Beschreibung
 *
 *  Diese Datei enthaelt die Implementierung Funktionen zur
 *  Laufzeitmessung im BAP-Projekt.
 *
 ******************************************************************/

#ifndef BAP_RUNTIME_TEST
#error Bitte definieren Sie BAP_RUNTIME_TEST fuer Laufzeitmessungen
#endif

/* Systemincludes mit <...> */
#include "sfr\regtc29x.sfr"

#include "sw_timer.h"
#include <stdio.h>

#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
volatile DefinitionOfSWTimer(BapIndInt8_Timer);
volatile DefinitionOfSWTimer(BapIndBS_Timer);
volatile DefinitionOfSWTimer(BapReqInt8_Timer);
volatile DefinitionOfSWTimer(BapReqBS_Timer);
volatile DefinitionOfSWTimer(BapTask_Timer);
volatile DefinitionOfSWTimer(BapIRQ_Timer);
volatile DefinitionOfSWTimer(BapTransmit_Timer);
volatile DefinitionOfSWTimer(BapReceive_Timer);
volatile DefinitionOfSWTimer(BapProcessReceived_Timer);
volatile DefinitionOfSWTimer(BapIndAll_Timer);
volatile DefinitionOfSWTimer(BapRxIRQ_Timer);
volatile DefinitionOfSWTimer(BapStart_Timer);
volatile DefinitionOfSWTimer(BapShutdown_Timer);
volatile DefinitionOfSWTimer(BapCanSendTask_Timer);
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
void InitSWTimer(void)
{
	/* Enable STM0 if disabled */
	if(STM0_CLC.B.DISS == 1){
		STM0_CLC.B.DISR = 0;
	}
}

void StartSWTimer(swtimer_t *timer)
{
    timer->TimerStartValue = STM0_TIM0.U;
}

void StopSWTimer(swtimer_t *timer)
{
    timer->TimerStopValue = STM0_TIM0.U;

    timer->TimerDifference = ((timer->TimerStopValue)-(timer->TimerStartValue));

    if(timer->TimerMaxDifference < timer->TimerDifference)
    {
        timer->TimerMaxDifference = timer->TimerDifference;
    }
    if(timer->TimerMinDifference > timer->TimerDifference)
    {
        timer->TimerMinDifference = timer->TimerDifference;
    }
}

uint16_t GetSWTimer(swtimer_t *timer)
{
    return(timer->TimerDifference);
}

uint16_t GetSWTimerMaxValue(swtimer_t *timer)
{
    return(timer->TimerMaxDifference);
}

uint16_t GetSWTimerMinValue(swtimer_t *timer)
{
    return(timer->TimerMinDifference);
}

#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>
