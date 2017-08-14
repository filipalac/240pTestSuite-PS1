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

void load_custom_font();
void draw_Vfont(char shadow, short x, short y, unsigned char r, unsigned char g, unsigned char b, char *fmt, va_list ap);
void draw_menu_font(char shadow, int count, int order, short x, short y, char *menu_name, ...);
void draw_font(char shadow, short x, short y, unsigned char r, unsigned char g, unsigned char b, char *fmt, ...);
void draw_char(char shadow, short x, short y, unsigned char r, unsigned char g, unsigned char b, char fmt);
void load_numbers();
void draw_number(short x, short y, unsigned char r, unsigned char g, unsigned char b, char fmt);
