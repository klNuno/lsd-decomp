#include "common.h"
#include "game/file_null.h"

/*
 * The null file back end (vtable g_fileNullVtbl, File_GetNullVtbl): the back end 0x23 that
 * File_SetBackend of src/game/file_base.c can pick; every I/O slot is empty.
 *
 * File boundaries: likely (docs/layout.md)
 */

/* Globals of the bank code, in their original order. */
s32 g_fileNullEnabled;
s32 g_fileNullOption;
extern u8 g_fileNullVtbl[];

void File_NullInit(void) {
}

void File_NullDestroy(void) {
}

void File_NullEmptySlot40(void) {
    u8 buf[0x40];
}

void File_NullOpen(void) {
    u8 buf[0x40];
}

void File_NullClose(void) {
}

void File_NullSeek(void) {
}

void File_NullEmptySlot50(void) {
}

s32 File_NullRead(void) {
    return 0;
}

void File_NullLoad(void) {
}

void File_NullRunQueue(void) {
}

void File_NullLoadAsync(void) {
}

void File_NullStop(void) {
}

void File_NullCancel(void) {
}

void *File_GetNullVtbl(void) {
    return g_fileNullVtbl;
}

s32 File_NullGetEnabled(s32 *valueOut) {
    if (valueOut != NULL) {
        *valueOut = g_fileNullOption;
    }
    return g_fileNullEnabled;
}

s32 File_NullEnable(s32 firstValue, s32 secondValue) {
    g_fileNullEnabled = firstValue;
    g_fileNullOption = secondValue;
    return 1;
}

s32 File_NullGetVSyncMode(void) {
    return 0;
}
