/*************************************************************************
 *
 *       System: MergeCOM-3 - Advanced Integrator's Tool Kit
 *
 *    $Workfile: mcstatus.h $
 *
 *    $Revision: 12 $
 *
 *        $Date: 2/18/01 11:53p $
 *
 *  Description:   This module contains the definitions of status code 
 *                 returned by MergeCOM-3 functions.
 *
 *************************************************************************
 *
 *		             (c) 2002-2005 Merge Healthcare
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
/* $Nokeywords$ */


#ifndef MTI_MCSTATUS_H
#define MTI_MCSTATUS_H


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
 *                    MC3MSG Service Return Status values                   *
 * ======================================================================== */
typedef enum {
    MC_NORMAL_COMPLETION        = 1,
        
    MC_ALREADY_REGISTERED       = 4000,  /* NEVER CHANGE */
    MC_ASSOCIATION_ABORTED,
    MC_ASSOCIATION_CLOSED,
    MC_ASSOCIATION_REJECTED,
    MC_ATTRIBUTE_HAS_VALUES,
    MC_BUFFER_TOO_SMALL,
    MC_CALLBACK_CANNOT_COMPLY,
    MC_CALLBACK_DATA_SIZE_NEGATIVE,
    MC_CALLBACK_DATA_SIZE_UNEVEN,
    MC_CALLBACK_PARM_ERROR,
    MC_CALLBACK_REGISTERED,
    MC_CANNOT_COMPLY,
    MC_CANT_ACCESS_PROFILE,
    MC_CONFIG_INFO_ERROR,
    MC_CONFIG_INFO_MISSING,
    MC_DDFILE_ERROR,
    MC_DOES_NOT_VALIDATE,
    MC_EMPTY_VALUE,
    MC_END_OF_DATA,
    MC_EXT_INFO_UNAVAILABLE,
    MC_FOUND,
    MC_FUNCTION_UNAVAILABLE,
    MC_INCOMPATIBLE_VR,        
    MC_INCOMPATIBLE_VALUE,
    MC_INVALID_APPLICATION_ID,
    MC_INVALID_APPLICATION_TITLE,
    MC_INVALID_ASSOC_ID,
    MC_INVALID_CHARS_IN_VALUE,        
    MC_INVALID_COMMAND,
    MC_INVALID_DATA_TYPE,
    MC_END_OF_LIST,
    MC_INVALID_GROUP,
    MC_INVALID_HOST_NAME,
    MC_INVALID_ITEM_ID,
    MC_INVALID_LENGTH_FOR_TITLE,
    MC_INVALID_LENGTH_FOR_VR,
    MC_INVALID_LICENSE,
    MC_INVALID_MESSAGE_ID,
    MC_INVALID_MESSAGE_RECEIVED,
    MC_INVALID_PARAMETER_NAME,
    MC_INVALID_PORT_NUMBER,
    MC_INVALID_PRIVATE_CODE,
    MC_INVALID_SERVICE_LIST_NAME,
    MC_INVALID_TAG,
    MC_INVALID_TRANSFER_SYNTAX,
    MC_INVALID_VALUE_FOR_VR,
    MC_INVALID_VALUE_NUMBER,
    MC_INVALID_VR_CODE,
    MC_LOG_EMPTY,
    MC_MESSAGE_EMPTY,
    MC_MESSAGE_VALIDATES,
    MC_MISSING_CONFIG_PARM,
    MC_MSGFILE_ERROR,
    MC_MUST_BE_POSITIVE,
    MC_NETWORK_SHUT_DOWN,
    MC_NO_APPLICATIONS_REGISTERED,
    MC_NO_CALLBACK,
    MC_NO_CONDITION_FUNCTION,
    MC_NO_FILE_SYSTEM,
    MC_NO_INFO_REGISTERED,
    MC_NO_LICENSE,
    MC_NO_MERGE_INI,
    MC_NO_MORE_ATTRIBUTES,
    MC_NO_MORE_VALUES,
    MC_NO_PROFILE,
    MC_NO_REQUEST_PENDING,
    MC_NON_SERVICE_ATTRIBUTE,
    MC_NOT_FOUND,
    MC_NOT_ONE_OF_ENUMERATED_VALUES,
    MC_NOT_ONE_OF_DEFINED_TERMS,
    MC_NULL_POINTER_PARM,
    MC_NULL_VALUE,
    MC_PROTOCOL_ERROR,
    MC_REQUIRED_ATTRIBUTE_MISSING,
    MC_REQUIRED_DATASET_MISSING,
    MC_REQUIRED_VALUE_MISSING,
    MC_STATE_VIOLATION,
    MC_SYSTEM_CALL_INTERRUPTED,
    MC_SYSTEM_ERROR,
    MC_TAG_ALREADY_EXISTS,
    MC_TEMP_FILE_ERROR,
    MC_TIMEOUT,
    MC_TOO_FEW_VALUES,
    MC_TOO_MANY_BLOCKS,
    MC_TOO_MANY_VALUES,
    MC_UNABLE_TO_CHECK_CONDITION,
    MC_UNACCEPTABLE_SERVICE,
    MC_UNEXPECTED_EOD,
    MC_UNKNOWN_ITEM,
    MC_UNKNOWN_SERVICE,
    MC_VALUE_MAY_NOT_BE_NULL,
    MC_VALUE_NOT_ALLOWED,
    MC_VALUE_OUT_OF_RANGE,
    MC_VALUE_TOO_LARGE,
    MC_VR_ALREADY_VALID,
    MC_LIBRARY_ALREADY_INITIALIZED, 
    MC_LIBRARY_NOT_INITIALIZED,
    MC_INVALID_DIRECTORY_RECORD_OFFSET,
    MC_INVALID_FILE_ID, 
    MC_INVALID_DICOMDIR_ID, 
    MC_INVALID_ENTITY_ID,
    MC_INVALID_MRDR_ID,
    MC_UNABLE_TO_GET_ITEM_ID,
    MC_INVALID_PAD,
    MC_ENTITY_ALREADY_EXISTS,
    MC_INVALID_LOWER_DIR_RECORD,
    MC_BAD_DIR_RECORD_TYPE,
    MC_UNKNOWN_HOST_CONNECTED,
    MC_INACTIVITY_TIMEOUT,
    MC_INVALID_SOP_CLASS_UID,
    MC_INVALID_VERSION,
    MC_OUT_OF_ORDER_TAG,
    MC_CONNECTION_FAILED,
    MC_UNKNOWN_HOST_NAME,
    MC_INVALID_FILE,
    MC_NEGOTIATION_ABORTED,
    MC_INVALID_SR_ID,
    MC_UNABLE_TO_GET_SR_ID,
    MC_DUPLICATE_NAME,
    MC_DUPLICATE_SYNTAX,
    MC_EMPTY_LIST,
    MC_MISSING_NAME,
    MC_INVALID_SERVICE_NAME,
    MC_SERVICE_IN_USE,
    MC_INVALID_SYNTAX_NAME,
    MC_SYNTAX_IN_USE,
    MC_NO_CONTEXT,
    MC_OFFSET_TABLE_TOO_SHORT,
    MC_MISSING_DELIMITER,
    MC_COMPRESSION_FAILURE,
    MC_END_OF_FRAME,
    MC_MUST_CONTINUE_BEFORE_READING,
    MC_COMPRESSOR_REQUIRED,
    MC_DECOMPRESSOR_REQUIRED,
    MC_DATA_AVAILABLE,
    MC_ZLIB_ERROR,
    MC_NOT_META_SOP,
    MC_INVALID_ITEM_TRANSFER_SYNTAX,
    MC_LICENSE_ERROR,
    MC_MAX_OPERATIONS_EXCEEDED,
    MC_INVALID_RECORD_ID,
    MC_INVALID_DICOMDIR_FILE,
    MC_INVALID_VR
} MC_STATUS;
      
                                  
/*
 * Public Function prototype
 */
EXP_PRE extern char* EXP_FUNC MC_Error_Message (MC_STATUS AstatusCode);
EXP_PRE extern char* EXP_FUNC MC_Pegasus_Error_Message (MC_STATUS AstatusCode);

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



