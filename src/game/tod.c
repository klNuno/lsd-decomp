#include "common.h"
#include "game/tod.h"
#include "game/heap.h"
#include "game/file_base.h"

/*
 * Tod: a TOD animation file (include/game/tod.h).
 *
 * File boundaries: likely (docs/layout.md)
 */

extern TodVtbl g_todVtbl;

Tod *Tod_Create(FileSource *source) {
    Tod *tod;

    tod = Heap_Alloc(0x2C);
    if (tod != NULL) {
        Tod_GetVtbl()->base.init(tod, source);
        return tod;
    }
    return NULL;
}

void Tod_Init(Tod *tod, FileSource *source) {
    u8 *data;
    TodVtbl *vtbl;

    File_GetBackendVtbl()->init(tod);
    vtbl = Tod_GetVtbl();
    tod->vtbl = vtbl;
    data = source->data;
    if (data != NULL) {
        tod->data.bytes = data;
        tod->size = 0;
        tod->vtbl->base.onLoaded(tod);
        return;
    }
    vtbl->base.loadAsync(tod, source->path);
}

void Tod_Destroy(Tod *tod) {
    File_GetBackendVtbl()->destroy(tod);
}

/* Slot 0x78: slot 0x7C on the first frame, after the 8-byte file header */
s32 Tod_ScanFirstFrame(Tod *tod, s32 ids, s32 tmdId) {
    return tod->vtbl->scanFrame(tod, ids, tmdId, tod->data.bytes + 8) & 0xFF;
}

/*
 * Slot 0x7C: returns how many objects the frame creates (type 8, flag 0) and stores their ids
 * in ids. With ids and tmdId, *tmdId becomes the index among them of the object the type 2
 * packet with TMD *tmdId names; with tmdId alone, the count of type 2 packets.
 */
s32 Tod_ScanFrame(Tod *tod, u8 *ids, s32 *tmdId, TodCursor packet) {
    u8 fields[4];              /* id, type, flag, length */
    u16 count;
    u32 i;
    u8 created;
    s32 found;
    s32 j;

    count = packet.frame->packetCount;
    packet.frame++;
    i = 0;
    created = 0;
    found = 0;
    for (; i < count; i++) {
        Tod_ReadPacket(tod, packet.words, &fields[0], &fields[1], &fields[2], &fields[3]);
        if (fields[1] == 8 && fields[2] == 0) {
            created++;
            if (ids != NULL) {
                *ids++ = fields[0];
            }
        } else if (fields[1] == 2) {
            if (ids != NULL) {
                if (tmdId != NULL && packet.packet->tmdId == *tmdId) {
                    j = 0;
                    ids -= created;
                    for (; j < created; j++) {
                        if (*ids++ == fields[0]) {
                            found = j;
                            break;
                        }
                    }
                }
            } else if (tmdId != NULL) {
                found++;
            }
        }
        packet.words += fields[3];
    }
    if (tmdId != NULL) {
        *tmdId = found;
    }
    return created;
}

/* Slot 0x80: splits a TOD packet header; returns the word after it */
u32 *Tod_ReadPacket(void *tod, u32 *packet, u8 *id, u8 *type, u8 *flag, u8 *length) {
    u32 header = *packet;

    *id = header;
    *type = (header >> 16) & 0xF;
    *flag = (header >> 20) & 0xF;
    *length = header >> 24;
    return packet + 1;
}

TodVtbl *Tod_GetVtbl(void) {
    return &g_todVtbl;
}
