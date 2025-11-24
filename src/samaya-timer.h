/* samaya-timer.h
 *
 * Copyright 2025 Suyog Tandel
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include <stdbool.h>
#include <glib.h>
#include <gsound-context.h>

typedef struct
{
	GMutex timer_mutex;
	GCond timer_cond;

	gboolean is_running;
	gboolean end_worker;

	// ms suffix means Milli Seconds and us means micro Seconds.
	gint64 initial_time_ms;
	gint64 remaining_time_ms;
	gint64 last_updated_time_us;
	gfloat timer_progress;
	GString *remaining_time_minutes_string;

	GThread *worker_thread;
	guint tick_interval_ms;

	// CallBack API to react on every second tick.
	void (*timer_tick_callback)(void);

	// Callback to function that will be executed on completion of the set timer.
	void (*timer_completion_callback)(void);
} Timer;


Timer *get_active_timer(void);

Timer *init_timer(float duration_minutes,
                  void (*on_finished)(void),
                  void (*timer_tick_callback)(void));

void timer_start(Timer *timer);

void timer_pause(Timer *timer);

void timer_resume(Timer *timer);

void timer_reset(Timer *timer);

void deinit_timer(Timer *timer);

void lock_timer(Timer *timer);

void unlock_timer(Timer *timer);

void decrement_remaining_time_ms(Timer *timer, gint64 elapsed_time_ms);

void update_timer_string_and_run_tick_callback(Timer *timer);

gboolean get_is_timer_running(Timer *timer);

gfloat get_timer_progress(Timer *timer);

gchar *get_time_str(Timer *timer);

void set_timer_initial_time_minutes(Timer *timer, gfloat initial_time_minutes);

void set_timer_thread(Timer *timer, GThread *timer_thread);


