#include "common.h"

/*
 * The Shift-JIS text helpers: decode, encode and format a number.
 *
 * File boundaries: guess (docs/layout.md)
 */

s8 *itoa(s32 value);
s8 *strcpy(s8 *dst, s8 *src);
s32 strlen(u8 *s);
void *memset(void *dst, s32 c, s32 n);
s8 *Text_Encode(s8 *dst, u8 *src);

s8 *Text_Decode(s8 *dst, u8 *src) {
    s8 *end = dst;
    s8 *out;
    u8 c;
    s32 value;
    s32 k;

    c = *src++;
    if (c != 0) {
        k = 0x40;
        out = dst;
        do {
            out++;
            c = *src;
            end++;
            if (c >= 0x80 || c == k) {
                value = c - 0x20;
            } else {
                value = c - 0x1F;
            }
            out[-1] = value;
            src++;
        } while (*src++ != 0);
    }
    *end = 0;
    return end;
}

s8 *Text_Encode(s8 *dst, u8 *src) {
    s8 *next;
    s8 *out;
    u8 c;
    s32 hi;
    s32 lo;

    next = dst;
    out = dst;
    while (*src != 0) {
        next++;
        hi = 0x81;
        if (*src >= 0x30) {
            hi = 0x82;
        }
        *out = hi;
        out = next;
        c = *src;
        next++;
        if (c >= 0x60 || c == 0x20) {
            lo = c + 0x20;
        } else {
            lo = c + 0x1F;
        }
        src++;
        *out = lo;
        out = next;
    }
    *next = 0;
    return next;
}

void Text_FormatNumber(s8 *dst, s32 value, s32 width, s32 noPad) {
    char digits[width + 1];
    char padded[width + 1];
    s32 pad;
    u8 *src;

    pad = strlen(strcpy(digits, itoa(value)));
    pad = width - pad;
    if (noPad == 0) {
        memset(padded, 0x30, width);
        strcpy(padded + pad, digits);
    }
    src = padded;
    if (noPad != 0) {
        src = digits;
    }
    Text_Encode(dst, src);
}
