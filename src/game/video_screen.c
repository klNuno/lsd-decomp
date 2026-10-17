#include "common.h"
#include "game/video_screen.h"
#include "game/heap.h"
#include "game/display.h"
#include "game/sound_bank.h"
#include "game/menu_screen.h"
#include "game/screen.h"
#include "game/clock.h"
#include "game/movie.h"

/*
 * VideoScreen (include/game/video_screen.h): the MenuScreen that plays one STR video (vtable 0x8006E5F8).
 *
 * File boundaries: likely (docs/layout.md)
 */

static ScreenVtbl *VideoScreen_GetVtbl(void);

extern ScreenVtbl g_videoScreenVtbl[]; /* VideoScreen */

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
    video->menuScreen.vtbl = VideoScreen_GetVtbl();
    if (area != NULL) {
        video->area = *area;
    } else {
        video->area = *MenuScreen_GetPictureRect();
    }
    video->movie = Movie_Create(MenuScreen_GetPictureRect(), 0, 0);
    video->path = NULL;
    video->menuScreen.vtbl->reset(video);
}

void VideoScreen_Destroy(VideoScreen *video) {
    Movie *movie = video->movie;
    movie->vtbl->delete_(movie);
    MenuScreen_GetVtbl()->destroy(video);
}

void VideoScreen_Reset(VideoScreen *video) {
    video->movieLoops = -1;
    video->movieRepeat = 0;
    video->skippable = 1;
    video->unkD0 = 0;
    video->closeAtOnce = 1;
}

/* Slot 0x44: plays path until it ends, CIRCLE skips it (when skippable) or the timeout runs out. */
void VideoScreen_Play(VideoScreen *video, ScreenEnv *env, char *path, s32 frameCount, s32 autoStart) {
    video->path = path;
    video->frameCount = frameCount;
    video->autoStart = autoStart;
    MenuScreen_GetVtbl()->run(video, env, 0);
}

void VideoScreen_Begin(VideoScreen *video) {
    Movie *movie;

    MenuScreen_GetVtbl()->begin(video);
    movie = video->movie;
    video->finished = 0;
    movie->vtbl->setAutoStart(movie, video->autoStart);
    if (video->movie->vtbl->open(video->movie, video->path, video->frameCount, video->movieRepeat, video->movieLoops) != 0) {
        /* the video does not open: time out at once */
        video->menuScreen.vtbl->setTimeout(video, 0);
    }
}

void VideoScreen_OnClock(VideoScreen *video, Clock *clock, s32 message) {
    Movie *movie;
    s32 finished;

    MenuScreen_GetVtbl()->onClock(video, clock, message);
    if (video->finished == 0) {
        movie = video->movie;
        finished = movie->vtbl->update(movie);
        video->finished = finished;
        if ((finished != 0) && (video->closing == 0)) {
            video->menuScreen.vtbl->setState(video, SCREEN_CLOSING);
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
        if (video->closeAtOnce == 0) {
            video->movie->vtbl->stop(video->movie);
        }
        break;
    case SCREEN_SKIP:
        video->menuScreen.vtbl->close(video);
        break;
    }
}

/* 15 ticks per second here, 20 in MenuScreen_SetTimeout */
void VideoScreen_SetTimeout(VideoScreen *video, s32 seconds) {
    video->menuScreen.timeout = seconds;
    if (seconds >= 0) {
        video->menuScreen.timeout = seconds * 15;
    }
}

void VideoScreen_OnCircle(VideoScreen *video) {
    MenuScreen_GetVtbl()->onCircle(video);
    if (video->skippable != 0) {
        video->menuScreen.result = 2;
        video->menuScreen.vtbl->setState(video, SCREEN_SKIP);
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
    if (video->closeAtOnce != 0) {
        video->movie->vtbl->stop(video->movie);
        return;
    }
    video->menuScreen.vtbl->setState(video, SCREEN_CLOSING);
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
    video->closeAtOnce = value;
}

static ScreenVtbl *VideoScreen_GetVtbl(void) {
    return g_videoScreenVtbl;
}
