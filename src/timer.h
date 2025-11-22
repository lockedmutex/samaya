#pragma once

#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>
#include <glib.h>

typedef struct {
    GMutex timerMutex;

    bool isRunning;

    // MS suffix means Milli Seconds and US means micro Seconds.
    gint64 initialTimeMS;
    gint64 remainingTimeMS;
    gint64 lastUpdatedTimeUS;
    gfloat timerProgress;
    GString *formattedTime;
    gboolean completionAudioPlayed;

    GThread *timerThread;
    guint tickIntervalMS;

    // gpointer should be typecasted to Timer.
    void (*update_time_string) (gpointer timer, GString *timeString);

    // Callback to function that plays completion sound.
    void (*play_completion_sound)(void);

    // Callback to function that will be executed on completion of the set timer.
    void (*on_finished)(void);

} Timer;

Timer* init_timer(float duration_minutes,
                  void (*play_completion_sound)(void),
                  void (*on_finished)(void));

void timer_start(Timer *timer);
void timer_pause(Timer *timer);
void timer_resume(Timer *timer);
void timer_reset(Timer *timer);

void deinit_timer(Timer *timer);

void set_initialTimeMS(gint64 initialTimeMS);
void decrement_remaining_time_ms(Timer *timer, gint64 elapsedTimeMS);
void set_remainingTimeMS(gint64 remainingTimeMS);
void set_lastUpdateTimeUS(gint64 lastUpdateTimeUS);
gfloat get_timerProgress(Timer *timer);
void set_timerProgress(gfloat timerProgress);
void set_completionAudioPlayed(bool completionAudioPlayed);

void lock_timer(Timer *timer);
void unlock_timer(Timer *timer);

void format_time (GString *inputString, gint64 timeMS);

#endif