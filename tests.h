/*
 * 240p test suite
 * Copyright 2017 Filip Aláč(PS1)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

void grid_scroll_test();
void backlight_zone();
void horizontal_stripes();
void checkerboard();
void scroll_test();
void striped_test(char drop_shadow);  //drop_shadow == 1 drop_shadow drop_shadow == 0 striped_test
void sound_test();
void passive_lag_test();
void lag_test();
void alternate_240p480i();
void audio_sync_test();
