/*************************************************************************
 *
 *       System: MergeCOM-3 - Advanced Integrator's Tool Kit
 *
 *    $Workfile: mc3media.h $
 *
 *    $Revision: 8 $
 *
 *        $Date: 3/10/:0 10:22a $
 *
 *       Author: Merge eFilm
 *
 *  Description: This module contains public definitions for using the
 *               MergeCOM-3 Advanced Toolkit Library's Media routines.
 *
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
/* $Nokeywords$ */



#ifndef MTI_MC3MEDIA_H
#define MTI_MC3MEDIA_H

#include <stdio.h>
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
 *                Message Media Group Attribute Definitions                 *
 * ======================================================================== */
#define MEDIA_GROUP_LENGTH                  0x00020000
#define MEDIA_FILE_META_INFO_VER            0x00020001
#define MEDIA_STORAGE_SOP_CLASS_UID         0x00020002
#define MEDIA_STORAGE_SOP_INSTANCE_UID      0x00020003
#define MEDIA_TRANSFER_SYNTAX_UID           0x00020010
#define MEDIA_IMPLEMENTATION_CLASS_UID      0x00020012
#define MEDIA_IMPLEMENTATION_VER_NAME       0x00020013
#define MEDIA_SOURCE_APPLICATION_ENTITY     0x00020016
#define MEDIA_SENDING_APPLICATION_ENTITY    0x00020017
#define MEDIA_RECEIVING_APPLICATION_ENTITY  0x00020018
#define MEDIA_PRIVATE_INFO_CREATOR_UID      0x00020100
#define MEDIA_PRIVATE_INFO                  0x00020102

/* ======================================================================== *
 *                   Functions to create or free media files                *
 * ======================================================================== */
                                            
EXP_PRE extern MC_STATUS EXP_FUNC MC_Create_File(int* AfileID, const char* AfileName, const char* AserviceName, MC_COMMAND Acommand); 
EXP_PRE extern MC_STATUS EXP_FUNC MC_Create_Empty_File(int* AfileID, const char* AfileName);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Empty_File(int AfileID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Free_File(int* AfileID);

/* ======================================================================== *
 *                 Functions to stream data to or from a file               *
 * ======================================================================== */

EXP_PRE extern MC_STATUS EXP_FUNC MC_Write_File(int             AfileID, 
                                                int             AnumBytes, 
                                                void*           AuserInfo, 
                                                MC_STATUS       (NOEXP_FUNC *AuserFunction)
                                                                (char*      CBfilename,
                                                                void*       CBuserInfo,
                                                                int         CBdataSize,
                                                                void*       CBdataBuffer,
                                                                int         CBisFirst, 
                                                                int         CBisLast)); 

EXP_PRE extern MC_STATUS EXP_FUNC MC_Write_File_By_Callback(int         AapplicationID,
                                                            int         AfileID, 
                                                            int         AnumBytes, 
                                                            void*       AuserInfo, 
                                                            MC_STATUS   (NOEXP_FUNC *AuserFunction)
                                                                        (char*      CBfilename,
                                                                        void*       CBuserInfo,
                                                                        int         CBdataSize,
                                                                        void*       CBdataBuffer,
                                                                        int         CBisFirst, 
                                                                        int         CBisLast)); 
                                                
EXP_PRE extern MC_STATUS EXP_FUNC MC_Open_File (int         AapplicationID,
                                                int         AfileID,  
                                                void*       AuserInfo, 
                                                MC_STATUS   (NOEXP_FUNC *AuserFunction)
                                                            (char*      CBfilename,
                                                            void*       CBuserInfo,
                                                            int*        CBdataSize,
                                                            void**      CBdataBuffer,
                                                            int         CBisFirst,
                                                            int*        CBisLast)); 

EXP_PRE extern MC_STATUS EXP_FUNC MC_Open_File_Upto_Tag(int             AapplicationID,
                                                        int             AfileID,  
                                                        void*           AuserInfo, 
                                                        unsigned long   Atag,
                                                        long*           Aoffset,
                                                        MC_STATUS       (NOEXP_FUNC *AuserFunction)
                                                                        (char*      CBfilename,
                                                                        void*       CBuserInfo,
                                                                        int*        CBdataSize,
                                                                        void**      CBdataBuffer,
                                                                        int         CBisFirst,
                                                                        int*        CBisLast)); 

EXP_PRE extern MC_STATUS EXP_FUNC MC_Open_File_Upto_Tag_Bypass_Value(   int             AapplicationID,
                                                                        int             AfileID,  
                                                                        void*           AuserInfo, 
                                                                        unsigned long   Atag,
                                                                        MTI_BOOLEAN     AbypassTagValue,
                                                                        long*           Aoffset,
                                                                        MC_STATUS       (NOEXP_FUNC *AuserFunction)
                                                                                        (char*      CBfilename,
                                                                                        void*       CBuserInfo,
                                                                                        int*        CBdataSize,
                                                                                        void**      CBdataBuffer,
                                                                                        int         CBisFirst,
                                                                                        int*        CBisLast)); 

EXP_PRE extern MC_STATUS EXP_FUNC MC_Open_File_Bypass_OBOW( int         AapplicationID,
                                                            int         AfileID,  
                                                            void*       AuserInfo, 
                                                            MC_STATUS   (NOEXP_FUNC *AuserFunction)
                                                                        (char*      CBfilename,
                                                                        void*       CBuserInfo,
                                                                        int*        CBdataSize,
                                                                        void**      CBdataBuffer,
                                                                        int         CBisFirst,
                                                                        int*        CBisLast)); 

/* ======================================================================== *
 *                    Functions for general use of files                    *
 * ======================================================================== */

#ifndef NO_FILE_SYSTEM
#if defined (__OS2__) || defined(_WIN32)
EXP_PRE extern void      EXP_FUNC MC_List_File(int AfileID, const char* AfileName);
#else
EXP_PRE extern void      EXP_FUNC MC_List_File(int AfileID, FILE* Afp);
#endif
#endif

EXP_PRE extern MC_STATUS EXP_FUNC MC_Validate_File(int AfileID, VAL_ERR** AerrInfo, VAL_LEVEL AerrLevel);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Get_File_Preamble(int AfileID, char* Apreamble);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Set_File_Preamble(int AfileID, const char* Apreamble);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Reset_Filename(int AfileID, const char* AnewFileName);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Get_Filename(int AfileID, char* AfileName, int AbufferSize);
EXP_PRE extern MC_STATUS EXP_FUNC MC_File_To_Message(int AfileID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Message_To_File(int AmsgID, const char* AfileName);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Get_File_Length(int AfileID, unsigned long* AmsgLength);

/* ======================================================================== *
 *             Functions to navigate through DICOMDIR structure             *
 *     These functions represent the legacy DICOMDIR API, new               *
 *      implementations should use the MC_DDH... functions instead          *
 * ======================================================================== */

EXP_PRE extern MC_STATUS EXP_FUNC MC_Dir_Root_Entity(int AdirID, int* AentityID, int* AitemID, char** AitemType, int* AisLast);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Dir_Next_Entity(int AdirID, int AitemID, int* AnextEntityID, int* AnextItemID, char** AnextItemType, int* AisLast);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Dir_First_Record(int AdirID, int AentityID, int* AitemID, char** AitemType, int* AisLast);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Dir_Next_Record(int AdirID, int AentityID, int* AitemID, char** AitemType, int* AisLast);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Dir_Add_Entity(int AdirID, int AitemID, const char* AnewItemType, int* AnewEntityID, int* AnewItemID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Dir_Delete_Referenced_Entity(int AdirID, int AitemID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Dir_Add_Record(int AdirID, int AentityID, const char* AnewItemType, int* AnewItemID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Dir_Delete_Record(int AdirID, int AitemID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Dir_Root_Count(int AdirID, int* Acount);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Dir_Entity_Count(int AdirID, int AentityID, int* Acount);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Dir_Item_Count(int AdirID, int AitemID, int* Acount);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Dir_Stream_Directory_Record(int AdirID, int AitemID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Dir_Sort(int AdirID);

/* ======================================================================== *
 *             Functions manipulate MRDR records                            *
 *     These functions represent the legacy DICOMDIR API, new               *
 *      implementations should use the MC_DDH... functions instead          *
 * ======================================================================== */

EXP_PRE extern MC_STATUS EXP_FUNC MC_Dir_Open_MRDR(int AdirID, int ArefItemID, const char* AnewMrdrType, int* AnewMrdrID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Dir_Reference_MRDR(int AdirID, int ArefItemID, int AmrdrID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_Dir_Remove_Ref_MRDR(int AdirID, int ArefItemID);

/* ======================================================================== *
 *             Functions for efficient DICOMDIR manipulation                *
 *      These functions should be used instead of the MC_Dir... functions   *
 *           in new implementations.
 * ======================================================================== */

EXP_PRE extern MC_STATUS EXP_FUNC MC_DDH_Create(const char* FilePath, const char* FileSetID, int TemplateFileID, int* DirMsgIDPtr);
EXP_PRE extern MC_STATUS EXP_FUNC MC_DDH_Open(const char* FilePath, int* DirMsgIDPtr);

typedef enum
{
    MC_REC_TYPE_PATIENT,
    MC_REC_TYPE_STUDY,
    MC_REC_TYPE_SERIES,
    MC_REC_TYPE_IMAGE,
    MC_REC_TYPE_RT_DOSE,
    MC_REC_TYPE_RT_STRUCTURE_SET,
    MC_REC_TYPE_RT_PLAN,
    MC_REC_TYPE_RT_TREAT_RECORD,
    MC_REC_TYPE_PRESENTATION,
    MC_REC_TYPE_WAVEFORM,
    MC_REC_TYPE_SR_DOCUMENT,
    MC_REC_TYPE_KEY_OBJECT_DOC,
    MC_REC_TYPE_SPECTROSCOPY,
    MC_REC_TYPE_RAW_DATA,
    MC_REC_TYPE_REGISTRATION,
    MC_REC_TYPE_FIDUCIAL,
    MC_REC_TYPE_HANGING_PROTOCOL,
    MC_REC_TYPE_ENCAP_DOC,
    MC_REC_TYPE_HL7_STRUC_DOC,
    MC_REC_TYPE_VALUE_MAP,
    MC_REC_TYPE_STEREOMETRIC,
    MC_REC_TYPE_PALETTE,
    MC_REC_TYPE_IMPLANT,
    MC_REC_TYPE_IMPLANT_ASSY,
    MC_REC_TYPE_IMPLANT_GROUP,
    MC_REC_TYPE_MEASUREMENT,
    MC_REC_TYPE_SURFACE,
    MC_REC_TYPE_SURFACE_SCAN,
    MC_REC_TYPE_TRACT,
    MC_REC_TYPE_PRIVATE,
    MC_REC_TYPE_UNKNOWN
} MC_DIR_RECORD_TYPE;

EXP_PRE extern MC_STATUS EXP_FUNC MC_DDH_Get_Record_Type(int RecordID, MC_DIR_RECORD_TYPE* RecType);
EXP_PRE extern MC_STATUS EXP_FUNC MC_DDH_Get_First_Lower_Record(int ParentID, int* LowerID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_DDH_Get_Next_Record(int RecordID, int* NextID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_DDH_Get_Parent_Record(int RecordID, int* ParentID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_DDH_Release_Record(int RecordID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_DDH_Add_Record(int ParentID, const char* RecordType, int* RecordID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_DDH_Delete_Record(int RecordID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_DDH_Copy_Values(int SourceID, int DestID, unsigned long* TagList);
EXP_PRE extern MC_STATUS EXP_FUNC MC_DDH_Update(int DirMsgID);

typedef enum
{
    MC_TS_CONTINUE,
    MC_TS_STOP_LEVEL,
    MC_TS_STOP_LOWER,
    MC_TS_STOP,
    MC_TS_ERROR
} MC_TRAVERSAL_STATUS;

EXP_PRE extern MC_STATUS EXP_FUNC MC_DDH_Traverse_Records(int RootID, void* UserData, MC_TRAVERSAL_STATUS (NOEXP_FUNC *userCbk)(int CurrentRecID, void* CbkData));

/* ======================================================================== *
 *             Functions for SR                                             *
 * ======================================================================== */

EXP_PRE extern MC_STATUS EXP_FUNC MC_Message_To_SR(int AmsgID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_SR_To_Message(int AsrID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_SR_Get_Root(int AsrID, int* AitemID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_SR_Add_Child(int AsrID, int AitemID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_SR_Add_Root(int AsrID, int *AitemID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_SR_Get_First_Child(int AsrID, int* AitemID, int* AisLast);
EXP_PRE extern MC_STATUS EXP_FUNC MC_SR_Get_Next_Child(int AsrID, int* AnextChildID, int* AisLast);
EXP_PRE extern MC_STATUS EXP_FUNC MC_SR_Get_Location(int AsrID, int AsizeOfLocation, char* Alocation);
EXP_PRE extern MC_STATUS EXP_FUNC MC_SR_Delete_Child(int AsrID);
EXP_PRE extern MC_STATUS EXP_FUNC MC_SR_Get_Child_Count(int AsrID, int *AchildCount);

/* ======================================================================== *
 *             High Level functions for SR                                  *
 * ======================================================================== */
/**************** CONSTANTS *********************************/
typedef enum
{
    SR_REL_CONTAINS = 0,
    SR_REL_HAS_OBS_CONTEXT,
    SR_REL_HAS_ACQ_CONTEXT,
    SR_REL_HAS_CONCEPT_MOD,
    SR_REL_HAS_PROPERTIES,
    SR_REL_INFERRED_FROM,
    SR_REL_SELECTED_FROM
} SR_RELATIONSHIP;

typedef enum
{
    SR_GRT_POINT = 0,
    SR_GRT_MULTIPOINT,
    SR_GRT_POLYLINE,
    SR_GRT_CIRCLE,
    SR_GRT_ELLIPSE,
    SR_GRT_POLYGON,
    SR_GRT_ELLIPSOID
} SR_GRAPHIC_TYPE;

typedef enum
{
    SR_TRT_POINT = 0,
    SR_TRT_MULTIPOINT,
    SR_TRT_SEGMENT,
    SR_TRT_MULTISEGMENT,
    SR_TRT_BEGIN,
    SR_TRT_END
} SR_TRANGE_TYPE;

typedef enum
{
    SR_CC_SEPARATE = 0,
    SR_CC_CONTINUOUS
} SR_CONT_CONTINUITY;

typedef enum
{
    SR_NODE_TEXT = 0,
    SR_NODE_CODE,
    SR_NODE_NUM,
    SR_NODE_DATETIME,
    SR_NODE_DATE,
    SR_NODE_TIME,
    SR_NODE_UIDREF,
    SR_NODE_PNAME,
    SR_NODE_SCOORD,
    SR_NODE_TCOORD_D,
    SR_NODE_TCOORD_O,
    SR_NODE_TCOORD_R,
    SR_NODE_COMPOSITE,
    SR_NODE_IMAGE,
    SR_NODE_WAVEFORM,
    SR_NODE_CONTAINER,
    SR_REFERENCE,
    SR_NODE_SCOORD3D
} SR_CONTENT_TYPE;

typedef struct point3d    
{ 
    float x, y, z;
} POINT3D;

/**************** HIGH LEVEL FUNCTIONS *********************************/
/************************* SR Creation *********************************/
EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_SR (
                                        const char*        AserviceName,    
                                        const char*        AtemplateId,
                                        SR_CONT_CONTINUITY Acontinuity,
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning,
                                        int*            AsrRootID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Free_SR
                                       (int             AsrRootID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_TEXT_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning,
                                        const char*        Atext,
                                        int*            AsrChildNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_CODE_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning,
                                        const char*        AconceptCodeValue,
                                        const char*        AconceptCodingScheme,
                                        const char*        AconceptCodeMeaning,
                                        int*            AsrChildNodeID);


EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Set_NUM_Qualifier
                                       (int             AsrNodeID,
                                        const char*        AqualifierCodeValue,
                                        const char*        AqualifierCodingScheme,
                                        const char*        AqualifierCodeMeaning);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Set_NUM_Next_Data
                                        (int            AsrNodeID,
                                        const char*        AnumericValue);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_NUM_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning,
                                        const char*        AnumericValue,
                                        const char*        AunitsCodeValue,
                                        const char*        AunitsCodingScheme,
                                        const char*        AunitsCodeMeaning,
                                        int*            AsrChildNodeID);


EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_DATETIME_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning,
                                        const char*        Adatetime,
                                        int*            AsrChildNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_DATE_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning,
                                        const char*        Adate,
                                        int*            AsrChildNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_TIME_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning,
                                        const char*        Atime,
                                        int*            AsrChildNodeID);



EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_UIDREF_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning,
                                        const char*        AuidRef,
                                        int*            AsrChildNodeID);


EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_PNAME_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning,
                                        const char*        ApersonName,
                                        int*            AsrChildNodeID);


EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_SCOORD_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        float            Acolumn,
                                        float            Arow,
                                        SR_GRAPHIC_TYPE AgraphicType,
                                        int             *AsrChildNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Set_SCOORD_Next_Data
                                        (int AsrNodeID,
                                        float Acolumn,
                                        float Arow);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_SCOORD3D_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        const char*     AreferenceUID,
                                        POINT3D         Apoint3D,
                                        SR_GRAPHIC_TYPE AgraphicType,
                                        int             *AsrChildNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Set_SCOORD3D_Next_Data
                                       (int AsrNodeID,
                                        POINT3D point3D);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_TCOORD_R_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        unsigned long    ArefSamplePosition,
                                        SR_TRANGE_TYPE  AtempRangeType,
                                        int             *AsrChildNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Set_TCOORD_R_Next_Data
                                        (int             AsrNodeID,
                                        unsigned long    ArefSamplePosition);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_TCOORD_O_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        const char*        AtimeOffset,
                                        SR_TRANGE_TYPE  AtempRangeType,
                                        int*            AsrChildNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Set_TCOORD_O_Next_Data
                                        (int             AsrNodeID,
                                        const char*        AtimeOffset);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_TCOORD_D_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        const char*        AdateTimeOffset,
                                        SR_TRANGE_TYPE  AtempRangeType,
                                        int*            AsrChildNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Set_TCOORD_D_Next_Data(    
                                        int             AsrNodeID,
                                        const char*        AdateTimeOffset);


EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_COMPOSITE_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        const char*        AsopClassUid,
                                        const char*        AsopInstanceUid,
                                        int*            AsrChildNodeID);


EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_IMAGE_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        const char*        AsopClassUid,
                                        const char*        AsopInstanceUid,
                                        int*            AsrChildNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Set_IMAGE_Frames(    
                                        int             AsrNodeID,
                                        long            AreferencedFrames[],
                                        long            AframesArraySize);


EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_WAVEFORM_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        const char*        AsopClassUid,
                                        const char*        AsopInstanceUid,
                                        int*            AsrChildNodeID);


EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Set_WAVEFORM_Channels
                                       (int             AsrNodeID,
                                        unsigned short    ArefChannels[],
                                        long            ArefChannelsSize);


EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_CONTAINER_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        SR_CONT_CONTINUITY Acontinuity,
                                        const char*        AtemplateId,
                                        int*            AsrChildNodeID);


EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Set_Concept_Name
                                       (int             AsrNodeID,
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning);

/************************* SR Reading *********************************/
EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_NodeType( 
                                        int             AsrNodeID,
                                        SR_CONTENT_TYPE    *AnodeType);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_First_Child(  
                                        int  AsrNodeID,
                                        int* AsrChildNodeID,
                                        SR_RELATIONSHIP *Arelationship,
                                        SR_CONTENT_TYPE    *AnodeType,
                                        int* AisLast );

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_Next_Child(  
                                        int  AsrNodeID,
                                        int* AsrChildNodeID,
                                        SR_RELATIONSHIP *Arelationship,
                                        SR_CONTENT_TYPE    *AnodeType,
                                        int* AisLast );

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_Concept_Name(    
                                        int         AsrNodeID,
                                        char        AconceptNameValue[],
                                        int            AconceptNameValueSize,
                                        char        AconceptNameScheme[],
                                        int            AconceptNameSchemeSize,
                                        char        AconceptNameMeaning[],
                                        int            AconceptNameMeaningSize);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_TEXT_Data(   
                                        int         AsrNodeID,
                                        char        Atext[],
                                        int            AtextSize);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_CODE_Data(    
                                        int         AsrNodeID,
                                        char        AconceptCodeValue[],
                                        int            AconceptCodeValueSize,
                                        char        AconceptCodingScheme[],
                                        int            AconceptCodingSchemeSize,
                                        char        AconceptCodeMeaning[],
                                        int            AconceptCodeMeaningSize);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_NUM_Data(    
                                        int         AsrNodeID,
                                        char        AnumericValue[],
                                        int             AnumericValueSize,
                                        int*        AvalueCount,
                                        char        AunitsCodeValue[],
                                        int         AunitsCodeValueSize,
                                        char        AunitsCodingScheme[],
                                        int            AunitsCodingSchemeSize,
                                        char        AunitsCodeMeaning[],
                                        int            AunitsCodeMeaningSize);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_NUM_Next_Data(
                                        int         AsrNodeID,
                                        char        AnumericValue[],
                                        int            AnumericValueSize);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_NUM_Qualifier(
                                        int         AsrNodeID,
                                        char        AqualifierCodeValue[],
                                        int            AqualifierCodeValueSize,
                                        char        AqualifierCodingScheme[],
                                        int            AqualifierCodingSchemeSize,
                                        char        AqualifierCodeMeaning[],
                                        int            AqualifierCodeMeaningSize);


EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_DATETIME_Data(   
                                        int         AsrNodeID,
                                        char        AdateTime[],
                                        int            AdateTimeSize);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_DATE_Data(   
                                        int         AsrNodeID,
                                        char        Adate[],
                                        int            AdateSize);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_TIME_Data(   
                                        int     AsrNodeID,
                                        char    Atime[],
                                        int        AtimeSize);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_UIDREF_Data( 
                                        int     AsrNodeID,
                                        char    AuidRef[],
                                        int        AuidRefSize);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_PNAME_Data(  
                                        int     AsrNodeID,
                                        char    ApersonName[],
                                        int     ApersonNameSize);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_SCOORD_First_Data(    
                                        int              AsrNodeID,
                                        float*           Acolumn,
                                        float*           Arow,
                                        int*             AvalueCount,
                                        SR_GRAPHIC_TYPE* AgraphicType);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_SCOORD_Next_Data(    
                                        int       AsrNodeID,
                                        float*    Acolumn,
                                        float*    Arow);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_SCOORD3D_First_Data
                                       (int              AsrNodeID,
                                        char**           AreferenceUID,
                                        POINT3D*         Apoint3D,
                                        int*             AvalueCount,
                                        SR_GRAPHIC_TYPE* AgraphicType);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_SCOORD3D_Next_Data
                                       (int            AsrNodeID,
                                        POINT3D*       Apoint3D);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_TCOORD_D_First_Data( 
                                        int     AsrNodeID,
                                        char    AdateTimeOffset[],
                                        int        AdateTimeOffsetSize,
                                        int*    AvalueCount,
                                        SR_TRANGE_TYPE *AtempRangeType);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_TCOORD_D_Next_Data(  
                                        int     AsrNodeID,
                                        char    AdateTimeOffset[],
                                        int        AdateTimeOffsetSize);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_TCOORD_O_First_Data( 
                                        int     AsrNodeID,
                                        char    AtimeOffset[],
                                        int        AtimeOffsetSize,
                                        int*    AvalueCount,
                                        SR_TRANGE_TYPE *AtempRangeType);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_TCOORD_O_Next_Data(  
                                        int     AsrNodeID,
                                        char    AtimeOffset[],
                                        int        AtimeOffsetSize);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_TCOORD_R_First_Data( 
                                        int                AsrNodeID,
                                        unsigned long*    ArefSamplePosition,
                                        int*            AvalueCount,
                                        SR_TRANGE_TYPE*    AtempRangeType);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_TCOORD_R_Next_Data( 
                                        int                AsrNodeID,
                                        unsigned long*    ArefSamplePosition);


EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_COMPOSITE_Data(  
                                        int     AsrNodeID,
                                        char    AsopClassUid[],
                                        int        AsopClassUidSize,
                                        char    AsopInstanceUid[],
                                        int        AsopInstanceUidSize);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_IMAGE_Data(  
                                        int     AsrNodeID,
                                        char    AsopClassUid[],
                                        int        AsopClassUidSize,
                                        char    AsopInstanceUid[],
                                        int        AsopInstanceUidSize,
                                        int*    ArefFramesCount);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_IMAGE_Frames(    
                                        int     AsrNodeID,
                                        long    AreferencedFrames[],
                                        long    AframesArraySize);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_WAVEFORM_Data(    
                                        int     AsrNodeID,
                                        char    AsopClassUid[],
                                        int        AsopClassUidSize,
                                        char    AsopInstanceUid[],
                                        int        AsopInstanceUidSize,
                                        int*    ArefChannelsCount);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_WAVEFORM_Channels(    
                                        int             AsrNodeID,
                                        unsigned short    ArefChannels[],
                                        long            ArefChannelsSize);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_CONTAINER_Data(    
                                        int             AsrNodeID,
                                        SR_CONT_CONTINUITY* Acontinuity,
                                        char    AtemplateId[],
                                        int        AtemplateIdSize);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Get_Reference(    
                                        int     AsrNodeID,
                                        int*    AsrRefNodeID);

/**************** UTILITY FUNCTIONS *********************************/

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_Child
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        int*            AsrChildNodeID);


EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Add_Reference
                                       (int             AsrNodeID,
                                        SR_RELATIONSHIP Arelationship,
                                        int             AsrRefNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_TEXT_Node( 
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning,
                                        const char*        Atext,
                                        int*            AsrNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_CODE_Node(
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning,
                                        const char*        AconceptCodeValue,
                                        const char*        AconceptCodingScheme,
                                        const char*        AconceptCodeMeaning,
                                        int*            AsrNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_NUM_Node(    
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning,
                                        const char*        AnumericValue,
                                        const char*        AunitsCodeValue,
                                        const char*        AunitsCodingScheme,
                                        const char*        AunitsCodeMeaning,
                                        int*            AsrNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_DATETIME_Node(
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning,
                                        const char*        Adatetime,
                                        int*            AsrNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_DATE_Node(
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning,
                                        const char*        Adate,
                                        int*            AsrNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_TIME_Node(
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning,
                                        const char*        Atime,
                                        int*            AsrNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_UIDREF_Node(
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning,
                                        const char*        AuidRef,
                                        int*            AsrNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_PNAME_Node(
                                        const char*        AconceptNameValue,
                                        const char*        AconceptNameScheme,
                                        const char*        AconceptNameMeaning,
                                        const char*        ApersonName,
                                        int*            AsrNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_SCOORD_Node(    
                                        float            Acolumn,
                                        float            Arow,
                                        SR_GRAPHIC_TYPE AgraphicType,
                                        int*            AsrNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_SCOORD3D_Node
                                       (const char*     AreferenceUID,
                                        POINT3D         Apoint,
                                        SR_GRAPHIC_TYPE AgraphicType,
                                        int*            AsrNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_TCOORD_R_Node(    
                                        unsigned long    ArefSamplePosition,
                                        SR_TRANGE_TYPE  AtempRangeType,
                                        int*            AsrNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_TCOORD_O_Node(    
                                        const char*        AtimeOffset,
                                        SR_TRANGE_TYPE  AtempRangeType,
                                        int*            AsrNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_TCOORD_D_Node(    
                                        const char*        AdateTimeOffsets,
                                        SR_TRANGE_TYPE  AtempRangeType,
                                        int*            AsrNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_COMPOSITE_Node(
                                        const char*        AsopClassUid,
                                        const char*        AsopInstanceUid,
                                        int*            AsrNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_IMAGE_Node(
                                        const char*        AsopClassUid,
                                        const char*        AsopInstanceUid,
                                        int*            AsrNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_WAVEFORM_Node(    
                                        const char*        AsopClassUid,
                                        const char*        AsopInstanceUid,
                                        int*            AsrNodeID);

EXP_PRE extern MC_STATUS EXP_FUNC MC_SRH_Create_CONTAINER_Node(    
                                        SR_CONT_CONTINUITY Acontinuity,
                                        const char*        AtemplateId,
                                        int*            AsrNodeID);

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

