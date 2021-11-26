// This is a generated source file for Chilkat version 9.5.0.56
#ifndef _C_CkJsonObject_H
#define _C_CkJsonObject_H
#include "chilkatDefs.h"

#include "Chilkat_C.h"

CK_VISIBLE_PUBLIC HCkJsonObject CkJsonObject_Create(void);
CK_VISIBLE_PUBLIC void CkJsonObject_Dispose(HCkJsonObject handle);
CK_VISIBLE_PUBLIC void CkJsonObject_getDebugLogFilePath(HCkJsonObject cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkJsonObject_putDebugLogFilePath(HCkJsonObject cHandle, const char *newVal);
CK_VISIBLE_PUBLIC const char *CkJsonObject_debugLogFilePath(HCkJsonObject cHandle);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_getEmitCompact(HCkJsonObject cHandle);
CK_VISIBLE_PUBLIC void CkJsonObject_putEmitCompact(HCkJsonObject cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_getEmitCrLf(HCkJsonObject cHandle);
CK_VISIBLE_PUBLIC void CkJsonObject_putEmitCrLf(HCkJsonObject cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkJsonObject_getI(HCkJsonObject cHandle);
CK_VISIBLE_PUBLIC void CkJsonObject_putI(HCkJsonObject cHandle, int newVal);
CK_VISIBLE_PUBLIC int CkJsonObject_getJ(HCkJsonObject cHandle);
CK_VISIBLE_PUBLIC void CkJsonObject_putJ(HCkJsonObject cHandle, int newVal);
CK_VISIBLE_PUBLIC int CkJsonObject_getK(HCkJsonObject cHandle);
CK_VISIBLE_PUBLIC void CkJsonObject_putK(HCkJsonObject cHandle, int newVal);
CK_VISIBLE_PUBLIC void CkJsonObject_getLastErrorHtml(HCkJsonObject cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkJsonObject_lastErrorHtml(HCkJsonObject cHandle);
CK_VISIBLE_PUBLIC void CkJsonObject_getLastErrorText(HCkJsonObject cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkJsonObject_lastErrorText(HCkJsonObject cHandle);
CK_VISIBLE_PUBLIC void CkJsonObject_getLastErrorXml(HCkJsonObject cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkJsonObject_lastErrorXml(HCkJsonObject cHandle);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_getLastMethodSuccess(HCkJsonObject cHandle);
CK_VISIBLE_PUBLIC void CkJsonObject_putLastMethodSuccess(HCkJsonObject cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkJsonObject_getSize(HCkJsonObject cHandle);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_getUtf8(HCkJsonObject cHandle);
CK_VISIBLE_PUBLIC void CkJsonObject_putUtf8(HCkJsonObject cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_getVerboseLogging(HCkJsonObject cHandle);
CK_VISIBLE_PUBLIC void CkJsonObject_putVerboseLogging(HCkJsonObject cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkJsonObject_getVersion(HCkJsonObject cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const char *CkJsonObject_version(HCkJsonObject cHandle);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_AddArrayAt(HCkJsonObject cHandle, int index, const char *name);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_AddBoolAt(HCkJsonObject cHandle, int index, const char *name, BOOL value);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_AddIntAt(HCkJsonObject cHandle, int index, const char *name, int value);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_AddNullAt(HCkJsonObject cHandle, int index, const char *name);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_AddNumberAt(HCkJsonObject cHandle, int index, const char *name, const char *numericStr);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_AddObjectAt(HCkJsonObject cHandle, int index, const char *name);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_AddStringAt(HCkJsonObject cHandle, int index, const char *name, const char *value);
CK_VISIBLE_PUBLIC HCkJsonArray CkJsonObject_ArrayAt(HCkJsonObject cHandle, int index);
CK_VISIBLE_PUBLIC HCkJsonArray CkJsonObject_ArrayOf(HCkJsonObject cHandle, const char *jsonPath);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_BoolAt(HCkJsonObject cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_BoolOf(HCkJsonObject cHandle, const char *jsonPath);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_Delete(HCkJsonObject cHandle, const char *name);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_DeleteAt(HCkJsonObject cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_Emit(HCkJsonObject cHandle, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkJsonObject_emit(HCkJsonObject cHandle);
CK_VISIBLE_PUBLIC HCkJsonObject CkJsonObject_GetDocRoot(HCkJsonObject cHandle);
CK_VISIBLE_PUBLIC int CkJsonObject_IndexOf(HCkJsonObject cHandle, const char *name);
CK_VISIBLE_PUBLIC int CkJsonObject_IntAt(HCkJsonObject cHandle, int index);
CK_VISIBLE_PUBLIC int CkJsonObject_IntOf(HCkJsonObject cHandle, const char *jsonPath);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_IsNullAt(HCkJsonObject cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_IsNullOf(HCkJsonObject cHandle, const char *jsonPath);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_Load(HCkJsonObject cHandle, const char *json);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_LoadFile(HCkJsonObject cHandle, const char *path);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_NameAt(HCkJsonObject cHandle, int index, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkJsonObject_nameAt(HCkJsonObject cHandle, int index);
CK_VISIBLE_PUBLIC HCkJsonObject CkJsonObject_ObjectAt(HCkJsonObject cHandle, int index);
CK_VISIBLE_PUBLIC HCkJsonObject CkJsonObject_ObjectOf(HCkJsonObject cHandle, const char *jsonPath);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_Rename(HCkJsonObject cHandle, const char *oldName, const char *newName);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_RenameAt(HCkJsonObject cHandle, int index, const char *name);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_SaveLastError(HCkJsonObject cHandle, const char *path);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_SetBoolAt(HCkJsonObject cHandle, int index, BOOL value);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_SetBoolOf(HCkJsonObject cHandle, const char *jsonPath, BOOL value);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_SetIntAt(HCkJsonObject cHandle, int index, int value);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_SetIntOf(HCkJsonObject cHandle, const char *jsonPath, int value);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_SetNullAt(HCkJsonObject cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_SetNullOf(HCkJsonObject cHandle, const char *jsonPath);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_SetNumberAt(HCkJsonObject cHandle, int index, const char *value);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_SetNumberOf(HCkJsonObject cHandle, const char *jsonPath, const char *value);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_SetStringAt(HCkJsonObject cHandle, int index, const char *value);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_SetStringOf(HCkJsonObject cHandle, const char *jsonPath, const char *value);
CK_VISIBLE_PUBLIC int CkJsonObject_SizeOfArray(HCkJsonObject cHandle, const char *jsonPath);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_StringAt(HCkJsonObject cHandle, int index, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkJsonObject_stringAt(HCkJsonObject cHandle, int index);
CK_VISIBLE_PUBLIC BOOL CkJsonObject_StringOf(HCkJsonObject cHandle, const char *jsonPath, HCkString outStr);
CK_VISIBLE_PUBLIC const char *CkJsonObject_stringOf(HCkJsonObject cHandle, const char *jsonPath);
#endif
