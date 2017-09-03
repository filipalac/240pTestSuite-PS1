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

#include<psx.h>
#include<stdio.h>
#include<stdlib.h>

#include"240p.h"
#include"sg_string.h"
#include"textures.h"

#include"lz4.h"

void load_custom_font()
{
	char data_buffer[4160];
	const void *ptr;

	ptr = font_array + 8;

	GsImage image;

	LZ4_decompress_fast(ptr, data_buffer, 4160);
	GsImageFromTim(&image, data_buffer);
	GsUploadImage(&image);
}

void draw_Vfont(char shadow, short x, short y, unsigned char r, unsigned char g, unsigned char b, char *fmt, va_list ap)
{
	GsSprite spr;
	char stringbuf[512];
	char *string;
	
	spr.x = x; spr.y = y;
	spr.r = r; spr.g = g; spr.b = b;
	spr.attribute = COLORMODE(COLORMODE_4BPP);
	spr.mx = spr.my = spr.rotate = spr.scalex = spr.scaley = 0;
	spr.cx = 960; spr.cy = 321;
	spr.tpage = 31;
	spr.w = 6; spr.h = 8;

	sg_vsprintf(stringbuf, fmt, ap); //standard vsnprintf is slow
	string = stringbuf;

	while (*string) {
		if (*string >= 32 && *string <= 127) { //check if printable
			spr.u = ((*string - 32) - ((*string - 32) / 16) * 16) * 6; //charoffset == *string - 32
			spr.v = (*string - 32) / 16 * 8;

			if (shadow) {
				spr.x++;
				spr.y++;
				spr.r = spr.g = spr.b = 0;
				GsSortSprite(&spr);
				spr.x--;
				spr.y--;
				spr.r = r; spr.g = g; spr.b = b;
			}

			GsSortSprite(&spr);

			spr.x += 5;
		}

		if (*string == '\r')
			spr.x = 0;
		else if (*string == '\n') {
			spr.x = x;
			spr.y += spr.h;
		}
		else if (*string == '\t')
			spr.x += spr.w * 8;
		string++;
	}
}

void draw_menu_font(char shadow, int count, int order, short x, short y, char *menu_name, ...)
{
	va_list ap;
	va_start(ap, menu_name);

	if (count == order) {
		draw_Vfont(shadow, x, y, 255, 0, 0, menu_name, ap);
	} else {
		draw_Vfont(shadow, x, y, 255, 255, 255, menu_name, ap);
	}

	va_end(ap);
}

void draw_font(char shadow, short x, short y, unsigned char r, unsigned char g, unsigned char b, char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	draw_Vfont(shadow, x, y, r, g, b, fmt, ap);
	va_end(ap);
}

void load_numbers()
{
	char data_buffer[8256];
	const void *ptr;

	ptr = numbers_array + 8;

	GsImage image;

	LZ4_decompress_fast(ptr, data_buffer, 8256);
	GsImageFromTim(&image, data_buffer);
	GsUploadImage(&image);
}

void draw_number(short x, short y, unsigned char r, unsigned char g, unsigned char b, char fmt)
{
	GsSprite spr;
	
	spr.x = x; spr.y = y;
	spr.r = r; spr.g = g; spr.b = b;
	spr.attribute = COLORMODE(COLORMODE_4BPP);
	spr.mx = spr.my = spr.rotate = spr.scalex = spr.scaley = 0;
	spr.cx = 912; spr.cy = 484;
	spr.tpage = 10;
	spr.w = 24; spr.h = 40;

	if (fmt >= 0 && fmt <= 10) {
		spr.u = (fmt - (fmt / 5) * 5) * 24;
		spr.v = fmt / 5 * 40;

		GsSortSprite(&spr);

		spr.x += 24;
	}
}
