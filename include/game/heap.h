#ifndef GAME_HEAP_H
#define GAME_HEAP_H

#include "common.h"

/*
 * The game's heap: one pool made at boot by Heap_Create(0x166C00) (pointer g_mainHeap),
 * never reset until power-off. First fit from the head of a doubly linked free list, the
 * low end of a block is handed out; free merges both neighbours and pushes the block at
 * the head (work/hunt6/F-findings.md).
 *
 * Every block starts with a header word: size in the low 28 bits (header included),
 * HEAP_FREE when the block is free, HEAP_PREV_FREE when the block just below it is free.
 * A free block's last word points back to its header, so free can find the block below.
 * The pool ends with a header of size 0 (HEAP_PREV_FREE only) that stops the walk.
 */
#define HEAP_PREV_FREE 0x80000000
#define HEAP_FREE 0x40000000
#define HEAP_FLAGS 0xF0000000
#define HEAP_SIZE_MASK 0x0FFFFFFF

typedef struct HeapBlock {
    u32 header;              /* size | HEAP_FREE | HEAP_PREV_FREE */
    struct HeapBlock *next;  /* free list, only while free; user data starts here when used */
    struct HeapBlock *prev;
} HeapBlock;

/* malloc(size + 0x20): this header, the pool at +0x1C, and the end header after it */
typedef struct Heap {
    HeapBlock *base;   /* first block, (u8 *)heap + 0x1C */
    u32 size;          /* pool bytes, at least 0x400 */
    HeapBlock *head;   /* free list */
    HeapBlock *tail;
    s32 unk_10;        /* set to 1 by Heap_Init, never read in this unit */
} Heap;

/*
 * Singly linked list of values, one 8-byte node per value (a 16-byte heap block):
 * List_Push pushes at the head, List_Remove removes the first node holding a value,
 * List_FreeAll frees every node, List_Next steps an iterator.
 */
typedef struct ListNode {
    struct ListNode *next;
    s32 value;
} ListNode;

/*
 * The root class: vtable g_objectVtbl. Derived vtables reuse its slots (Object_Notify is in
 * the data 57 times, Object_Watch 36 times); DreamSys 0x80087BDC overrides slots 0x08 to 0x18 and 0x38.
 * An object watches other objects (watched) and is watched by others (watchers): a
 * watch adds a node to both lists, destroy tells every watcher with message 1, and
 * each watcher's onNotify then drops it.
 * Slot 0x3C is 0 in both vtables read (base and DreamSys); derived methods follow it.
 * Slots are left unprototyped: the code calls some of them with fewer arguments.
 */
typedef struct ObjectVtbl {
    s32 classWord;           /* 0 here, 0x1F34 in the DreamSys vtable 0x80087BDC: identifies the class. Its low 4 bits
                                are the sender type every onNotify dispatches on (1 display, 2 pad, 4 scene node,
                                5 clock, 9 model object); the low byte the kind Scene_DrawNode switches on.
                                Values: 0x130 menu screen, 0x1F130 main menu, 0xB card, 0x10 keyboard,
                                0x20 file chooser, 0x164 fade, 0x230 task, 0x1F34 DreamSys */
    void *(*delete_)();      /* 0x04 Object_Delete: destroy, free, return NULL */
    void (*init)();          /* 0x08 Object_Init */
    void (*destroy)();       /* 0x0C Object_Destroy */
    void (*watch)();         /* 0x10 Object_Watch (self, other) */
    void (*unwatch)();       /* 0x14 Object_Unwatch (self, other) */
    void (*unwatchAll)();    /* 0x18 Object_UnwatchAll */
    void (*nextWatched)();   /* 0x1C Object_NextWatched (self, &value, &iter) */
    void (*addWatcher)();    /* 0x20 Object_AddWatcher (self, watcher) */
    void (*removeWatcher)(); /* 0x24 Object_RemoveWatcher (self, watcher) */
    void (*freeWatchers)();  /* 0x28 Object_FreeWatchers */
    void (*nextWatcher)();   /* 0x2C Object_NextWatcher (self, &value, &iter) */
    void (*notify)();        /* 0x30 Object_Notify (self, message) */
    void (*unk_34)();        /* 0x34 Object_EmptySlot34, empty */
    void (*onNotify)();      /* 0x38 Object_OnNotify (self, sender, message) */
} ObjectVtbl;

typedef struct Object {
    ObjectVtbl *vtbl;
    ListNode *watched;   /* objects this one watches */
    ListNode *watchers;  /* objects watching this one */
} Object;

/* Message sent by destroy to every watcher: the sender is going away */
#define OBJECT_MSG_DESTROYED 1

/* Functions of src/game/heap.c that other files call or reference (docs/naming.md, Prototypes) */
Heap *Heap_Create(); /* unprototyped: main passes a second argument */
void Heap_SetCurrent(Heap *heap);
void *Heap_Alloc(); /* K&R definition: callers pass only the size, the heap argument is read only when g_currentHeap is NULL */
void *Heap_Free(); /* K&R definition: callers pass only the pointer, the heap argument is read only when g_currentHeap is NULL */
s32 Object_Delete(Object *object);
void Object_Destroy(Object *object);
void Object_Watch(Object *object, Object *other);
void Object_Unwatch(Object *object, Object *other);
void Object_UnwatchAll(Object *object);
void Object_NextWatched(Object *object, s32 *value, ListNode **iter);
void Object_AddWatcher(Object *object);
void Object_RemoveWatcher(Object *object);
void Object_FreeWatchers(Object *object);
void Object_NextWatcher(Object *object, s32 *value, ListNode **iter);
void Object_Notify(Object *object, void *message);
void Object_EmptySlot34(void);
void Object_OnNotify(Object *object, s32 sender, s32 message);
ObjectVtbl *Object_GetBaseVtbl(void);
void List_Next(s32 *value, ListNode **iter);
void Object_DeleteArray(Object **objects, s32 count);
s32 Heap_IsBusy(void);

#endif
