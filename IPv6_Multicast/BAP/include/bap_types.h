/******************************************************************
 *
 *     Copyright (c) 2004-2023 Volkswagen AG, D-38436 Wolfsburg
 *
 ******************************************************************
 *
 * Projekt:    BAP
 * BAP Version: 1.12.2
 *
 ******************************************************************
 *
 * Beschreibung
 *
 *  Diese Datei enthaelt alle zugelassenen Typdefinitionen im BAP
 *  Projekt, die in mehr als einer Schicht verwendet werden.
 *
 ******************************************************************
 *
 * Versionsgeschichte (ohne SCM)
 *
 * Datum        Version     Autor       Beschreibung
 * ----------------------------------------------------------------
 * 2023-10-10	1.12.2		DRH			[EEARCH-35935] Release preparation, adapt Copyright date and version number.
 * 2022-11-15   1.12.1      DRH         [SSWPPB-297] Renamed macros and global variables module specific
 * 2022-10-21	1.12.1		DRH			[SSWPPB-296] Release preparation, adapt Copyright date and version number.
 * 2022-06-17	1.12.0		DRH			[SSWPPB-269] Release preparation, adapt Copyright date and version number.
 * 2021-12-07	1.11.3		JEO			[SSWPPB-244] Release preparation, adapt Copyright date and version number.
 * 2021-03-08   1.11.3      DRH         [SSWPPB-142] Replaced magic numbers by constants
 * 2021-03-01	1.11.3		JEO			[SSWPPB-142] Improve jutification of Pc-Lint deac or MISRA rules violation.
 * 2020-03-31   1.11.1      ODD         [SSWPPB-93] add type definition "paru8Buffer_t" which are needed to remove compiler error
 *                                      when using strict compiler settings under Autosar
 * 2016-10-21	1.8.1       FST         [SSWCCB-2410] Softwareschalter DLL_COMPILATION zur Unterscheidung
 *                                      der Erzeugung von Steuergeraete-Code und der BAP-Dll eingefuegt
 * 2014-08-05	1.8.0       WWU         [SSWCCB-1908] BapRequest_et, BapIndication_et, BapAcknowledge_et wird in AUTOSAR mit
 *                                      verkuerztem Name definiert.
 * 2012-02-28	1.6.3       WWU         Definitionen von AUTOSAR-Types entfernt. Wird in bap_defines.h durch Rte_type.h definiert.
 * 2011-06-21	1.6.1.2     WWU         Definitionen von BapError_et, BapRequest_et, BapAcknowledge_et und BapIndication_et werden
 *                                      sich durch Macros fuer verschiedene Integrationszwecke (AUTOSAR oder Embedded) unterschieden.
 * 2011-05-27   1.6.1       NQU         Doppeldeklarationsschutzes nach EB-Standard (RTE_TYPE_name zusaetzlich zu Rte_TypeDef_name)
 * 2011-04-04   1.6         NQU         Geaendert die Stelle wo die fctId_t und lsgId_t ifndefs geprueft werden
 * 2011-02-18   1.6 	    NQU         Es wird ueberprueft ob die BAP Typen definiert in Rte_Type.h (#ifndef)
 * 2008-08-26   1.5.0.1     RVE         BapIndication_t und BapAcknowledge_t mit festen Werten fuer BAPSimGen
 * 2007-09-18   1.5         VSA         Erweiterung der Acknowledge-Typen mit Ack und DataAck.
 * 2007-09-13   1.5         ALI         Einige Macros nach bap_user_stdtypes.h verschoben
 * 2007-08-27   1.5         RVE         Erweiterung der Requests/Indications um StatusAck und Ack.
 *                                      Einschraenkung der relevanten Requests auf Methoden.
 *                                      Manuelle Nummerierung bei Indications entfernt.
 * 2007-07-18   1.5         SHU         Acknowledge fuer SmallFSG eingefuehrt.
 * 2006-06-02   1.4         ALA         Defines, welche in bap_user_stdtypes.h bereits vorhanden sind, entfernt.
 * 2006-04-12   1.4         MWI         Verlagerung der Standardtypen nach bap_stdtypes.h bzw bap_user_stdtypes.h
 * 2006-04-12   1.4         ALA         Unterstuetzung von symbolischen IDs in der Konfiguration.
 * 2006-04-12   1.4         ALA         Enum Datentyp fuer BAP_Acknowledge hinzugefuegt.
 * 2006-04-12   1.4         ALA         Unterstuetzung von BAP_ROM_DATA_FAR.
 * 2005-04-25   1.3         CRI         BapErr_Aborted entfernt, muss von Applikation definiert werden
 * 2005-04-10   1.3         CRI         BapErr_Aborted hinzugefuegt fuer FSG beim Methodenabbruch
 * 2005-04-10   1.3         CRI         BapInd_Processing_CNF hinzugefuegt fuer Methoden
 * 2004-11-17   1.2         JOK         enum BapError_t ist nun in bap_defines.h definiert und hier
 *                                      nur noch zu Dokumentationszwecken enthalten.
 * 2004-09-03   1.2         JOK         Konstante Methode Indications definiert
 * 2004-09-03   1.2         JOK         Konstante Methode Requests definiert
 * 2004-09-17   1.1.1       ALA         Defines von internen FctIds von bap_config.h uebernommen,
 *                                      da diese auch in der Applikation benoetigt werden.
 ******************************************************************/

#ifndef BAP_TYPES_H
#define BAP_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */


/* Eigene Header-Dateien "..." */
#include "bap_user_stdtypes.h"

#include "bap_defines.h"


/* Makro-Definitionen */



/**
 *  Auswertung der Steuergeraeteklasse und Abbildung auf
 *  die Compilerschalter fuer die einzelnen Funktionaliteaten.
 */
#ifdef BAP_SGTYPE_IS_ASG_AND_LARGE_FSG
    /** Compiler-Schalter, beide Varianten zusammen */
    #define BAP_ASG
    #define BAP_FSG
    /** Compiler-Schalter: 8-Bit Datentyp wird unterstuetzt */
    #define BAP_USES_DATATYPE_8
    /** Compiler-Schalter: 16-Bit Datentyp wird unterstuetzt */
    #define BAP_USES_DATATYPE_16
    /** Compiler-Schalter: 32-Bit Datentyp wird unterstuetzt*/
    #define BAP_USES_DATATYPE_32
    /** Compiler-Schalter: ByteSequence Datentyp wird unterstuetzt*/
    #define BAP_USES_DATATYPE_BS
    /** Compiler-Schalter: Segmentierung von Botschaften ueber Bus einschalten */
    #define BAP_USES_SEGMENTATION
    /** Compiler-Schalter: Unterstuetzung von Acknowledge-Mechanismus */
    #define BAP_USES_ACKNOWLEDGE
    /** Compiler-Schalter: Unterstuetzung von Funktionsklasse Array einschalten */
    #define BAP_USES_ARRAYS
    /** Compiler-Schalter: Unterstuetzung von Methoden einschalten */
    #define BAP_USES_METHODS
    /** Compiler-Schalter: StatusAll als Block */
    #define BAP_USES_STATUS_ALL
    /** Compiler-Schalter: Debug/Diagnose kann fuer eine LsgId ein/ausgeschaltet werden */
    #define BAP_DBG_PER_LSG
    /** Compiler-Schalter: Begrenzung der Taskzeit durch Begrenzung der Anzahl an Indications bzw. CanTransmit-Aufrufen */
    #define BAP_TASKTIME_LIMIT
#endif

#ifdef BAP_SGTYPE_IS_ASG
    /** Compiler-Schalter: Spezielle Funktionalitaet eines ASG (Cache/Retry/HB-Monitoring) */
    #define BAP_ASG
    /** Compiler-Schalter: 8-Bit Datentyp wird unterstuetzt */
    #define BAP_USES_DATATYPE_8
    /** Compiler-Schalter: 16-Bit Datentyp wird unterstuetzt */
    #define BAP_USES_DATATYPE_16
    /** Compiler-Schalter: 32-Bit Datentyp wird unterstuetzt*/
    #define BAP_USES_DATATYPE_32
    /** Compiler-Schalter: ByteSequence Datentyp wird unterstuetzt*/
    #define BAP_USES_DATATYPE_BS
    /** Compiler-Schalter: Segmentierung von Botschaften ueber Bus einschalten */
    #define BAP_USES_SEGMENTATION
    /** Compiler-Schalter: Unterstuetzung von Acknowledge-Mechanismus */
    #define BAP_USES_ACKNOWLEDGE
    /** Compiler-Schalter: Unterstuetzung von Funktionsklasse Array einschalten */
    #define BAP_USES_ARRAYS
    /** Compiler-Schalter: Unterstuetzung von Methoden einschalten */
    #define BAP_USES_METHODS
    /** Compiler-Schalter: Debug/Diagnose kann fuer eine LsgId ein/ausgeschaltet werden */
    #define BAP_DBG_PER_LSG
    /** Compiler-Schalter: Begrenzung der Taskzeit durch Begrenzung der Anzahl an Indications bzw. CanTransmit-Aufrufen */
    #define BAP_TASKTIME_LIMIT
#endif

#ifdef BAP_SGTYPE_IS_LARGE_FSG
    /** Compiler-Schalter: Spezielle Funktionalitaet eines FSG (HB-Senden) */
    #define BAP_FSG
    /** Compiler-Schalter: 8-Bit Datentyp wird unterstuetzt */
    #define BAP_USES_DATATYPE_8
    /** Compiler-Schalter: 16-Bit Datentyp wird unterstuetzt */
    #define BAP_USES_DATATYPE_16
    /** Compiler-Schalter: 32-Bit Datentyp wird unterstuetzt*/
    #define BAP_USES_DATATYPE_32
    /** Compiler-Schalter: ByteSequence Datentyp wird unterstuetzt*/
    #define BAP_USES_DATATYPE_BS
    /** Compiler-Schalter: Segmentierung von Botschaften ueber Bus einschalten */
    #define BAP_USES_SEGMENTATION
    /** Compiler-Schalter: Unterstuetzung von Acknowledge-Mechanismus */
    #define BAP_USES_ACKNOWLEDGE
    /** Compiler-Schalter: Unterstuetzung von Funktionsklasse Array einschalten */
    #define BAP_USES_ARRAYS
    /** Compiler-Schalter: Unterstuetzung von Methoden einschalten */
    #define BAP_USES_METHODS
    /** Compiler-Schalter: Debug/Diagnose kann nur global ein/ausgeschaltet werden */
    #define BAP_DBG_ON_OFF
    /** Compiler-Schalter: StatusAll als Block */
    #define BAP_USES_STATUS_ALL
    /** Compiler-Schalter: Begrenzung der Taskzeit durch Begrenzung der Anzahl an Indications bzw. CanTransmit-Aufrufen */
    #define BAP_TASKTIME_LIMIT
#endif

/** Konstante fuer die interne FctId fuer GETALL */
/* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_GETALL fit in enum. */
#define BAP_FCTID_GETALL  /*lint -save -e9034 */  ((fctId_t)1)  /*lint -restore */

/** Konstante fuer die interne FctId fuer BAPCONFIG */
/* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_BAPCONFIG fit in enum. */
#define BAP_FCTID_BAPCONFIG /*lint -save -e9034 */ ((fctId_t)2) /*lint -restore */

/* MISRA_2012_REQ_10.3 : PC-Lint 9.00L throws warning for no reasons when fctId_t is defined as enum.
 * It is purely a tool failure which does not cause any side effects. Should be corrected in the new product
 * PC Lint Plus. Documented with a mail from the Lint team in the SSWCCB-2522_BAP-Entwicklung auf MISRA2012 umstellen folder */
/* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_FCTLIST fit in enum. */

/** Konstante fuer die interne FctId fuer FUNCTIONLIST */
#define BAP_FCTID_FCTLIST /*lint -save -e9034 */  ((fctId_t)3) /*lint -restore */

/** Konstante fuer die Laenge von FUNCTIONLIST */
#define BAP_FCTID_FCTLIST_SIZE ((uint32_t)8)

/** Konstante fuer den letzten Index in FUNCTIONLIST */
#define BAP_FCTLIST_LASTINDEX 7

/** Konstante fuer die interne FctId fuer HEARTBEAT */
/* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_HEARTBEAT fit in enum. */
#define BAP_FCTID_HEARTBEAT /*lint -save -e9034 */ ((fctId_t)4) /*lint -restore */

/** Bitmap fuer Fct-ID 2 (BAP-Config) in BIG Endian */
#define BAP_FCTID_BAPCONFIG_BITMAP ((uint8_t)0x20)

/** Bitmap fuer Fct-ID 2 und 3 (BAP-Config und FctList available) in BIG Endian */
#define BAP_FCTID_BAPCONFIG_FCTLIST_BITMAP ((uint8_t)0x30)


/* Typ-Definitionen */

/**
 *  Dieser Typ beschreibt alle Request-Typen, die von der Applikation genutzt
 *  werden koennen.
 *
 *  @remark (intern)
 *  Die Enum-Werte sind fest vergeben, um einen einfachen Zugriff auf die
 *  Abbildungsmatrix fuer die Abbildung f(Req/Inc, FctKlasse) => OpCode zu erreichen.
 *
 *  @remark Es werden jeweils nur die fuer ASG oder FSG gueltigen Request-Typen definiert.
 */
#ifndef BAP_USES_ASR_WRAPPER /* Falls AUTOSAR verwendet ist */
typedef enum BapRequest_t
{
#ifdef BAP_ASG
    /** DataSetGet_REQ */
    BapReq_DataSetGet = 0,

    /** DataSet_REQ */
    BapReq_DataSet = 1,

#ifdef BAP_USES_METHODS
    /** Start_REQ */
    BapReq_Start = 5,

    /** StartResult_REQ */
    BapReq_StartResult = 6,

    /** Abort_REQ */
    BapReq_Abort = 7,
#endif /* BAP_USES_METHODS */

    /** DataGet_REQ */
    BapReq_DataGet = 2,

    /** Ack_REQ */
    BapReq_Ack = 11,
#endif /* BAP_ASG */

#ifdef BAP_FSG
    /** Data_CNF */
    BapReq_Data = 3,

    /** DataAck_REQ */
    BapReq_DataAck = 10,

#ifdef BAP_USES_ARRAYS
    /** Changed_REQ */
    BapReq_Changed = 4,
#endif /* #ifdef BAP_USES_ARRAYS */

#ifdef BAP_USES_METHODS
    /** Processing_REQ */
    BapReq_Processing = 8,

    /** Result_REQ */
    BapReq_Result = 9,
#endif /* BAP_USES_METHODS */

#endif /* BAP_FSG */

    /** Interne Kennzeichnung fuer einen ungueltigen Request, fuer InitSendBuffer und CacheGet */
    BapReq_Invalid = 0x1f
} BapRequest_et;
#else
typedef BapReq_et BapRequest_et;
#endif /** #ifdef BAP_USES_ASR_WRAPPER */

/** Konstante fuer die Anzahl von Requestarten */
#define BAP_NUMBER_OF_REQUESTS 12

/**
 *  Dieser Typ beschreibt alle Acknowledge-Typen, welche von BAP an die Applikation
 *  gemeldet werden. @see BAP_Acknowledge.
 *
 *  Nach dem erfolgreichen Versenden eines Requests, welcher von der Applikation
 *  an BAP durch Aufruf von BAP_Request... eingeleitet wurde, wird der entsprechende
 *  Acknowledge-Typ and die Applikation gemeldet.
 *  Dieser beinhaltet im Namen die Funktionsklasse sowie den Request-Typ, der von
 *  der Applikation an BAP uebergeben wurde.
 *
 */
#ifndef BAP_USES_ASR_WRAPPER /* Falls AUTOSAR verwendet ist */
typedef enum BapAcknowledge_t
{
#ifdef BAP_ASG
    /** Ein DataSetGet-Request eines Properties wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Property_DataSetGet = 0,

    /** Ein DataSetGet-Request eines Arrays wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Array_DataSetGet = 1,

    /** Ein DataSet-Request eines Properties wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Property_DataSet = 2,

    /** Ein DataSet-Request eines Arrays wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Array_DataSet = 3,

    /** Ein Start-Request einer Methode wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Method_Start = 4,

    /** Ein StartResult-Request einer Methode wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Method_StartResult = 5,

    /** Ein Abort-Request einer Methode wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Method_Abort = 6,

    /** Ein DataGet-Request eines Properties wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Property_DataGet = 7,

    /** Ein DataGet-Request eines Arrays wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Array_DataGet = 8,

    /** Ein DataGet-Request (GetAll) des Caches wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Cache_DataGet = 9,

    /** Ein Ack-Request eines Properties wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Property_Ack = 10,

#endif /* #ifdef BAP_ASG */

#ifdef BAP_FSG
    /** Ein Data-Request (Status) eines Properties wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Property_Data = 11,

    /** Ein DataAck-Request (Status) eines Properties wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Property_DataAck = 12,

    /** Ein Error-Request eines Properties wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Property_Error = 13,
#ifdef BAP_USES_ARRAYS
    /** Ein Data-Request eines Arrays wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Array_Data = 14,

    /** Ein Changed-Request eines Arrays wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Array_Changed = 15,

    /** Ein Error-Request eines Arrays wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Array_Error = 16,
#endif /* #ifdef BAP_USES_ARRAYS */
#ifdef BAP_USES_METHODS
    /** Ein Processing-Request einer Methode wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Method_Processing = 17,

    /** Ein Result-Request einer Methode wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Method_Result = 18,

    /** Ein Error-Request einer Methode wurde vollstaendig an den Bus-Treiber uebergeben */
    BapAck_Method_Error = 19,
#endif /* BAP_USES_METHODS */
#endif /* #ifdef BAP_FSG */
    /** Dieser Acknowledge-Typ wird von BAP nur intern verwendet und nicht an die Applikation gemeldet */
    BapAck_Nothing = 0x1f
} BapAcknowledge_et;
#else
typedef BapAck_et BapAcknowledge_et;
#endif /** #ifdef BAP_USES_ASR_WRAPPER */

/**
 *  Dieser Typ beschreibt alle Indication-Typen, welche an die Applikation
 *  gemeldet werden koennen.
 *  Die Enum-Werte sind fest vergeben, um einen einfachen Zugriff auf die
 *  Abbildungsmatrix fuer die Abbildung f(Req/Inc, FctKlasse) => OpCode zu erreichen.
 *
 *  @remark Es werden jeweils nur die fuer ASG oder FSG gueltigen Indication-Typen definiert.
 */
#ifndef BAP_USES_ASR_WRAPPER /* Falls AUTOSAR verwendet ist */
typedef enum BapIndication_t
{
#ifdef BAP_ASG
    /** Data_RSP */
    BapInd_Data = 0,

    /** Reset_IND */
    BapInd_Reset = 1,

    /** DataAck_IND */
    BapInd_DataAck = 2,

#ifdef BAP_USES_METHODS
    /** Result_IND */
    BapInd_Result = 3,

    /** Processing_IND */
    BapInd_Processing = 4,
#endif /*BAP_USES_METHODS*/

#ifdef BAP_USES_ARRAYS
    /** Changed_IND */
    BapInd_Changed = 5,
#endif /* #ifdef BAP_USES_ARRAYS */
#endif /* BAP_ASG */

#ifdef BAP_FSG
    /** DataSetGet_IND */
    BapInd_DataSetGet = 6,

    /** DataSet_IND */
    BapInd_DataSet = 7,

    /** DataGet_IND */
    BapInd_DataGet = 8,

    /** Ack_IND */
    BapInd_Ack = 9,

#ifdef BAP_USES_METHODS
    /** App muss Processing schicken */
    BapInd_Processing_CNF = 10,

    /** Start_IND */
    BapInd_Start = 11,

    /** StartResult_IND */
    BapInd_StartResult = 12,

    /** AbortResult_IND */
    BapInd_Abort = 13,
#endif /* BAP_USES_METHODS */
#endif /* BAP_FSG */

    /** Interne Kennzeichnung fuer eine ungueltige Indication */
    BapInd_Invalid = 0x1f
} BapIndication_et;
#else
typedef BapInd_et BapIndication_et;
#endif /* #ifdef BAP_USES_ASR_WRAPPER */

#ifdef DLL_COMPILATION
typedef uint32_t BapCanMsgId_t;
#elif defined (BAP_USES_16BIT_CAN_MESSAGE_HANDLE)
/** Der Datentyp nimmt die ID eines Can Message Handles oder die Can Id selbst auf.
 *  Im einen Fall wird in die XML-Datei der symbolische Name der CanMessage eingetragen.
 *  Im anderen Fall wird direkt die CAN-Id (16Bit) als Zahlenwert (z.B. 0x741) eingetragen.
 */
typedef uint16_t BapCanMsgId_t;
#else
typedef uint8_t BapCanMsgId_t;
#endif /* #if defined (BAP_USES_16BIT_CAN_MESSAGE_HANDLE) || defined (DLL_COMPILATION) */

/** Der Datentyp nimmt den Can-Kanal auf. Dieser ordnet eine CanId einem
 *  physikalischen Bus zu.
 */
typedef uint8_t BapCanInterfaceChannel_t;



/** The data-type will be used in the file bap_config.h, bap_bclcan, config.c
 * the data-type definition BapBufferWithLength_ot to prevent implicit type-cast
 * and also be used in generated config.c file to prevent compiler errors
 * under autosar when using strict compiler settings
 */
typedef uint8_t (*paru8Buffer_t)[];
/* Const Deklarationen */

/* Externe globale Variablen */

/* Deklarationen von Funktionen */


#ifdef __cplusplus
}
#endif

#endif      /* #ifndef BAP_UTIL_BAPTYPES_H */

