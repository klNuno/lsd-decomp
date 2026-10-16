#include "common.h"
#include "game/scene.h"
#include "game/sound.h"
#include "game/video_screen.h"
#include "game/heap.h"
#include "game/menu_screen.h"
#include "game/movie.h"

/*
 * VideoScreen (include/game/scene.h): the MenuScreen that plays one STR video (vtable 0x8006E5F8).
 *
 * File boundaries: likely (docs/layout.md)
 */

/* The STR movie Movie_Create makes (src/game/movie.c, vtable g_movieVtbl). */
typedef struct ScreenMovieVtbl {
    u8 pad_00[0x04];
    void *(*delete_)();
    u8 pad_08[0x40 - 0x08];
    s32 (*open)();       /* 0x40 (movie, path, frameCount, a, b): non-zero when it fails */
    u8 pad_44[0x48 - 0x44];
    s32 (*poll)();       /* 0x48 non-zero once the video has ended */
    void (*stop)();      /* 0x4C */
    u8 pad_50[0x6C - 0x50];
    void (*setUnk68)();  /* 0x6C */
} ScreenMovieVtbl;

typedef struct ScreenMovie {
    ScreenMovieVtbl *vtbl;
} ScreenMovie;

static ScreenVtbl *VideoScreen_GetVtbl(void);

extern ScreenVtbl g_videoScreenVtbl[]; /* VideoScreen */

/* VideoScreen */

VideoScreen *VideoScreen_New(MenuDef *menu, char *soundPath, SoundBank *sound, ScreenRect *area) {
    VideoScreen *video;

    video = Heap_Alloc(0xDC);
    if (video != NULL) {
        VideoScreen_GetVtbl()->init(video, menu, soundPath, sound, area);
        return video;
    }
    return NULL;
}

void VideoScreen_Init(VideoScreen *video, MenuDef *menu, char *soundPath, SoundBank *sound, ScreenRect *area) {
    MenuScreen_GetVtbl()->init(video, menu, soundPath, sound);
    video->vtbl = VideoScreen_GetVtbl();
    if (area != NULL) {
        video->area = *area;
    } else {
        video->area = *MenuScreen_GetPictureRect();
    }
    video->movie = Movie_Create(MenuScreen_GetPictureRect(), 0, 0);
    video->path = NULL;
    video->vtbl->reset(video);
}

void VideoScreen_Destroy(VideoScreen *video) {
    ScreenMovie *movie = video->movie;
    movie->vtbl->delete_(movie);
    MenuScreen_GetVtbl()->destroy(video);
}

void VideoScreen_Reset(VideoScreen *video) {
    video->movieLoops = -1;
    video->movieRepeat = 0;
    video->skippable = 1;
    video->unkD0 = 0;
    video->unkD4 = 1;
}

/* Slot 0x44: plays path until it ends, CIRCLE skips it (when skippable) or the timeout runs out. */
void VideoScreen_Play(VideoScreen *video, ScreenEnv *env, char *path, s32 frameCount, s32 arg4) {
    video->path = path;
    video->frameCount = frameCount;
    video->unkC0 = arg4;
    MenuScreen_GetVtbl()->run(video, env, 0);
}

void VideoScreen_Begin(VideoScreen *video) {
    ScreenMovie *movie;

    MenuScreen_GetVtbl()->begin(video);
    movie = video->movie;
    video->finished = 0;
    movie->vtbl->setUnk68(movie, video->unkC0);
    if (video->movie->vtbl->open(video->movie, video->path, video->frameCount, video->movieRepeat, video->movieLoops) != 0) {
        /* the video does not open: time out at once */
        video->vtbl->setTimeout(video, 0);
    }
}

void VideoScreen_OnClock(VideoScreen *video, Clock *clock, s32 message) {
    ScreenMovie *movie;
    s32 finished;

    MenuScreen_GetVtbl()->onClock(video, clock, message);
    if (video->finished == 0) {
        movie = video->movie;
        finished = movie->vtbl->poll(movie);
        video->finished = finished;
        if ((finished != 0) && (video->closing == 0)) {
            video->vtbl->setState(video, SCREEN_CLOSING);
        }
    }
}

void VideoScreen_SetState(VideoScreen *video, s32 state) {
    MenuScreen_GetVtbl()->setState(video, state);
    switch (state) {
    case SCREEN_ACTIVE:
        video->closing = 0;
        break;
    case SCREEN_CLOSING:
        video->closing = 1;
        break;
    case SCREEN_CLOSED:
        if (video->unkD4 == 0) {
            video->movie->vtbl->stop(video->movie);
        }
        break;
    case SCREEN_SKIP:
        video->vtbl->close(video);
        break;
    }
}

/* 15 ticks per second here, 20 in MenuScreen_SetTimeout */
void VideoScreen_SetTimeout(VideoScreen *video, s32 seconds) {
    video->timeout = seconds;
    if (seconds >= 0) {
        video->timeout = seconds * 15;
    }
}

void VideoScreen_OnCircle(VideoScreen *video) {
    MenuScreen_GetVtbl()->onCircle(video);
    if (video->skippable != 0) {
        video->result = 2;
        video->vtbl->setState(video, SCREEN_SKIP);
    }
}

void VideoScreen_OnUp(VideoScreen *video) {
    MenuScreen_GetVtbl()->onUp(video);
}

void VideoScreen_OnDown(VideoScreen *video) {
    MenuScreen_GetVtbl()->onDown(video);
}

void VideoScreen_EmptySlot88(void) {
}

void VideoScreen_EmptySlot8C(void) {
}

void VideoScreen_Close(VideoScreen *video) {
    if (video->unkD4 != 0) {
        video->movie->vtbl->stop(video->movie);
        return;
    }
    video->vtbl->setState(video, SCREEN_CLOSING);
}

void VideoScreen_SetMovieRepeat(VideoScreen *video, s32 value) {
    video->movieRepeat = value;
}

void VideoScreen_SetMovieLoops(VideoScreen *video, s32 value) {
    video->movieLoops = value;
}

void VideoScreen_SetSkippable(VideoScreen *video, s32 skippable) {
    video->skippable = skippable;
}

void func_8003BE74(VideoScreen *video, s32 value) {
    video->unkD0 = value;
}

void VideoScreen_SetCloseAtOnce(VideoScreen *video, s32 value) {
    video->unkD4 = value;
}

static ScreenVtbl *VideoScreen_GetVtbl(void) {
    return g_videoScreenVtbl;
}
