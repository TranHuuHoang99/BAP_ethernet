/******************************************************************
 *
 *     Copyright (c) 2004-2023 Volkswagen AG, D-38436 Wolfsburg
 *
 ******************************************************************
 *
 * Beschreibung
 *
 *  Diese Datei enthaelt die Schnittstelle zur
 *  Laufzeitmessung im BAP-Projekt.
 *  Diese Schnittstelle darf nicht ausserhalb der BAP
 *  Komponente verwendet werden, da sie in zukuenftigen Versionen
 *  Aenderungen unterliegen darf.
 *
 ******************************************************************/

#ifdef BAP_RUNTIME_TEST

#include "bap_user_stdtypes.h"

typedef struct {
  uint32_t TimerStartValue;
  uint32_t TimerStopValue;
  uint32_t TimerDifference;
  uint32_t TimerMaxDifference;
  uint32_t TimerMinDifference;
} swtimer_t;

#define DefinitionOfSWTimer(a) swtimer_t a = {0,0,0,0,0xffffffff};

extern volatile swtimer_t BapIndInt8_Timer;
extern volatile swtimer_t BapIndBS_Timer;
extern volatile swtimer_t BapReqInt8_Timer;
extern volatile swtimer_t BapReqBS_Timer;
extern volatile swtimer_t BapTask_Timer;
extern volatile swtimer_t BapIRQ_Timer;
extern volatile swtimer_t BapTransmit_Timer;
extern volatile swtimer_t BapReceive_Timer;
extern volatile swtimer_t BapProcessReceived_Timer;
extern volatile swtimer_t BapIndAll_Timer;
extern volatile swtimer_t BapRxIRQ_Timer;
extern volatile swtimer_t BapStart_Timer;
extern volatile swtimer_t BapShutdown_Timer;
extern volatile swtimer_t BapCanSendTask_Timer;

void InitSWTimer(void);

void StartSWTimer(swtimer_t *timer);

void StopSWTimer(swtimer_t *timer);

uint16_t GetSWTimer(swtimer_t *timer);

uint16_t GetSWTimerMaxValue(swtimer_t *timer);

uint16_t GetSWTimerMinValue(swtimer_t *timer);

#define BAP_RUNTIME_TEST_START() InitSWTimer();
#define BAP_RUNTIME_TEST_INDINT8_START() if((poCanRxRomRow->lsgId == 1) && (poCanRxRomRow->fctId == 16)){StartSWTimer(&BapIndInt8_Timer);}
#define BAP_RUNTIME_TEST_INDINT8_STOP() if((poCanRxRomRow->lsgId == 1) && (poCanRxRomRow->fctId == 16)){StopSWTimer(&BapIndInt8_Timer);}
#define BAP_RUNTIME_TEST_INDBS_START() if((apoPars->lsgId == 1) && (apoPars->fctId == 30)){StartSWTimer(&BapIndBS_Timer);}
#define BAP_RUNTIME_TEST_INDBS_STOP() if((apoPars->lsgId == 1) && (apoPars->fctId == 30)){StopSWTimer(&BapIndBS_Timer);}
#define BAP_RUNTIME_TEST_REQBS_START() StartSWTimer(&BapReqBS_Timer);
#define BAP_RUNTIME_TEST_REQBS_STOP() StopSWTimer(&BapReqBS_Timer);
#define BAP_RUNTIME_TEST_REQINT8_START() StartSWTimer(&BapReqInt8_Timer);
#define BAP_RUNTIME_TEST_REQINT8_STOP() StopSWTimer(&BapReqInt8_Timer);
#define BAP_RUNTIME_TEST_TASK_START() StartSWTimer(&BapTask_Timer);
#define BAP_RUNTIME_TEST_TASK_STOP() StopSWTimer(&BapTask_Timer);
#define BAP_RUNTIME_TEST_IRQ_START() StartSWTimer(&BapIRQ_Timer);
#define BAP_RUNTIME_TEST_IRQ_STOP() StopSWTimer(&BapIRQ_Timer);
#define BAP_RUNTIME_TEST_TRANSMIT_START() StartSWTimer(&BapTransmit_Timer);
#define BAP_RUNTIME_TEST_TRANSMIT_STOP() StopSWTimer(&BapTransmit_Timer);
#define BAP_RUNTIME_TEST_RECEIVE_START() StartSWTimer(&BapReceive_Timer);
#define BAP_RUNTIME_TEST_RECEIVE_STOP() StopSWTimer(&BapReceive_Timer);
#define BAP_RUNTIME_TEST_PROCESS_RECEIVED_START() StartSWTimer(&BapProcessReceived_Timer);
#define BAP_RUNTIME_TEST_PROCESS_RECEIVED_STOP() StopSWTimer(&BapProcessReceived_Timer);
#define BAP_RUNTIME_TEST_INDALL_START() if((apoPars->lsgId == 1) && (apoPars->fctId == 1)){StartSWTimer(&BapIndAll_Timer);}
#define BAP_RUNTIME_TEST_INDALL_STOP() if((apoPars->lsgId == 1) && (apoPars->fctId == 1)){StopSWTimer(&BapIndAll_Timer);}
#define BAP_RUNTIME_TEST_RX_IRQ_START() StartSWTimer(&BapRxIRQ_Timer);
#define BAP_RUNTIME_TEST_RX_IRQ_STOP() StopSWTimer(&BapRxIRQ_Timer);
#define BAP_RUNTIME_TEST_START_START() StartSWTimer(&BapStart_Timer);
#define BAP_RUNTIME_TEST_START_STOP() StopSWTimer(&BapStart_Timer);
#define BAP_RUNTIME_TEST_SHUTDOWN_START() StartSWTimer(&BapShutdown_Timer);
#define BAP_RUNTIME_TEST_SHUTDOWN_STOP() StopSWTimer(&BapShutdown_Timer);
#define BAP_RUNTIME_TEST_CANSENDTASK_START() StartSWTimer(&BapCanSendTask_Timer);
#define BAP_RUNTIME_TEST_CANSENDTASK_STOP() StopSWTimer(&BapCanSendTask_Timer);

#else /* BAP_RUNTIME_TEST */

#define BAP_RUNTIME_TEST_START()
#define BAP_RUNTIME_TEST_INDINT8_START()
#define BAP_RUNTIME_TEST_INDINT8_STOP()
#define BAP_RUNTIME_TEST_INDBS_START()
#define BAP_RUNTIME_TEST_INDBS_STOP()
#define BAP_RUNTIME_TEST_REQBS_START()
#define BAP_RUNTIME_TEST_REQBS_STOP()
#define BAP_RUNTIME_TEST_REQINT8_START()
#define BAP_RUNTIME_TEST_REQINT8_STOP()
#define BAP_RUNTIME_TEST_TASK_START()
#define BAP_RUNTIME_TEST_TASK_STOP()
#define BAP_RUNTIME_TEST_IRQ_START()
#define BAP_RUNTIME_TEST_IRQ_STOP()
#define BAP_RUNTIME_TEST_TRANSMIT_START()
#define BAP_RUNTIME_TEST_TRANSMIT_STOP()
#define BAP_RUNTIME_TEST_RECEIVE_START()
#define BAP_RUNTIME_TEST_RECEIVE_STOP()
#define BAP_RUNTIME_TEST_INDALL_START()
#define BAP_RUNTIME_TEST_INDALL_STOP()
#define BAP_RUNTIME_TEST_RX_IRQ_START()
#define BAP_RUNTIME_TEST_RX_IRQ_STOP()
#define BAP_RUNTIME_TEST_START_START()
#define BAP_RUNTIME_TEST_START_STOP()
#define BAP_RUNTIME_TEST_SHUTDOWN_START()
#define BAP_RUNTIME_TEST_SHUTDOWN_STOP()
#define BAP_RUNTIME_TEST_CANSENDTASK_START()
#define BAP_RUNTIME_TEST_CANSENDTASK_STOP()

#endif /* BAP_RUNTIME_TEST */
