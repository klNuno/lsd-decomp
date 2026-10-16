#include "common.h"
#include "gte.h"
#include "game/heap.h"
#include "psyq/libapi.h"
#include "psyq/libc.h"

/*
 * File boundaries: guess (docs/layout.md)
 */

Heap *g_currentHeap; /* the heap Heap_Init, Heap_Alloc and Heap_Free use; their heap argument only when NULL */
static void Heap_Init(Heap *fallbackHeap);
extern ObjectVtbl g_objectVtbl[]; /* the root class vtable */
s32 g_heapBusy; /* heap busy flag, Heap_SetBusy */
static s32 List_Push();
static void List_Remove();
static void List_FreeAll(ListNode **head);
static void Heap_SetBusy(s32 busy);

Heap *Heap_Create(u32 size) {
    Heap *heap;

    if (size < 0x400) {
        size = 0x400;
    }
    heap = malloc(size + 0x20);
    if (heap != NULL) {
        heap->base = (HeapBlock *)((u8 *)heap + 0x1C);
        heap->size = size;
        Heap_Init(heap);
    } else {
        printf("bMemPMgr = %p, poolSize = %ld in BMemPMgrInit\n", 0, size);
    }
    return heap;
}

void Heap_SetCurrent(Heap *heap) {
    g_currentHeap = heap;
}

static void Heap_Delete(void *heap) {
    free(heap);
}

/* The whole pool becomes one free block, followed by the end header. */
static void Heap_Init(Heap *fallbackHeap) {
    Heap *heap = g_currentHeap;
    HeapBlock *block;
    u8 *end;
    if (heap == NULL) {
        heap = fallbackHeap;
    }
    heap->unk_10 = 1;
    block = heap->base;
    heap->head = block;
    heap->tail = block;
    block->header = heap->size | HEAP_FREE;
    heap->head->next = NULL;
    heap->tail->prev = NULL;
    end = (u8 *)block + (block->header & HEAP_SIZE_MASK);
    ((HeapBlock **)end)[-1] = block;
    *(u32 *)end = HEAP_PREV_FREE;
}

/* K&R on purpose: callers pass only the size. Returns NULL when no free block is large enough. */
void *Heap_Alloc(size, fallbackHeap)
    u32 size;
    Heap *fallbackHeap;
{
    Heap *heap;
    HeapBlock *block;
    HeapBlock *rest;
    HeapBlock *prev;
    HeapBlock *next;
    HeapBlock *after;
    HeapBlock *before;
    void *result;
    u32 header;
    u32 blockSize;
    u32 tmp;
    u32 pad;

    Heap_SetBusy(1);
    result = NULL;
    heap = g_currentHeap;
    if (heap == NULL) {
        heap = fallbackHeap;
    }
    if (size != 0) {
        /* round up to a word, at least 12 bytes of data, plus the header word */
        pad = size & 3;
        if (pad != 0) {
            tmp = size + 4;
            size = tmp - pad;
        }
        if (size < 0xC) {
            size = 0xC;
        }
        size += 4;
        block = heap->head;
        while (block != NULL) {
            header = block->header;
            blockSize = header & HEAP_SIZE_MASK;
            if (blockSize >= size) {
                block->header = header & 0xBFFFFFFF;
                result = (char *)block + 4;
                if (blockSize < size + 0x10) {
                    /* too small to split: hand out the whole block */
                    rest = (HeapBlock *)((char *)block + (block->header & HEAP_SIZE_MASK));
                    rest->header &= 0x7FFFFFFF;
                    next = block->next;
                    prev = block->prev;
                    if (next != NULL) {
                        next->prev = prev;
                    } else {
                        heap->tail = prev;
                    }
                    before = block->prev;
                    after = block->next;
                    if (before != NULL) {
                        before->next = after;
                    } else {
                        heap->head = after;
                    }
                } else {
                    /* split: the low end is used, the rest takes its place in the free list */
                    block->header = (block->header & HEAP_FLAGS) | size;
                    rest = (HeapBlock *)((char *)block + (block->header & HEAP_SIZE_MASK));
                    rest->header = (blockSize - size) | HEAP_FREE;
                    rest->next = block->next;
                    rest->prev = block->prev;
                    if (block->next != NULL) {
                        block->next->prev = rest;
                    } else {
                        heap->tail = rest;
                    }
                    if (block->prev != NULL) {
                        block->prev->next = rest;
                    } else {
                        heap->head = rest;
                    }
                    *(HeapBlock **)((char *)rest + (rest->header & HEAP_SIZE_MASK) - 4) = rest;
                }
                break;
            }
            block = block->next;
        }
    }
    Heap_SetBusy(0);
    return result;
}

/* K&R on purpose: callers pass only the pointer. Merges the free neighbours, pushes at the head. */
void *Heap_Free(data, fallbackHeap)
    void *data;
    Heap *fallbackHeap;
{
    Heap *heap;
    HeapBlock *block;
    HeapBlock *next;
    u32 size;
    u32 nextFree;

    Heap_SetBusy(1);
    heap = g_currentHeap;
    if (heap == NULL) {
        heap = fallbackHeap;
    }
    if (data != NULL) {
        block = (HeapBlock *)((u8 *)data - 4);
        next = (HeapBlock *)((u8 *)block + (block->header & HEAP_SIZE_MASK));
        nextFree = next->header & HEAP_FREE;
        if ((s32)block->header < 0) {
            /* HEAP_PREV_FREE: grow the block below over this one, take it off the list */
            size = block->header & HEAP_SIZE_MASK;
            block = ((HeapBlock **)block)[-1];
            block->header = (block->header & HEAP_FLAGS) | (size + (block->header & HEAP_SIZE_MASK));
            {
                HeapBlock *p;
                HeapBlock *n;
                n = block->next;
                p = block->prev;
                if (n != NULL) {
                    n->prev = p;
                } else {
                    heap->tail = p;
                }
            }
            {
                HeapBlock *n;
                HeapBlock *p;
                p = block->prev;
                n = block->next;
                if (p != NULL) {
                    p->next = n;
                } else {
                    heap->head = n;
                }
            }
        }
        if (nextFree != 0) {
            /* the block above is free: absorb it */
            size = next->header & HEAP_SIZE_MASK;
            block->header = (block->header & HEAP_FLAGS) | (size + (block->header & HEAP_SIZE_MASK));
            {
                HeapBlock *p;
                HeapBlock *n;
                n = next->next;
                p = next->prev;
                if (n != NULL) {
                    n->prev = p;
                } else {
                    heap->tail = p;
                }
            }
            {
                HeapBlock *n;
                HeapBlock *p;
                p = next->prev;
                n = next->next;
                if (p != NULL) {
                    p->next = n;
                } else {
                    heap->head = n;
                }
            }
            next = (HeapBlock *)((u8 *)block + (block->header & HEAP_SIZE_MASK));
        }
        block->next = heap->head;
        heap->head = block;
        block->prev = NULL;
        if (block->next != NULL) {
            block->next->prev = block;
        } else {
            heap->tail = block;
        }
        ((HeapBlock **)next)[-1] = block;
        block->header |= HEAP_FREE;
        next->header |= HEAP_PREV_FREE;
    }
    Heap_SetBusy(0);
    return NULL;
}

static void func_80017EA8(void) {
}

/* vtable slot 0x04 */
s32 Object_Delete(Object *object) {
    object->vtbl->destroy();
    Heap_Free(object);
    return 0;
}

/* vtable slot 0x08 */
void Object_Init(Object *object) {
    object->vtbl = Object_GetBaseVtbl();
    object->watchers = 0;
    object->watched = 0;
}

/* vtable slot 0x0C */
void Object_Destroy(Object *object) {
    object->vtbl->notify(object, OBJECT_MSG_DESTROYED);
    object->vtbl->unwatchAll(object);
    object->vtbl->freeWatchers(object);
}

/* vtable slot 0x10; `other` reaches List_Push untouched in a1 */
void Object_Watch(Object *object, Object *other) {
    if (List_Push(&object->watched) != 0) {
        other->vtbl->addWatcher(other, object);
    }
}

/* vtable slot 0x14; `other` reaches List_Remove untouched in a1 */
void Object_Unwatch(Object *object, Object *other) {
    List_Remove(&object->watched);
    other->vtbl->removeWatcher(other, object);
}

/* vtable slot 0x18 */
void Object_UnwatchAll(Object *object) {
    s32 watched;
    s32 *value;
    ListNode *iter;

    value = &watched;
    iter = object->watched;
    List_Next(value, &iter);
    while (watched != 0) {
        object->vtbl->unwatch(object, watched);
        List_Next(value, &iter);
    }
}

/* vtable slot 0x1C: start with *value == 0 */
void Object_NextWatched(Object *object, s32 *value, ListNode **iter) {
    if (*value == 0) {
        *iter = object->watched;
    }
    List_Next(value, iter);
}

/* vtable slot 0x20; the watcher reaches List_Push untouched in a1 */
void Object_AddWatcher(Object *object) {
    List_Push(&object->watchers);
}

/* vtable slot 0x24; the watcher reaches List_Remove untouched in a1 */
void Object_RemoveWatcher(Object *object) {
    List_Remove(&object->watchers);
}

/* vtable slot 0x28 */
void Object_FreeWatchers(Object *object) {
    List_FreeAll(&object->watchers);
    object->watchers = NULL;
}

/* vtable slot 0x2C: start with *value == 0 */
void Object_NextWatcher(Object *object, s32 *value, ListNode **iter) {
    if (*value == 0) {
        *iter = object->watchers;
    }
    List_Next(value, iter);
}

static s32 List_Push(ListNode **head, s32 value) {
    ListNode *node;

    node = Heap_Alloc(8);
    if (node != NULL) {
        node->next = *head;
        node->value = value;
        *head = node;
        return 1;
    }
    return 0;
}

static void List_Remove(ListNode **head, s32 value) {
    ListNode *node;
    ListNode *prev;

    node = *head;
    prev = NULL;
    while (node != NULL) {
        if (node->value == value) {
            if (prev != NULL) {
                prev->next = node->next;
            } else {
                *head = node->next;
            }
            Heap_Free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

static void List_FreeAll(ListNode **head) {
    ListNode *node;
    ListNode *cur;

    node = *head;
    while (node != NULL) {
        cur = node;
        node = node->next;
        Heap_Free(cur);
    }
}

/* vtable slot 0x30: calls onNotify(watcher, object, message) on every watcher */
void Object_Notify(Object *object, void *message) {
    Object *watcher;
    ListNode *iter;

    iter = object->watchers;
    List_Next(&watcher, &iter);
    while (watcher != NULL) {
        watcher->vtbl->onNotify(watcher, object, message);
        List_Next(&watcher, &iter);
    }
}

/* vtable slot 0x34 */
void func_80018350(void) {
}

/* vtable slot 0x38: a watched object going away is dropped (`sender` stays in a1) */
void Object_OnNotify(Object *object, s32 sender, s32 message) {
    if (message == OBJECT_MSG_DESTROYED) {
        object->vtbl->unwatch();
    }
}

ObjectVtbl *Object_GetBaseVtbl(void) {
    return g_objectVtbl;
}

/* *value = the node's value and *iter steps to the next node; *value = 0 at the end */
void List_Next(s32 *value, ListNode **iter) {
    ListNode *node;

    node = *iter;
    if (node != NULL) {
        *value = node->value;
        *iter = (*iter)->next;
        return;
    }
    *value = 0;
}

/* Deletes `count` objects through vtable slot 0x04 and leaves NULL in each slot */
void Object_DeleteArray(Object **objects, s32 count) {
    while (count-- > 0) {
        *objects = (*objects)->vtbl->delete_(*objects);
        objects++;
    }
}

/* Set to 1 while Heap_Alloc or Heap_Free runs */
static void Heap_SetBusy(s32 busy) {
    g_heapBusy = busy;
}

s32 Heap_IsBusy(void) {
    return g_heapBusy;
}
