/*************************************************************************
 *
 *       System: MergeCOM-3 - Advanced Integrator's Tool Kit
 *
 *    $Workfile: mergecom.h $
 *
 *    $Revision: 20 $
 *
 *        $Date: 3/09/01 9:24a $
 *
 *  Description: This module contains defintions used by applications
 *               which use the MergeCOM-3 Advanced Tool Kit networking
 *               functions.
 *
 *************************************************************************
 *
 *                   (c) 2002-2005 Merge Healthcare
 *                     Milwaukee, Wisconsin 53214
 *
 *                      -- ALL RIGHTS RESERVED --
 *
 *  This software is furnished under license and may be used and copied
 *  only in accordance with the terms of such license and with the
 *  inclusion of the above copyright notice.  This software or any other
 *  copies thereof may not be provided or otherwise made available to any
 *  other person.  No title to and ownership of the software is hereby
 *  transferred.
 *
 ************************************************************************/



#ifndef MTI_MERGECOM_H
#define MTI_MERGECOM_H


#if !defined(EXP_FUNC)
#if defined(WIN311)
#define EXP_FUNC        __far __pascal __export
#define EXP_FUNC_CDECL  __far __export
#define NOEXP_FUNC      __far __pascal
#define EXP_PRE
#elif defined(INTEL_BCC)
#define EXP_FUNC        __export
#define EXP_FUNC_CDECL  __export
#define NOEXP_FUNC
#define EXP_PRE
#elif defined(INTEL_DOTNET)
#define EXP_FUNC        __stdcall
#define EXP_FUNC_CDECL
#define NOEXP_FUNC      __stdcall
#define EXP_PRE         __declspec(dllexport)
#elif defined(_WIN32)
#define EXP_FUNC        __cdecl
#define EXP_FUNC_CDECL  __cdecl
#define NOEXP_FUNC      __cdecl
#define EXP_PRE
#else
#define EXP_FUNC
#define EXP_FUNC_CDECL
#define NOEXP_FUNC
#define EXP_PRE
#endif
#endif


#if defined(_WIN32) && !defined(_PHAR_LAP) 
#ifndef _WINSOCKAPI_
#include <winsock2.h>
#endif
#elif defined(VXWORKS)
#include <socket.h>
#else
#include <sys/socket.h>
#endif


#if defined(_WIN32) && !defined(_PHAR_LAP)
typedef SOCKET MC_SOCKET;
#else
typedef int MC_SOCKET;
#endif


#include "mcstatus.h"
#include "mc3msg.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MACINTOSH
#pragma enumsalwaysint on
#pragma options align=mac68k
#endif

#ifdef __BORLANDC__
#pragma option -b
#endif

/* ======================================================================== *
 *                        User Identity Type
 * ======================================================================== *
 *  This enumerated value is used to specify the types of User Identity     * 
 *  negotiation defined in DICOM Supplement 99 and DICOM CP 595.            */
typedef enum {
    NO_USER_IDENTITY = 0,
    USERNAME = 1,
    USERNAME_AND_PASSCODE = 2,
    KERBEROS_SERVICE_TICKET = 3,
    SAML_ASSERTION = 4
} USER_IDENTITY_TYPE;


/* ======================================================================== *
 *                      User Identity Field Type
 * ======================================================================== *
 *  This enumerated value represents several User Identity negotiation      * 
 *  related fields that information can be retrieved for.   User Identity   *
 *  negotiation was defined in DICOM Supplement 99 and DICOM CP 595         */
typedef enum {
    PRIMARY_FIELD,
    SECONDARY_FIELD,
    SERVER_RESPONSE_FIELD
} USER_IDENTITY_FIELD_TYPE;


/* ======================================================================== *
 *                    Association Information Structure                     *
 * ======================================================================== *
 *  Calls to MC_Get_Association_Info must pass the address of a variable    *
 *   of this type.  The structure will be filled in by that function.       */
typedef struct MC_Assoc_Info {
    int     NumberOfProposedServices;        /* From service list */
    int     NumberOfAcceptableServices;      /* Acceptable to both sides */
    char    RemoteApplicationTitle[20];      /* 16-characters max */
    char    RemoteHostName[66];              /* Network node name
                                                64-characters max*/
    MC_SOCKET Tcp_socket;                    /* TCP Socket used for
                                                association */
    char    RemoteIPAddress[66];             /* Network IP Address */
    char    LocalApplicationTitle[20];       /* 16-characters max */
    char    RemoteImplementationClassUID[66];/* 64-characters max */
    char    RemoteImplementationVersion[20]; /* 16-characters max */
    unsigned long LocalMaximumPDUSize;
    unsigned long RemoteMaximumPDUSize;
    unsigned short MaxOperationsInvoked;     /* Negotiated Max operations
                                              * invoked by the assoc requestor */
    unsigned short MaxOperationsPerformed;   /* Negotiated Max operations
                                              * performed by the assoc requestor */
    USER_IDENTITY_TYPE UserIdentityType;     /* User Identity negotiation type
                                              * as defined in DICOM Supplement
                                              * 99. */
    unsigned char PositiveResponseRequested; /* Set according to if a positive
                                              * response is requested when 
                                              * User Identity is specified. */
    unsigned char PositiveResponseReceived;  /* Set for association requestors
                                              * if a positive response was 
                                              * received from the association
                                              * acceptor */
} AssocInfo;

/* ======================================================================== *
 *                     Connection type identifier                           *
 * ======================================================================== */
typedef enum {
    REQUESTER_CONNECTION,       /* MC_Open_[Secure]_Association */
    ACCEPTOR_CONNECTION         /* MC_Wait_For_[Secure]_Association */
} CONN_TYPE;

/* ======================================================================== *
 *                     Secure Socket Status Codes                           *
 * ======================================================================== */
typedef enum {
    SS_NORMAL_COMPLETION,
    SS_ERROR,
    SS_TIMEOUT,
    SS_SESSION_CLOSED
} SS_STATUS;


/* ======================================================================== *
 *                    Socket Security Functions Structure                   *
 * ======================================================================== *
 *  This structure provides MergeCOM-3 with event handler functions used    *
 *   while processing a Secure TCP/IP Connection.                           */
typedef struct MC_Secure_Socket_Functions_Struct 
{
    SS_STATUS (NOEXP_FUNC *SS_Session_Start)(MC_SOCKET SocketToUse, CONN_TYPE ConnectionType, void* ApplicationContext, void** SecurityContext);
    SS_STATUS (NOEXP_FUNC *SS_Read)(void* SScontext, void* ApplicationContext, char* Buffer, unsigned int  BytesToRead, unsigned int* BytesRead, int Timeout);
    SS_STATUS (NOEXP_FUNC *SS_Write)(void* SScontext, void* ApplicationContext, char* Buffer, unsigned int  BytesToWrite, unsigned int* BytesWritten, int Timeout);
    void      (NOEXP_FUNC *SS_Session_Shutdown)(void* SScontext, void* ApplicationContext);
} SecureSocketFunctions;

/* ======================================================================== *
 *                      Capture File Callback Functions                     *
 * ======================================================================== *
 *  This structure provides MergeCOM-3 with event handler functions used    *
 *  to capture the network data stream.  A pointer to this structure is     *
 *  passed with the MC_Register_NetworkCapture_Callbacks() function.        *
 *  The MC_Register_NetworkCapture_Callbacks() is used to override the      *
 *  default MergeCOM-3 network capture functions.                           */
typedef struct MC_NetworkCaptureInfo_Struct 
{
    void* CAP_applicationContext;
    int   (NOEXP_FUNC *CAP_initialization)(void* Acontext, long AmaxFileSize, char* AfileName, int AnumFiles, int ArewriteFiles);
    void  (NOEXP_FUNC *CAP_shutdown)(void* Acontext);
    void* (NOEXP_FUNC *CAP_getConnectionContext)(void* AppContext, struct sockaddr *AIPaddr1, struct sockaddr *AIPaddr2);
    void  (NOEXP_FUNC *CAP_freeConnectionContext)(void* AppContext, void* AconnContext);
    int   (NOEXP_FUNC *CAP_conectionOpened)(void* appContext, void* connContext, struct sockaddr *sourceIPaddr, struct sockaddr *destIPaddr);
    int   (NOEXP_FUNC *CAP_conectionClosed)(void* appContext, void* connContext, struct sockaddr *sourceIPaddr, struct sockaddr *destIPaddr);
    int   (NOEXP_FUNC *CAP_dataSent)(void* appContext, void* connContext, struct sockaddr *sourceIPaddr, struct sockaddr *destIPaddr, char* data, long dataLength);
} MC_NetworkCaptureInfo;

/* ======================================================================== *
 *                     SCU and SCP Role information                         *
 * ======================================================================== */
typedef enum {
        SCU_ROLE,
        SCP_ROLE,
        BOTH_ROLES
} ROLE_TYPE;


/* ======================================================================== *
 *                Related General Service Information Structure             *
 * ======================================================================== *
 *  Calls to MC_Get_First_Acceptable_Service and                            *
 *   MC_Get_Next_Acceptable_Service must pass the address of a variable of  *
 *   this type.  The structure will be filled in by that function.          */
typedef struct MC_Related_SOP_Class_Info {
    char            ServiceName[50];        /* MergeCOM-3 Service Name. May
                                               be zero length if the SOP
                                               Class is not known by
                                               MergeCOM-3 */
    char            SOPClassUID[66];        /* Service Class UID for the
                                               service if defined in the
                                               association request */
} RelatedSOPClass;


/* ======================================================================== *
 *                      Service Information Structure                       *
 * ======================================================================== *
 *  Calls to MC_Get_First_Acceptable_Service and                            *
 *   MC_Get_Next_Acceptable_Service must pass the address of a variable of  *
 *   this type.  The structure will be filled in by that function.          */
typedef struct MC_Service_Info {
    char            ServiceName[50];        /* MergeCOM-3 Service Name.  May
                                               be zero length if this context
                                               was accepted because of a
                                               related general SOP Class that
                                               we do support */
    TRANSFER_SYNTAX SyntaxType;             /* Transfer syntax negotiated
                                               for the service */
    ROLE_TYPE       RoleNegotiated;         /* The role negotiated for the
                                               service */
    int             PresentationContextID;  /* Presentation Context ID */
    char            SOPClassUID[66];        /* SOP Class UID associated
                                               with ServiceName */
    char            ServiceClassUID[66];    /* Optional Service Class UID
                                               for the service if defined
                                               in the association request */
    int             NumberRelatedSOPClasses;/* Number of related general
                                               SOP Classes contained in the
                                               association request */
    RelatedSOPClass RelatedSOPClasses[10];  /* Array containing related
                                               general SOP classes for this
                                               negotiated serivce */
} ServiceInfo;



/* ======================================================================== *
 *               Association Rejection Reasons Enumerated Type              *
 * ======================================================================== *
 *  Calls to MC_Reject_Association must use this enumerated type to         *
 *   specify the reason why the association is being rejected.  Note that   *
 *   not all of the potential rejection reasons are listed because they are *
 *   automatically handled by the tool kit.                                 */
typedef enum {
        PERMANENT_NO_REASON_GIVEN,
        TRANSIENT_NO_REASON_GIVEN,
        PERMANENT_CALLING_AE_TITLE_NOT_RECOGNIZED,

        TRANSIENT_TEMPORARY_CONGESTION,
        TRANSIENT_LOCAL_LIMIT_EXCEEDED,

        PERMANENT_CALLED_AE_TITLE_NOT_RECOGNIZED,
        PERMANENT_APPLICATION_CONTEXT_NAME_NOT_SUPPORTED,
        PERMANENT_CALLING_AE_QUALIFIER_NOT_RECOGNIZED,
        PERMANENT_CALLING_AP_INVOCATION_ID_NOT_RECOGNIZED,
        PERMANENT_CALLING_AE_INVOCATION_ID_NOT_RECOGNIZED,
        PERMANENT_CALLED_AE_QUALIFIER_NOT_RECOGNIZED,
        PERMANENT_CALLED_AP_INVOCATION_ID_NOT_RECOGNIZED,
        PERMANENT_CALLED_AE_INVOCATION_ID_NOT_RECOGNIZED,

        PERMANENT_CALLED_PRES_ADDRESS_UNKNOWN,
        PERMANENT_PRES_PROTOCOL_VERSION_NOT_SUPPORTED,
        PERMANENT_NO_PRESENTATION_SAP_AVAILABLE

} REJECT_REASON;




/* ======================================================================== *
 *                  User Identity Positive Response Requested               *
 * ======================================================================== *
 * Definitions for the values for Positive-Response_Requested as defined in * 
 * defined in DICOM Supplement 99 - User Indeityt Services.                 */

#define NO_RESPONSE_REQUESTED  (unsigned char)0
#define POSITIVE_RESPONSE_REQUESTED  (unsigned char)1


/* ======================================================================== *
 *                      Message Response Status Codes                       *
 * ======================================================================== *
 *           NOTE: NEVER change the values assigned to these codes!         *
 * Definitions for some of the more common DICOM Service Class status codes */

#define RESP_STATUS unsigned short


/* ======================================================================== *
 *                  Storage Service Class: C_STORE_RSP Codes                *
 * ======================================================================== */
/* SUCCESS code */
#define C_STORE_SUCCESS                         ((RESP_STATUS)0x0000)

/* WARNING codes */
#define C_STORE_WARNING_ELEMENT_COERCION        ((RESP_STATUS)0xB000)
#define C_STORE_WARNING_INVALID_DATASET         ((RESP_STATUS)0xB007)
#define C_STORE_WARNING_ELEMENTS_DISCARDED      ((RESP_STATUS)0xB006)

/* FAILURE codes */
#define C_STORE_FAILURE_REFUSED_NO_RESOURCES    ((RESP_STATUS)0xA700)
#define C_STORE_FAILURE_INVALID_DATASET         ((RESP_STATUS)0xA900)
#define C_STORE_FAILURE_CANNOT_UNDERSTAND       ((RESP_STATUS)0xC000)
#define C_STORE_FAILURE_PROCESSING_FAILURE      ((RESP_STATUS)0x0110)


/* ======================================================================== *
 *        Study Content NotificationService Class: C_STORE_RSP Codes        *
 * ======================================================================== */
/* SUCCESS codes */
#define C_STORE_SUCCESS_COMPLETE_STUDY_EXISTS   ((RESP_STATUS)0x0000)
#define C_STORE_SUCCESS_PARTIAL_STUDY_EXISTS    ((RESP_STATUS)0x0001)
#define C_STORE_SUCCESS_STUDY_DOES_NOT_EXIST    ((RESP_STATUS)0x0002)
#define C_STORE_SUCCESS_UNKNOWN_EXISTENCE       ((RESP_STATUS)0x0003)

/* FAILURE code */
#define C_STORE_FAILED_OPERATION                ((RESP_STATUS)0xC002)


/* ======================================================================== *
 *                Verification Service Class: C_ECHO_RSP Codes              *
 * ======================================================================== */
/* SUCCESS code */
#define C_ECHO_SUCCESS                          ((RESP_STATUS)0x0000)


/* ======================================================================== *
 *               Query/Retrieve Service Class: C_FIND_RSP Codes             *
 * ======================================================================== */
/* SUCCESS code */
#define C_FIND_SUCCESS                          ((RESP_STATUS)0x0000)

/* PENDING codes */
#define C_FIND_PENDING                          ((RESP_STATUS)0xFF00)
#define C_FIND_PENDING_NO_OPTIONAL_KEY_SUPPORT  ((RESP_STATUS)0xFF01)

/* FAILURE codes */
#define C_FIND_FAILURE_REFUSED_NO_RESOURCES     ((RESP_STATUS)0xA700)
#define C_FIND_FAILURE_INVALID_DATASET          ((RESP_STATUS)0xA900)
#define C_FIND_FAILURE_UNABLE_TO_PROCESS        ((RESP_STATUS)0xC001)
#define C_FIND_FAILURE_RPI_UNABLE_TO_PROCESS    ((RESP_STATUS)0xC000)
#define C_FIND_FAILURE_MORE_THAN_ONE_MATCH_FOUND ((RESP_STATUS)0xC100)
#define C_FIND_FAILURE_UNABLE_TO_SUPPORT_REQUESTED_TEMPLATE ((RESP_STATUS) 0xC200)

/* CANCEL code */
#define C_FIND_CANCEL_REQUEST_RECEIVED          ((RESP_STATUS)0xFE00)


/* ======================================================================== *
 *               Query/Retrieve Service Class: C_MOVE_RSP Codes             *
 * ======================================================================== */
/* SUCCESS code */
#define C_MOVE_SUCCESS_NO_FAILURES              ((RESP_STATUS)0x0000)

/* WARNING code */
#define C_MOVE_WARNING_ONE_OR_MORE_FAILURES     ((RESP_STATUS)0xB000)

/* PENDING code */
#define C_MOVE_PENDING_MORE_SUB_OPERATIONS      ((RESP_STATUS)0xFF00)

/* FAILURE codes */
#define C_MOVE_FAILURE_REFUSED_CANT_CALCULATE   ((RESP_STATUS)0xA701)
#define C_MOVE_FAILURE_REFUSED_CANT_PERFORM     ((RESP_STATUS)0xA702)
#define C_MOVE_FAILURE_REFUSED_DEST_UNKNOWN     ((RESP_STATUS)0xA801)
#define C_MOVE_FAILURE_INVALID_DATASET          ((RESP_STATUS)0xA900)
#define C_MOVE_FAILURE_UNABLE_TO_PROCESS        ((RESP_STATUS)0xC001)

/* FAILURE codes for Instance Root Retrieve */
#define C_MOVE_FAILURE_NONE_OF_THE_FRAMES_FOUND       ((RESP_STATUS)0xAA00)
#define C_MOVE_FAILURE_UNABLE_TO_CREATE_NEW_OBJECT    ((RESP_STATUS)0xAA01)
#define C_MOVE_FAILURE_UNABLE_TO_EXTRACT_FRAMES       ((RESP_STATUS)0xAA02)
#define C_MOVE_FAILURE_INVALID_TIME_BASED_REQUEST     ((RESP_STATUS)0xAA03)
#define C_MOVE_FAILURE_INVALID_REQUEST                ((RESP_STATUS)0xAA04)

/* CANCEL code */
#define C_MOVE_CANCEL_REQUEST_RECEIVED          ((RESP_STATUS)0xFE00)


/* ======================================================================== *
 *               Query/Retrieve Service Class: C_GET_RSP Codes              *
 * ======================================================================== */
/* SUCCESS code */
#define C_GET_SUCCESS_NO_FAILURES_OR_WARNINGS   ((RESP_STATUS)0x0000)

/* WARNING code */
#define C_GET_WARNING_SOME_FAILURES_WARNINGS    ((RESP_STATUS)0xB000)

/* PENDING code */
#define C_GET_PENDING_MORE_SUB_OPERATIONS       ((RESP_STATUS)0xFF00)

/* FAILURE codes */
#define C_GET_FAILURE_REFUSED_CANT_CALC_MATCHES ((RESP_STATUS)0xA701)
#define C_GET_FAILURE_REFUSED_CANT_PERFORM      ((RESP_STATUS)0xA702)
#define C_GET_FAILURE_INVALID_DATASET           ((RESP_STATUS)0xA900)
#define C_GET_FAILURE_UNABLE_TO_PROCESS         ((RESP_STATUS)0xC001)

/* FAILURE codes for Instance Root Retrieve */
#define C_GET_FAILURE_NONE_OF_THE_FRAMES_FOUND       ((RESP_STATUS)0xAA00)
#define C_GET_FAILURE_UNABLE_TO_CREATE_NEW_OBJECT    ((RESP_STATUS)0xAA01)
#define C_GET_FAILURE_UNABLE_TO_EXTRACT_FRAMES       ((RESP_STATUS)0xAA02)
#define C_GET_FAILURE_INVALID_TIME_BASED_REQUEST     ((RESP_STATUS)0xAA03)
#define C_GET_FAILURE_INVALID_REQUEST                ((RESP_STATUS)0xAA04)

/* CANCEL code */
#define C_GET_CANCEL_REQUEST_RECEIVED               ((RESP_STATUS)0xFE00)


/* ======================================================================== *
 *                      N_EVENT_REPORT_RSP Response Codes                   *
 * ======================================================================== */
/* SUCCESS code */
#define N_EVENT_SUCCESS                             ((RESP_STATUS)0x0000)

/* FAILURE codes */
#define N_EVENT_CLASS_INSTANCE_CONFLICT             ((RESP_STATUS)0x0119)
#define N_EVENT_DUPLICATE_INVOCATION                ((RESP_STATUS)0x0210)
#define N_EVENT_INVALID_ARGUMENT_VALUE              ((RESP_STATUS)0x0115)
#define N_EVENT_MISTYPED_ARGUMENT                   ((RESP_STATUS)0x0212)
#define N_EVENT_NO_SUCH_ARGUMENT                    ((RESP_STATUS)0x0114)
#define N_EVENT_NO_SUCH_EVENT_TYPE                  ((RESP_STATUS)0x0113)
#define N_EVENT_NO_SUCH_SOP_CLASS                   ((RESP_STATUS)0x0118)
#define N_EVENT_NO_SUCH_SOP_INSTANCE                ((RESP_STATUS)0x0112)
#define N_EVENT_PROCESSING_FAILURE                  ((RESP_STATUS)0x0110)
#define N_EVENT_RESOURCE_LIMITATION                 ((RESP_STATUS)0x0213)
#define N_EVENT_UNRECOGNIZED_OPERATION              ((RESP_STATUS)0x0211)
#define N_EVENT_REFERENCED_SOP_CLASS_NOT_SUPPORTED  ((RESP_STATUS)0x0122)
#define N_EVENT_DUPLICATE_TRANSACTION_UID           ((RESP_STATUS)0x0131)


/* ======================================================================== *
 *                          N_GET_RSP Response Codes                        *
 * ======================================================================== */
/* SUCCESS code */
#define N_GET_SUCCESS                               ((RESP_STATUS)0x0000)

/* WARNING codes */
#define N_GET_WARNING_OPT_ATTRIB_UNSUPPORTED        ((RESP_STATUS)0x0001)
#define N_GET_ATTRIBUTE_LIST_ERROR                  ((RESP_STATUS)0x0107)

/* FAILURE codes */
#define N_GET_CLASS_INSTANCE_CONFLICT               ((RESP_STATUS)0x0119)
#define N_GET_DUPLICATE_INVOCATION                  ((RESP_STATUS)0x0210)
#define N_GET_MISTYPED_ARGUMENT                     ((RESP_STATUS)0x0212)
#define N_GET_NO_SUCH_SOP_CLASS                     ((RESP_STATUS)0x0118)
#define N_GET_NO_SUCH_SOP_INSTANCE                  ((RESP_STATUS)0x0112)
#define N_GET_PROCESSING_FAILURE                    ((RESP_STATUS)0x0110)
#define N_GET_RESOURCE_LIMITATION                   ((RESP_STATUS)0x0213)
#define N_GET_UNRECOGNIZED_OPERATION                ((RESP_STATUS)0x0211)
#define N_GET_REFERENCED_SOP_CLASS_NOT_SUPPORTED    ((RESP_STATUS)0x0122)
#define N_GET_DUPLICATE_TRANSACTION_UID             ((RESP_STATUS)0x0131)

/* ======================================================================== *
 *                          N_SET_RSP Response Codes                        *
 * ======================================================================== */
/* SUCCESS code */
#define N_SET_SUCCESS                               ((RESP_STATUS)0x0000)

/* WARNING codes */
#define N_SET_REQUESTED_MIN_OR_MAX_DENSITY_OUTSIDE_RANGE    ((RESP_STATUS)0xB605)
#define N_SET_ATTRIBUTE_VALUE_OUT_OF_RANGE                  ((RESP_STATUS)0x0116)
#define N_SET_ATTRIBUTE_LIST_ERROR                          ((RESP_STATUS)0x0107)

/* FAILURE codes */
#define N_SET_CLASS_INSTANCE_CONFLICT               ((RESP_STATUS)0x0119)
#define N_SET_DUPLICATE_INVOCATION                  ((RESP_STATUS)0x0210)
#define N_SET_INVALID_ATTRIBUTE_VALUE               ((RESP_STATUS)0x0106)
#define N_SET_MISTYPED_ARGUMENT                     ((RESP_STATUS)0x0212)
#define N_SET_INVALID_OBJECT_INSTANCE               ((RESP_STATUS)0x0117)
#define N_SET_MISSING_ATTRIBUTE_VALUE               ((RESP_STATUS)0x0121)
#define N_SET_NO_SUCH_ATTRIBUTE                     ((RESP_STATUS)0x0105)
#define N_SET_NO_SUCH_SOP_CLASS                     ((RESP_STATUS)0x0118)
#define N_SET_NO_SUCH_SOP_INSTANCE                  ((RESP_STATUS)0x0112)
#define N_SET_PROCESSING_FAILURE                    ((RESP_STATUS)0x0110)
#define N_SET_RESOURCE_LIMITATION                   ((RESP_STATUS)0x0213)
#define N_SET_UNRECOGNIZED_OPERATION                ((RESP_STATUS)0x0211)
#define N_SET_REFERENCED_SOP_CLASS_NOT_SUPPORTED    ((RESP_STATUS)0x0122)
#define N_SET_DUPLICATE_TRANSACTION_UID             ((RESP_STATUS)0x0131)


/* Print Management Service Classes WARNING codes*/
#define N_SET_WARNING_IMAGE_CROPPED_TO_FIT      ((RESP_STATUS)0xB609)
#define N_SET_WARNING_IMAGE_DECIMATED_TO_FIT    ((RESP_STATUS)0xB60A)

/* Print Management Service Classes FAILURE codes*/
#define N_SET_INSUFFICIENT_PRINTER_MEMORY       ((RESP_STATUS)0xC605)
#define N_SET_MORE_THAN_ONE_VOID_LUT_BOX        ((RESP_STATUS)0xC606)
#define N_SET_FAILURE_IMAGE_LARGER_THAN_BOX     ((RESP_STATUS)0xC603)
#define N_SET_FAILURE_COMBINED_LARGER_THAN_BOX  ((RESP_STATUS)0xC613)

/* Modality Performed Procedure Step FAILURE codes*/
#define N_SET_OBJECT_MAY_NO_LONGER_BE_UPDATED   ((RESP_STATUS)0x0110)

/* Modify GP Performed Procedure Step REFUSED codes */
#define N_SET_REFUSED_PPS_NOT_IN_PROGRESS            ((RESP_STATUS)0xA506)


/* ======================================================================== *
 *                        N_ACTION_RSP Response Codes                       *
 * ======================================================================== */
/* SUCCESS code */
#define N_ACTION_SUCCESS                            ((RESP_STATUS)0x0000)

/* FAILURE codes */
#define N_ACTION_CLASS_INSTANCE_CONFLICT            ((RESP_STATUS)0x0119)
#define N_ACTION_DUPLICATE_INVOCATION               ((RESP_STATUS)0x0210)
#define N_ACTION_INVALID_ARGUMENT_VALUE             ((RESP_STATUS)0x0115)
#define N_ACTION_MISTYPED_ARGUMENT                  ((RESP_STATUS)0x0212)
#define N_ACTION_NO_SUCH_ARGUMENT                   ((RESP_STATUS)0x0114)
#define N_ACTION_NO_SUCH_SOP_CLASS                  ((RESP_STATUS)0x0118)
#define N_ACTION_NO_SUCH_SOP_INSTANCE               ((RESP_STATUS)0x0112)
#define N_ACTION_PROCESSING_FAILURE                 ((RESP_STATUS)0x0110)
#define N_ACTION_RESOURCE_LIMITATION                ((RESP_STATUS)0x0213)
#define N_ACTION_UNRECOGNIZED_OPERATION             ((RESP_STATUS)0x0211)
#define N_ACTION_NO_SUCH_ACTION_TYPE                ((RESP_STATUS)0x0123)
#define N_ACTION_REFERENCED_SOP_CLASS_NOT_SUPPORTED ((RESP_STATUS)0x0122)
#define N_ACTION_DUPLICATE_TRANSACTION_UID          ((RESP_STATUS)0x0131)

/* Print Management Service Classes WARNING codes */
#define N_ACTION_WARNING_NO_COLLATION_SUPPORT   ((RESP_STATUS)0xB601)
#define N_ACTION_WARNING_SESSION_EMPTY_PAGE     ((RESP_STATUS)0xB602)
#define N_ACTION_WARNING_BOX_EMPTY_PAGE         ((RESP_STATUS)0xB603)
#define N_ACTION_WARNING_IMAGE_CROPPED_TO_FIT   ((RESP_STATUS)0xB609)
#define N_ACTION_WARNING_IMAGE_DECIMATED_TO_FIT ((RESP_STATUS)0xB60A)

/* Print Management Service Classes FAILURE codes */
#define N_ACTION_FAILURE_NO_FILM_SOP_INSTANCES  ((RESP_STATUS)0xC600)
#define N_ACTION_FAILURE_SESSION_PRINT_Q_FULL   ((RESP_STATUS)0xC601)
#define N_ACTION_FAILURE_BOX_PRINT_Q_FULL       ((RESP_STATUS)0xC602)
#define N_ACTION_FAILURE_SIZE_LARGER_THAN_BOX   ((RESP_STATUS)0xC603)
#define N_ACTION_FAILURE_IMAGE_POS_COLLISION    ((RESP_STATUS)0xC604)
#define N_ACTION_FAILURE_COMBINED_SIZE_LARGER_THAN_BOX ((RESP_STATUS)0xC613)

/* Print Queue Management Service Classes FAILURE codes */
#define N_ACTION_FAILURE_PRINT_QUEUE_IS_HALTED  ((RESP_STATUS)0xC651)
#define N_ACTION_FAILURE_MISMATCH_OF_OWNER_IDS  ((RESP_STATUS)0xC652)
#define N_ACTION_FAILURE_JOB_IN_PROCESS         ((RESP_STATUS)0xC653)

/* Pull Print Request WARNING codes */
#define N_ACTION_MEMORY_ALLOCATION_NOT_SUPP     ((RESP_STATUS)0xB600)
#define N_ACTION_WARNING_ANNOTATION_NOT_SUPP    ((RESP_STATUS)0xB604)
#define N_ACTION_WARNING_IMAGE_OVERLAY_NOT_SUPP ((RESP_STATUS)0xB605)
#define N_ACTION_WARNING_PRES_LUT_NOT_SUPP      ((RESP_STATUS)0xB606)
#define N_ACTION_WARNING_IMAGE_BOX_LUT_NOT_SUPP ((RESP_STATUS)0xB608)

/* Pull Print Request FAILURE codes */
#define N_ACTION_FAILURE_INSUFFICIENT_MEMORY    ((RESP_STATUS)0xC605)
#define N_ACTION_FAILURE_NO_STORED_PRINT_AT_AE  ((RESP_STATUS)0xC607)
#define N_ACTION_FAILURE_NO_IMAGE_AT_AE         ((RESP_STATUS)0xC608)
#define N_ACTION_FAILURE_RETRIEVING_STORED_PRINT ((RESP_STATUS)0xC609)
#define N_ACTION_FAILURE_RETRIEVING_IMAGE       ((RESP_STATUS)0xC60A)
#define N_ACTION_FAILURE_UNKNOWN_RETREIVE_AE    ((RESP_STATUS)0xC60B)
/* misspelled code above corrected */
#define N_ACTION_FAILURE_UNKNOWN_RETRIEVE_AE    ((RESP_STATUS)0xC60B)
#define N_ACTION_FAILURE_PRINTER_CANNOT_ACCEPT_COLOR ((RESP_STATUS)0xC60C)
#define N_ACTION_FAILURE_EMPTY_PAGE             ((RESP_STATUS)0xC60D)
#define N_ACTION_FAILURE_ANNOTATION_NOT_SUPP    ((RESP_STATUS)0xC60E)
#define N_ACTION_FAILURE_IMAGE_OVERLAY_NOT_SUPP ((RESP_STATUS)0xC60F)
#define N_ACTION_FAILURE_PRES_LUT_NOT_SUPP      ((RESP_STATUS)0xC610)
#define N_ACTION_FAILURE_IMAGE_BOX_LUT_NOT_SUPP ((RESP_STATUS)0xC614)
#define N_ACTION_FAILURE_UNABLE_TO_OPEN_ASSOC   ((RESP_STATUS)0xC615)

/* Modify GP Scheduled Procedure Step REFUSED codes */
#define N_ACTION_REFUSED_MAY_NO_LONGER_BE_UPDATED    ((RESP_STATUS)0xA501)
#define N_ACTION_REFUSED_WRONG_TRANSACTION_ID        ((RESP_STATUS)0xA502)
#define N_ACTION_REFUSED_ALREADY_IN_PROGRESS         ((RESP_STATUS)0xA503)

/* Media Creation Management FAILURE codes */
#define N_ACTION_MEDIA_CREATION_RQ_COMPLETED    ((RESP_STATUS)0xC201)
#define N_ACTION_MEDIA_CREATION_RQ_IN_PROGRESS  ((RESP_STATUS)0xC202)
#define N_ACTION_CANCELLATION_DENIED            ((RESP_STATUS)0xC203)

/* Substance Administration Information Services FAILURE codes */
#define N_ACTION_OPERATOR_NOT_AUTHORIZED        ((RESP_STATUS)0xC10E)
#define N_ACTION_PATIENT_CANNOT_BE_IDENTIFIED   ((RESP_STATUS)0xC110)
#define N_ACTION_UPDATE_OF_MAR_FAILED           ((RESP_STATUS)0xC111)


/* ======================================================================== *
 *                        N_CREATE_RSP Response Codes                       *
 * ======================================================================== */
/* SUCCESS code */
#define N_CREATE_SUCCESS                            ((RESP_STATUS)0x0000)

/* FAILURE codes */
#define N_CREATE_CLASS_INSTANCE_CONFLICT            ((RESP_STATUS)0x0119)
#define N_CREATE_DUPLICATE_INVOCATION               ((RESP_STATUS)0x0210)
#define N_CREATE_DUPLICATE_SOP_INSTANCE             ((RESP_STATUS)0x0111)
#define N_CREATE_INVALID_ATTRIBUTE_VALUE            ((RESP_STATUS)0x0106)
#define N_CREATE_MISSING_ATTRIBUTE                  ((RESP_STATUS)0x0120)
#define N_CREATE_MISSING_ATTRIBUTE_VALUE            ((RESP_STATUS)0x0121)
#define N_CREATE_MISTYPED_ARGUMENT                  ((RESP_STATUS)0x0212)
#define N_CREATE_NO_SUCH_ATTRIBUTE                  ((RESP_STATUS)0x0105)
#define N_CREATE_NO_SUCH_SOP_CLASS                  ((RESP_STATUS)0x0118)
#define N_CREATE_NO_SUCH_SOP_INSTANCE               ((RESP_STATUS)0x0112)
#define N_CREATE_PROCESSING_FAILURE                 ((RESP_STATUS)0x0110)
#define N_CREATE_RESOURCE_LIMITATION                ((RESP_STATUS)0x0213)
#define N_CREATE_UNRECOGNIZED_OPERATION             ((RESP_STATUS)0x0211)
#define N_CREATE_REFERENCED_SOP_CLASS_NOT_SUPPORTED ((RESP_STATUS)0x0122)
#define N_CREATE_DUPLICATE_TRANSACTION_UID          ((RESP_STATUS)0x0131)

/* Print Management Service Classes FAILURE codes */
#define N_CREATE_NO_MEMORY_ALLOCATION_POSSIBLE  ((RESP_STATUS)0x0106)
#define N_CREATE_TEMPORARILY_NO_MEMORY          ((RESP_STATUS)0x0213)

/* Print Management Service Classes WARNING codes */
#define N_CREATE_MEMORY_ALLOCATION_NOT_SUPPORTED ((RESP_STATUS)0xB600)
#define N_CREATE_REQUESTED_MIN_OR_MAX_DENSITY_OUTSIDE_RANGE ((RESP_STATUS)0xB605)
#define N_CREATE_ATTRIBUTE_VALUE_OUT_OF_RANGE    ((RESP_STATUS)0x0116)
#define N_CREATE_ATTRIBUTE_LIST_ERROR            ((RESP_STATUS)0x0107)

/* Basic Print Image Overlay Box FAILURE codes */
#define N_CREATE_FAILURE_COMBINED_REQUIRES_CROPPING  ((RESP_STATUS)0xC616)

/* Modify GP Performed Procedure Step REFUSED codes */
#define N_CREATE_REFUSED_SPS_NOT_IN_PROGRESS         ((RESP_STATUS)0xA504)
#define N_CREATE_REFUSED_UNMATCHED_TRANSACTION_ID    ((RESP_STATUS)0xA505)

/* Media Creation FAILURE codes */
#define N_CREATE_FAILURE_MEDIA_CREATION_ALREADY_RCV  ((RESP_STATUS)0xA510)


/* ======================================================================== *
 *                        N_DELETE_RSP Response Codes                       *
 * ======================================================================== */
/* SUCCESS code */
#define N_DELETE_SUCCESS                            ((RESP_STATUS)0x0000)

/* FAILURE codes */
#define N_DELETE_CLASS_INSTANCE_CONFLICT            ((RESP_STATUS)0x0119)
#define N_DELETE_DUPLICATE_INVOCATION               ((RESP_STATUS)0x0210)
#define N_DELETE_MISTYPED_ARGUMENT                  ((RESP_STATUS)0x0212)
#define N_DELETE_NO_SUCH_SOP_CLASS                  ((RESP_STATUS)0x0118)
#define N_DELETE_NO_SUCH_SOP_INSTANCE               ((RESP_STATUS)0x0112)
#define N_DELETE_PROCESSING_FAILURE                 ((RESP_STATUS)0x0110)
#define N_DELETE_RESOURCE_LIMITATION                ((RESP_STATUS)0x0213)
#define N_DELETE_UNRECOGNIZED_OPERATION             ((RESP_STATUS)0x0211)
#define N_DELETE_REFERENCED_SOP_CLASS_NOT_SUPPORTED ((RESP_STATUS)0x0122)
#define N_DELETE_DUPLICATE_TRANSACTION_UID          ((RESP_STATUS)0x0131)

/* ======================================================================== *
 *          MergeCOM-3 Advanced Tool Kit Network-Related Functions          *
 * ======================================================================== */

EXP_PRE extern MC_STATUS EXP_FUNC MC_Abort_Association(int* AssociationID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Accept_Association(int AssociationID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Accept_Association_With_Identity(int AssociationID, void* AserverResponse, unsigned short AserverResponseLength);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Clear_Negotiation_Info(int ApplicationID, const char* Aservice);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Close_Association(int* AssociationID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Get_Association_Info(int AssociationID, AssocInfo* Ainfo);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Get_First_Acceptable_Service(int AsessionID, ServiceInfo* AservInfo);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Get_Next_Acceptable_Service(int AsessionID, ServiceInfo* AservInfo);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Set_Message_Transfer_Syntax(int AmsgID, TRANSFER_SYNTAX Asyntax);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Get_Message_Transfer_Syntax(int AmsgID, TRANSFER_SYNTAX* Asyntax);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Reset_Message_Transfer_Syntax(int AmsgID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Get_Listen_Socket(MC_SOCKET* AlistenSocket);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Get_Listen_Socket_For_Port(int Aport, MC_SOCKET* AlistenSocket);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Get_Negotiation_Info(int AssociationID, const char* ServiceName, void** ExtInfoBuffer, int* ExtInfoLength);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Get_Meta_ServiceName(int AsessionID, char* AservBuf, int AservBufSize);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Get_User_Identity_Info(int AsessionID, USER_IDENTITY_FIELD_TYPE AfieldType, void* Afield, unsigned short AfieldLength);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Get_User_Identity_Length(int AsessionID, USER_IDENTITY_FIELD_TYPE AfieldType, unsigned short* AfieldLength);

EXP_PRE extern MC_STATUS EXP_FUNC MC_Open_Association(  int         ApplicationID,
                                                        int*        AssociationID,
                                                        const char* RemoteApplicationTitle,
                                                        int*        RemoteHostPortNumber,
                                                        char*       RemoteHostTCPIPName,
                                                        char*       ServiceList );

EXP_PRE extern MC_STATUS EXP_FUNC MC_Open_Secure_Association(   int                     ApplicationID,
                                                                int*                    AssociationID,
                                                                const char*             RemoteApplicationTitle,
                                                                int*                    RemoteHostPortNumber,
                                                                char*                   RemoteHostTCPIPName,
                                                                char*                   ServiceList,
                                                                SecureSocketFunctions*  SS_functions,
                                                                void*                   SS_application_context  );

EXP_PRE extern MC_STATUS EXP_FUNC MC_Open_Association_With_Identity(int                     ApplicationID,
                                                                    int*                    AsessionID,
                                                                    const char*             AremoteAppTitle,
                                                                    int*                    AremotePortNumber,
                                                                    char*                   AremoteHostName,
                                                                    char*                   AserviceListName,
                                                                    SecureSocketFunctions*  SS_functions,
                                                                    void*                   SS_application_context,
                                                                    USER_IDENTITY_TYPE      AidentityType,
                                                                    unsigned char           AresponseRequested,
                                                                    void*                   AprimaryField,
                                                                    unsigned short          AprimaryFieldLength,
                                                                    void*                   AsecondaryField,
                                                                    unsigned short          AsecondaryFieldLength);

/* ======================================================================== *
 *          MergeCOM-3 Advanced Tool Kit Compressor Decompressor Functions  *
 * ======================================================================== */

EXP_PRE extern MC_STATUS EXP_FUNC MC_RLE_Compressor(    int            AmsgID,
                                                        void**         Context,
                                                        unsigned long  AinputLength,
                                                        void*          AinputBuffer,
                                                        unsigned long* AoutputLength,
                                                        void**         AoutputBuffer,
                                                        int            AisFirst,
                                                        int            AisLast,
                                                        int            Arelease );

EXP_PRE extern MC_STATUS EXP_FUNC MC_RLE_Decompressor(  int            AmsgID,
                                                        void**         Context,
                                                        unsigned long  AinputLength,
                                                        void*          AinputBuffer,
                                                        unsigned long* AoutputLength,
                                                        void**         AoutputBuffer,
                                                        int            AisFirst,
                                                        int            AisLast,
                                                        int            Arelease );

EXP_PRE extern MC_STATUS EXP_FUNC MC_Standard_Compressor(   int            AmsgID,
                                                            void**         Context,
                                                            unsigned long  AinputLength,
                                                            void*          AinputBuffer,
                                                            unsigned long* AoutputLength,
                                                            void**         AoutputBuffer,
                                                            int            AisFirst,
                                                            int            AisLast,
                                                            int            Arelease );

EXP_PRE extern MC_STATUS EXP_FUNC MC_Standard_Decompressor( int            AmsgID,
                                                            void**         Context,
                                                            unsigned long  AinputLength,
                                                            void*          AinputBuffer,
                                                            unsigned long* AoutputLength,
                                                            void**         AoutputBuffer,
                                                            int            AisFirst,
                                                            int            AisLast,
                                                            int            Arelease );

/* ======================================================================== *
 *          MergeCOM-3 Advanced Tool Kit Application Functions   *
 * ======================================================================== */

EXP_PRE extern MC_STATUS EXP_FUNC MC_Register_Application(int* ApplicationID, const char* ApplicationTitle);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Reject_Association(int AssociationID, REJECT_REASON Areason);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Release_Application(int* ApplicationID);

/* ======================================================================== *
 *          MergeCOM-3 Advanced Tool Kit Network Reading Functions          *
 * ======================================================================== */

EXP_PRE extern MC_STATUS EXP_FUNC MC_Read_Message(int AssociationID, int Timeout, int* MessageID, char** ServiceName, MC_COMMAND* Command);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Read_Message_To_Tag( int AssociationID, int Timeout, unsigned long AstopTag, int* MessageID, char** ServiceName, MC_COMMAND* Command );
EXP_PRE extern MC_STATUS EXP_FUNC MC_Continue_Read_Message( int AssociationID, /*int Timeout,*/ int* MessageID/*, char** ServiceName, MC_COMMAND* Command*/ );
EXP_PRE extern MC_STATUS EXP_FUNC MC_Continue_Read_Message_To_Tag(int AssociationID, /*int Timeout,*/ unsigned long AstopTag, int* MessageID/*, char** ServiceName, MC_COMMAND* Command*/);

EXP_PRE extern MC_STATUS EXP_FUNC MC_Continue_Read_Message_To_Stream(int    AsessionID,
                                                                     int*   AmsgID,
                                                                     void*  AuserInfo,
                                                                     MC_STATUS (NOEXP_FUNC *AuserFunction)
                                                                     (int       CBmsgID,
                                                                      void*     CBuserInfo,
                                                                      int       CBdataSize,
                                                                      void*     CBdataBuffer,
                                                                      int       CBisFirst,
                                                                      int       CBisLast));

EXP_PRE extern MC_STATUS EXP_FUNC MC_Read_To_Stream(int               AssociationID,
                                                    int               Timeout,
                                                    char**            AserviceName,
                                                    MC_COMMAND*       Acommand,
                                                    char*             Afilename,
                                                    void*             AuserInfo,
                                                    MC_STATUS    (NOEXP_FUNC *AuserFunction)
                                                                 (int   CBmsgID,
                                                                  void* CBuserInfo,
                                                                  int   CBdataSize,
                                                                  void* CBdataBuffer,
                                                                  int   CBisFirst,
                                                                  int   CBisLast));

/* ======================================================================== *
 *          MergeCOM-3 Advanced Tool Kit Network Sending Functions          *
 * ======================================================================== */

EXP_PRE extern MC_STATUS EXP_FUNC MC_Send_Request_Message(int AsessionID, int MessageID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Send_Request_Message_For_Service(int AsessionID, int AmessageID, char* AserviceName);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Send_Response_Message(int AsessionID, RESP_STATUS ResponseStatus, int ResponseMessageID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_Send_Request(int AsessionID, char* Afilename, void* AuserInfo,
                                                  MC_STATUS    (NOEXP_FUNC*    AuserFunction)
                                                               (int            CBmsgID,
                                                                unsigned long  CBtag,
                                                                void*          CBuserInfo,
                                                                CALLBACK_TYPE  CBtype,
                                                                unsigned long* CBdataSize,
                                                                void**         CBdataBuffer,
                                                                int            CBisFirst,
                                                                int*           CBisLast));

EXP_PRE extern MC_STATUS EXP_FUNC MC_Send_Request_For_Service(  int AsessionID, char* AserviceName, char* Afilename, void* AuserInfo,
                                                                MC_STATUS    (NOEXP_FUNC*    AuserFunction)
                                                                                (int            CBmsgID,
                                                                                unsigned long  CBtag,
                                                                                void*          CBuserInfo,
                                                                                CALLBACK_TYPE  CBtype,
                                                                                unsigned long* CBdataSize,
                                                                                void**         CBdataBuffer,
                                                                                int            CBisFirst,
                                                                                int*           CBisLast));

EXP_PRE extern MC_STATUS EXP_FUNC MC_Send_Response(int AsessionID, RESP_STATUS ResponseStatus, char* Afilename, void* AuserInfo,
                                                   MC_STATUS    (NOEXP_FUNC*    AuserFunction)
                                                                (int            CBmsgID,
                                                                 unsigned long  CBtag,
                                                                 void*          CBuserInfo,
                                                                 CALLBACK_TYPE  CBtype,
                                                                 unsigned long* CBdataSize,
                                                                 void**         CBdataBuffer,
                                                                 int            CBisFirst,
                                                                 int*           CBisLast));

EXP_PRE extern MC_STATUS EXP_FUNC MC_Set_Negotiation_Info(int ApplicationID, const char* ServiceName, void* ExtInfoBuffer, int ExtInfoLength);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Set_Negotiation_Info_For_Association(int AssociationID, const char* ServiceName, void* ExtInfoBuffer, int ExtInfoLength);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Wait_For_Connection(int Timeout, MC_SOCKET* Socket);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Wait_For_Connection_On_Port(int Timeout, int Port, MC_SOCKET* Socket);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Wait_For_Connection_On_Address(int Timeout, int Port, const char* Address, MC_SOCKET* Socket);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Wait_For_Association(const char* ServiceList, int Timeout, int* ApplicationID, int* AssociationID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Wait_For_Association_On_Port(const char* AserviceListName, int Atimeout, int ApplicationID, int Aport, int* AsessionID) ;
EXP_PRE extern MC_STATUS EXP_FUNC MC_Wait_For_Association_On_Address( const char* AserviceListName, int Atimeout, int ApplicationID, int Aport, const char* Address, int* AsessionID );

EXP_PRE extern MC_STATUS EXP_FUNC MC_Wait_For_Secure_Association( const char*             ServiceList,
                                                                  int                     Timeout,
                                                                  int*                    ApplicationID,
                                                                  int*                    AssociationID,
                                                                  SecureSocketFunctions*  SS_functions,
                                                                  void*                   SS_application_context);

EXP_PRE extern MC_STATUS EXP_FUNC MC_Wait_For_Secure_Association_On_Port( const char*            AserviceListName,
                                                                          int                    Atimeout,
                                                                          int                    ApplicationID,
                                                                          int                    Aport,
                                                                          int*                   AsessionID,
                                                                          SecureSocketFunctions* SS_functions,
                                                                          void*                  SS_application_context);

EXP_PRE extern MC_STATUS EXP_FUNC MC_Wait_For_Secure_Association_On_Address(const char*            AserviceListName,
                                                                            int                    Atimeout,
                                                                            int                    ApplicationID,
                                                                            int                    Aport,
                                                                            const char*            Address,
                                                                            int*                   AsessionID,
                                                                            SecureSocketFunctions* SS_functions,
                                                                            void*                  SS_application_context);


EXP_PRE extern MC_STATUS EXP_FUNC MC_Process_Secure_Association_Request( MC_SOCKET              Asocket,
                                                                         const char*            AserviceListName,
                                                                         int*                   ApplicationID,
                                                                         int*                   AsessionID,
                                                                         SecureSocketFunctions* SS_functions,
                                                                         void*                  SS_application_context );

EXP_PRE extern MC_STATUS EXP_FUNC MC_Process_Association_Request( MC_SOCKET Asocket, const char* AserviceListName, int* ApplicationID, int* AsessionID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Close_Listen_Port(int Aport);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Close_Listen_Port_On_Address(int Aport, const char* Address);

/* The following function available only a operating systems supporting child processes */
EXP_PRE extern MC_STATUS MC_Release_Parent_Association(int* AsessionID);

/* The following function available only a operating systems supporting child processes */
EXP_PRE extern void MC_Release_Parent_Connection(MC_SOCKET Asocket);

/* The following function registers functions to be used to capture network traffic */
EXP_PRE extern MC_STATUS MC_Register_Network_Capture_Callbacks(MC_NetworkCaptureInfo *AcallbackInfo);

/* The following support the dynamic generation of service lists */
EXP_PRE extern MC_STATUS EXP_FUNC MC_NewSyntaxList(char* A_name, TRANSFER_SYNTAX A_syntax_ids[]);
EXP_PRE extern MC_STATUS EXP_FUNC MC_NewServiceFromName(char* AserviceName, char* ASOPClassName, char* ASyntaxListName, int ASCURole, int ASCPRole);

EXP_PRE extern MC_STATUS EXP_FUNC MC_NewServiceWithExtInfoFromName( char*   AserviceName,
                                                                    char*   ASOPClassUID,
                                                                    char*   ASyntaxListName,
                                                                    int     ASCURole,
                                                                    int     ASCPRole,
                                                                    void*   AExtInfoBuffer,
                                                                    int     AExtInfoBufferLength);

EXP_PRE extern MC_STATUS EXP_FUNC MC_NewServiceFromUID( char* AserviceName, char* ASOPClassUID, char* ASyntaxListName, int ASCURole, int ASCPRole);

EXP_PRE extern MC_STATUS EXP_FUNC MC_NewServiceWithExtInfoFromUID(  char*   AserviceName,
                                                                    char*   ASOPClassUID,
                                                                    char*   ASyntaxListName,
                                                                    int     ASCURole,
                                                                    int     ASCPRole,
                                                                    void*   AExtInfoBuffer,
                                                                    int     AExtInfoBufferLength);

EXP_PRE extern MC_STATUS EXP_FUNC MC_NewProposedServiceList(char* ServiceListName, char* ServiceNameArray[]);
EXP_PRE extern MC_STATUS EXP_FUNC MC_NewProposedServiceListAsync(char* ServiceListName, char* ServiceNameArray[], unsigned short MaxOperationsInvoked, unsigned short MaxOperationsPerformed);
EXP_PRE extern MC_STATUS EXP_FUNC MC_FreeServiceList(char* AServiceList);
EXP_PRE extern MC_STATUS EXP_FUNC MC_FreeService(char* AServiceName);
EXP_PRE extern MC_STATUS EXP_FUNC MC_FreeSyntaxList(char* ASyntaxList);

/* ======================================================================== *
 *          MergeCOM-3 Advanced Tool Kit   memory cleanup                   *
 * ======================================================================== */

EXP_PRE extern MC_STATUS EXP_FUNC MC_Cleanup_Memory( int Asec );
EXP_PRE extern MC_STATUS EXP_FUNC MC_Report_Memory( MC_ul_size_t* bytesAllocated, MC_ul_size_t* bytesNotFreeable );
EXP_PRE extern MC_STATUS EXP_FUNC MC_Report_Memory_Ex( MC_ul_size_t* bytesAllocated, MC_ul_size_t* bytesNotFreeable, MC_ul_size_t* bytesInUse );

#ifdef __BORLANDC__
#pragma option -b.
#endif

#ifdef _MACINTOSH
#pragma enumsalwaysint reset
#pragma options align=reset
#endif

#ifdef __cplusplus
}
#endif

#endif

