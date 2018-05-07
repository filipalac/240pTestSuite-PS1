/*
 * 240p test suite
 * Copyright 2017-2018 Filip Aláč(PS1)
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
#include<psxspu.h>

#include<stdio.h>
#include<stdlib.h>

#include"240p.h"
#include"help.h"
#include"font.h"
#include"textures.h"

#define YTOP224 (y_res == 224 ? 8 : 0)

void grid_scroll_test()
{
	int speed = 1;
	char vertical = 1;

	GsImage imagegrid;
	GsSprite grid;

	upload_sprite(&imagegrid, &grid, &lingrid_array);

	while (1) {
		if (display_is_old) {
		set_screen(x_res, 240, VMODE, interlaced);
		GsSortCls(0, 0, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_VSCROLL);
			break;
		case PAD_CROSS:
			vertical = !vertical;
			break;
		case PAD_CIRCLE:
			speed *= - 1;
			break;
		case PAD_SQUARE:
			speed = 0;
			break;
		case PAD_LEFT:
			if (speed > - 4)
				speed--;
			break;
		case PAD_RIGHT:
			if (speed < 4)
				speed++;
			break;
		}

		if (vertical) {
			grid.x = 0;
			grid.v += speed;
			GsSortSprite(&grid);
			grid.x = 160;
			GsSortSprite(&grid);
		} else {
			grid.x += speed;
			if (grid.x > 0 || grid.x < - 16)
				grid.x = speed - 8;
			GsSortSprite(&grid);
			grid.x += 160;
			GsSortSprite(&grid);
			grid.x -= 160;
		}

		draw_list();
		}
	}
}

void backlight_zone()
{
	psx_pad_state padbuf;

	GsRectangle rectangle;
	rectangle.r = rectangle.g = rectangle.b = 255;
	rectangle.x = 10; rectangle.y = 10;
	rectangle.w = 1; rectangle.h = 1;
	rectangle.attribute = 0;

	while (1) {
		if (display_is_old) {
		set_screen(x_res, 240, VMODE, interlaced);
		GsSortCls(0, 0, 0);

		PSX_PollPad(0, &padbuf);
		if (padbuf.buttons & PAD_LEFT) rectangle.x > 0 ? rectangle.x-- : 0;
		if (padbuf.buttons & PAD_RIGHT) rectangle.x < x_res - rectangle.w ? rectangle.x++ : 0;
		if (padbuf.buttons & PAD_UP) rectangle.y > 0 + YTOP224 ? rectangle.y-- : 0;
		if (padbuf.buttons & PAD_DOWN) rectangle.y < y_res - rectangle.h + YTOP224 ? rectangle.y++ : 0;

		if (padbuf.type == 2 || padbuf.type == 3) {
			signed char current_pad_x = 0;
			signed char current_pad_y = 0;

			if (padbuf.type == 2) {
				current_pad_x = padbuf.extra.analogJoy.x[1];
				current_pad_y = padbuf.extra.analogJoy.y[1];
			} else {
				current_pad_x = padbuf.extra.analogPad.x[1];
				current_pad_y = padbuf.extra.analogPad.y[1];
			}

			if (rectangle.x >= 0 && rectangle.x <= x_res - rectangle.w)
				rectangle.x += current_pad_x / 24;

			if (rectangle.y >= 0 + YTOP224 && rectangle.y <= y_res - rectangle.h + YTOP224)
				rectangle.y += current_pad_y / 24;

			if (rectangle.x > x_res - rectangle.w)
				rectangle.x = x_res - rectangle.w;

			if (rectangle.y > y_res - rectangle.h + YTOP224)
				rectangle.y = y_res - rectangle.h + YTOP224;

			if (rectangle.x < 0)
				rectangle.x = 0;

			if (rectangle.y < 0 + YTOP224)
				rectangle.y = 0 + YTOP224;
		}

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_BACKLIT);
			break;
		case PAD_CROSS:
			if (rectangle.w < 25)
				rectangle.w = rectangle.h *= 2;
			else
			       	rectangle.w = rectangle.h = 1;
			break;
		case PAD_CIRCLE:
			if (rectangle.r == 255)
				rectangle.r = rectangle.g = rectangle.b = 0;
			else rectangle.r = rectangle.g = rectangle.b = 255;
			break;
		}

		GsSortRectangle(&rectangle);

		draw_list();
		}
	}
}

void horizontal_stripes()
{
	char alternating = 0;
	char even = 1;
	char vertical = 0;
	int frame_counter = 0;
	int frame = 0;
	int frame_time = 90;
	unsigned short x_res_tmp = x_res;
	char x_res_cnt = x_res == 256 ? 0 : 1;


	GsLine line;
	line.r = line.g = line.b = 255;
	line.x[0] = 0; line.y[0] = 0;
	line.x[1] = 320; line.y[1] = 0;

	GsRectangle box;
	box.r = box.g = box.b = 1;
	box.attribute = ENABLE_TRANS | TRANS_MODE(0);

	while (1) {
		if (display_is_old) {
		set_screen(x_res_tmp, 240, VMODE, interlaced);
		GsSortCls(0, 0, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_STRIPES);
			break;
		case PAD_CROSS:
			alternating = !alternating;
			break;
		case PAD_CIRCLE:
			even = !even;
			break;
		case PAD_SQUARE:
			frame_counter = !frame_counter;
			break;
		case PAD_UP:
			vertical = !vertical;
			break;
		case PAD_LEFT:
			frame_time = 90;
			x_res_cnt--;
			if (x_res_cnt < 0)
				x_res_cnt = 3;
			break;
		case PAD_RIGHT:
			frame_time = 90;
			x_res_cnt++;
			if (x_res_cnt > 3)
				x_res_cnt = 0;
			break;
		}

		switch (x_res_cnt) {
		case 0:
			x_res_tmp = 256;
			break;
		case 1:
		       	x_res_tmp = 320;
			break;
		case 2:
			x_res_tmp = 384;
			break;
		case 3:
			x_res_tmp = 640;
			break;
		}


		if (alternating)
			even = !even;

		if (!vertical) {
			line.x[0] = 0;
			line.x[1] = x_res_tmp;
			for (unsigned short i = 0; i < y_res; i++) {
				if (even) {
					if (!(i % 2)) {
						line.y[0] = line.y[1] = i;
						GsSortLine(&line);
					}
				} else if (i % 2) {
					line.y[0] = line.y[1] = i;
					GsSortLine(&line);
				}
			}
		} else {
			line.y[0] = 0;
			line.y[1] = y_res;
			for (unsigned short i = 0; i < x_res_tmp; i++) {
				if (even) {
					if (!(i % 2)) {
						line.x[0] = line.x[1] = i;
						GsSortLine(&line);
					}
				} else if (i % 2) {
					line.x[0] = line.x[1] = i;
					GsSortLine(&line);
				}
			}
		}

		if (frame_counter) {
			frame++;
			if (GsScreenM == VMODE_NTSC && frame > 59)
				frame = 0;
			else if (GsScreenM  == VMODE_PAL && frame > 49)
				frame = 0;

			box.x = x_res_tmp * 0.0625 - 1; box.y = y_res - 30;
			box.w = x_res_tmp == 640 ? 47 * 2 : 47 ; box.h = 8;

			if (x_res_tmp == 640)
				set_font_scale(SCALE_ONE * 2, 0);

			GsSortRectangle(&box);
			draw_font(0, x_res_tmp * 0.0625, y_res - 30, 255, 255, 255, "frame: %d", frame);
			set_font_scale(0, 0);
		}

		if (frame_time > 0) {
			box.x = x_res_tmp * 0.75 - 1; box.y = 20;
			box.w = x_res_tmp == 640 ? 37 * 2 : 37 ; box.h = 8;

			if (x_res_tmp == 640)
				set_font_scale(SCALE_ONE * 2, 0);

			GsSortRectangle(&box);
			draw_font(0, x_res_tmp * 0.75, 20, 0, 255, 0, "%dx%d", x_res_tmp, y_res);
			set_font_scale(0, 0);
	       		frame_time--;
		}

		draw_list();
		}
	}
}

void checkerboard()
{
	char alternating = 0;
	char even = 1;
	char frame_counter = 0;
	int frame = 0;
	int frame_time = 90;
	unsigned short x_res_tmp = x_res;
	char x_res_cnt = x_res == 256 ? 0 : 1;

	GsImage image;
	GsSprite sprite;

	upload_sprite(&image, &sprite, &checkerboard_array);

	GsRectangle box;
	box.r = box.g = box.b = 1;
	box.attribute = ENABLE_TRANS | TRANS_MODE(0);

	while (1) {
		if (display_is_old) {
		set_screen(x_res_tmp, 240, VMODE, interlaced);
		GsSortCls(0, 0, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_CHECK);
			break;
		case PAD_CROSS:
			alternating = !alternating;
			break;
		case PAD_CIRCLE:
			even = !even;
			break;
		case PAD_SQUARE:
			frame_counter = !frame_counter;
			break;
		case PAD_LEFT:
			frame_time = 90;
			x_res_cnt--;
			if (x_res_cnt < 0)
				x_res_cnt = 3;
			break;
		case PAD_RIGHT:
			frame_time = 90;
			x_res_cnt++;
			if (x_res_cnt > 3)
				x_res_cnt = 0;
			break;
		}

		switch (x_res_cnt) {
		case 0:
			x_res_tmp = 256;
			break;
		case 1:
		       	x_res_tmp = 320;
			break;
		case 2:
			x_res_tmp = 384;
			break;
		case 3:
			x_res_tmp = 640;
			break;
		}

		if (alternating)
			even = !even;

		for (unsigned short i = 0; i < x_res_tmp; i += 80) {
			for (unsigned short j = 0; j < y_res; j += 120) {
				sprite.x = i;
				sprite.y = j + even;
				GsSortSprite(&sprite);
			}
		}

		if (frame_counter) {
			frame++;
			if (GsScreenM == VMODE_NTSC && frame > 59)
				frame = 0;
			else if (GsScreenM == VMODE_PAL && frame > 49)
				frame = 0;

			box.x = x_res_tmp * 0.0625 - 1; box.y = y_res - 30;
			box.w = x_res_tmp == 640 ? 47 * 2 : 47 ; box.h = 8;

			if (x_res_tmp == 640)
				set_font_scale(SCALE_ONE * 2, 0);

			GsSortRectangle(&box);
			draw_font(0, x_res_tmp * 0.0625, y_res - 30, 255, 255, 255, "frame: %d", frame);
			set_font_scale(0, 0);
		}

		if (frame_time > 0) {
			box.x = x_res_tmp * 0.75 - 1; box.y = 20;
			box.w = x_res_tmp == 640 ? 37 * 2 : 37 ; box.h = 8;

			if (x_res_tmp == 640)
				set_font_scale(SCALE_ONE * 2, 0);

			GsSortRectangle(&box);
			draw_font(0, x_res_tmp * 0.75, 20, 0, 255, 0, "%dx%d", x_res_tmp, y_res);
	       		frame_time--;
			set_font_scale(0, 0);
		}

		draw_list();
		}
	}
}

void scroll_test()
{
	char vertical = 0;
	int i = 0;
	int speed = 1;

	GsImage image;
	GsSprite sonicsky, back[4], floor, kiki;

	upload_sprite(&image, &sonicsky, &sonicsky_array);
	upload_sprite(&image, &back[0], &sonicback1_array);
	upload_sprite(&image, &back[1], &sonicback2_array);
	upload_sprite(&image, &back[2], &sonicback3_array);
	upload_sprite(&image, &back[3], &sonicback4_array);
	upload_sprite(&image, &floor, &sonicfloor_array);
	upload_sprite(&image, &kiki, &kiki_array);

	kiki.h = kiki.w = 256;
	kiki.x = x_res == 256 ? 0 : 32;

	while (1) {
		if (display_is_old) {
		set_screen(x_res, 240, VMODE, interlaced);
		GsSortCls(0, 0, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_HSCROLL);
			break;
		case PAD_CROSS:
			vertical = !vertical;
			i = 0;
			break;
		case PAD_CIRCLE:
			speed *= - 1;
			break;
		case PAD_SQUARE:
			speed = 0;
			break;
		case PAD_LEFT:
			if (speed > - 22)
				speed--;
			break;
		case PAD_RIGHT:
			if (speed < 22)
				speed++;
			break;
		}

		if (!vertical) {
			i++;
			if (i > 119)
				i = 0;


			back[0].y = back[1].y = back[2].y = back[3].y = 128;
			back[i/30].x = sonicsky.x = 0;
			back[0].u = back[1].u = back[2].u = back[3].u = sonicsky.u += speed;
			GsSortSprite(&back[i/30]);
			GsSortSprite(&sonicsky);
			back[i/30].x = sonicsky.x = 256;
			GsSortSprite(&back[i/30]);
			GsSortSprite(&sonicsky);

			floor.w = floor.h = 256;
			floor.x = 0;
			floor.y = y_res == 224 ? 112 : 128;
			floor.u += 2 * speed;
			GsSortSprite(&floor);
			floor.x = 256;
			GsSortSprite(&floor);
		} else {
			i += speed;
			if (abs(i) >= 512)
				i = 0;

			kiki.tpage = 11;
			kiki.y = - 512 + i;
			GsSortSprite(&kiki);
			kiki.tpage = 27;
			kiki.y = - 256 + i;
			GsSortSprite(&kiki);
			kiki.tpage = 11;
			kiki.y = + i;
			GsSortSprite(&kiki);
			kiki.tpage = 27;
			kiki.y = i + 256;
			GsSortSprite(&kiki);
			kiki.tpage = 11;
			kiki.y = i + 512;
			GsSortSprite(&kiki);
		}

		draw_list();
		}
	}
}

void striped_test(char drop_shadow)
{
	psx_pad_state padbuf;
	signed char current_pad_x = 0;
	signed char current_pad_y = 0;
	unsigned char sonic_timer = 0;
	char orientation = 0;
	char background = 0;
	char image_uploaded = 0;
	char cursor = 0;
	char even = 0;

	GsImage  image;
	GsSprite motoko, striped, sonicsky, back[4], floor, check, shadow, buzzbomber, buzzbombershadow;

	upload_sprite(&image, &striped, &striped_array);
	if (drop_shadow) {
		upload_sprite(&image, &shadow, &shadow_array);
		upload_sprite(&image, &buzzbomber, &buzzbomber_array);
		upload_sprite(&image, &buzzbombershadow, &buzzbombershadow_array);
	}

	upload_sprite(&image, &sonicsky, &sonicsky_array);
	upload_sprite(&image, &back[0], &sonicback1_array);
	upload_sprite(&image, &back[1], &sonicback2_array);
	upload_sprite(&image, &back[2], &sonicback3_array);
	upload_sprite(&image, &back[3], &sonicback4_array);

	upload_sprite(&image, &motoko, &motoko_array);

	striped.x = striped.y = 8;

	GsLine line;
	line.r = line.g = line.b = 255;

	while (1) {
		if (display_is_old) {
		set_screen(x_res, 240, VMODE, interlaced);
		GsSortCls(0, 0, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			if (drop_shadow)
				draw_help(HELP_SHADOW);
			else
				draw_help(HELP_STRIPED);
			break;
		case PAD_CROSS:
			image_uploaded = 0;
			if (background != 3)
				background++;
			else
				background = 0;
			break;
		case PAD_SQUARE:
			cursor = !cursor;
			break;
		case PAD_CIRCLE:
			even = !even;
			break;
		}

		PSX_PollPad(0, &padbuf);
		if (padbuf.buttons & PAD_LEFT) striped.x > 0 ? striped.x-- : 0;
		if (padbuf.buttons & PAD_RIGHT) striped.x < x_res - striped.w ? striped.x++ : 0;
		if (padbuf.buttons & PAD_UP) striped.y > 0 + YTOP224 ? striped.y-- : 0;
		if (padbuf.buttons & PAD_DOWN) striped.y < y_res - striped.h + YTOP224 ? striped.y++ : 0;

		if (padbuf.type == 2 || padbuf.type == 3) {
			if (padbuf.type == 2) {
				current_pad_x = padbuf.extra.analogJoy.x[1];
				current_pad_y = padbuf.extra.analogJoy.y[1];
			} else {
				current_pad_x = padbuf.extra.analogPad.x[1];
				current_pad_y = padbuf.extra.analogPad.y[1];
			}

			if (striped.x >= 0 && striped.x <= x_res - striped.w)
				striped.x += current_pad_x / 24;

			if (striped.y >= 0 + YTOP224 && striped.y <= y_res - striped.h + YTOP224)
				striped.y += current_pad_y / 24;

			if (striped.x > x_res - striped.w)
				striped.x = x_res - striped.w;

			if (striped.y > y_res - striped.h + YTOP224)
				striped.y = y_res - striped.h + YTOP224;

			if (striped.x < 0)
				striped.x = 0;

			if (striped.y < 0 + YTOP224)
				striped.y = 0 + YTOP224;
		}

		switch (background) {
		case 0:
			if (!image_uploaded) {  // This control is needed because it is in loop
				upload_sprite(&image, &motoko, &motoko_array);
				image_uploaded = 1;
			}
			GsSortCls(255, 255, 255);

			motoko.y = y_res == 224 ? - 8 : 0;
			motoko.scalex = x_res == 256 ? 3276 : 0;
			motoko.x = 0;
			motoko.w = 255;
			motoko.tpage = 12;
			motoko.attribute = COLORMODE(COLORMODE_8BPP);
			GsSortSprite(&motoko);
			motoko.x = x_res == 256 ? 203 : 255;
			motoko.w = 64;
			motoko.tpage = 14;
			GsSortSprite(&motoko);
			break;
		case 1:
			line.x[0] = 0; line.y[0] = 0;
			line.x[1] = 320; line.y[1] = 0;
			for (unsigned short i = 0; i < x_res; i++) {
				if (!(i % 2)) {
					line.y[0] = line.y[1] = i;
					GsSortLine(&line);
				}
			}
			break;
		case 2:
			if (!image_uploaded) {
				upload_sprite(&image, &check, &checkerboard_array);
				image_uploaded = 1;
			}
			for (unsigned short i = 0; i < x_res; i += 80) {
				for (unsigned short j = 0; j < y_res; j += 120) {
					check.x = i;
					check.y = j;
					GsSortSprite(&check);
				}
			}
			break;
		case 3:
			if (!image_uploaded) {
				upload_sprite(&image, &floor, &sonicfloor_array);
				upload_sprite(&image, &back[0], &sonicback1_array);
				upload_sprite(&image, &back[1], &sonicback2_array);
				upload_sprite(&image, &back[2], &sonicback3_array);
				upload_sprite(&image, &back[3], &sonicback4_array);
				image_uploaded = 1;
			}
			sonic_timer++;
			if (sonic_timer > 119)
				sonic_timer = 0;

			back[0].y = back[1].y = back[2].y = back[3].y = 128;
			back[sonic_timer/30].x = sonicsky.x = 0;
			back[0].u = back[1].u = back[2].u = back[3].u = sonicsky.u = striped.x;
			GsSortSprite(&back[sonic_timer/30]);
			GsSortSprite(&sonicsky);
			back[sonic_timer/30].x = sonicsky.x = 256;
			GsSortSprite(&back[sonic_timer/30]);
			GsSortSprite(&sonicsky);

			floor.x = 0;
			floor.y = y_res == 224 ? 112 : 128;
			floor.u = 2 * striped.x;
			GsSortSprite(&floor);
			floor.x = 256;
			GsSortSprite(&floor);
			break;
		}

		if (!drop_shadow)
			GsSortSprite(&striped);
		else {
			even = !even;
			shadow.x = buzzbomber.x = striped.x;
			shadow.y = buzzbomber.y = striped.y;
			switch (cursor) {
			case 0:
				if (even)
					GsSortSprite(&shadow);
				break;
			case 1:
				if ((padbuf.buttons & PAD_LEFT && orientation)
					|| ( current_pad_x <= - 24 && orientation)) {

				       	buzzbomber.attribute = buzzbombershadow.attribute = 0;
					orientation = !orientation;
				}
				else if ((padbuf.buttons & PAD_RIGHT && !orientation)
					|| ( current_pad_x >= 24 && !orientation)) {

				       	buzzbomber.attribute = buzzbombershadow.attribute = H_FLIP;
					orientation = !orientation;
				}
				GsSortSprite(&buzzbomber);
				if (even) {
					buzzbombershadow.x = buzzbomber.x + 20;
					buzzbombershadow.y = buzzbomber.y + 20;
					GsSortSprite(&buzzbombershadow);
				}
				break;
			}
		}

		draw_list();
		}
	}
}

void sound_test()
{
	int cnt = 0;

	SsVoiceStartAddr(0, SPU_DATA_BASE_ADDR);
	SsVoicePitch(0, 0x1000 / (44100 / 16000));

	while (1) {
		if (display_is_old) {
		set_screen(x_res, 240, VMODE, interlaced);
		GsSortCls(0, 0, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_SOUND);
			break;
		case PAD_LEFT:
			if (cnt >= 0)
				cnt--;
			if (cnt < 0)
				cnt = 2;
			break;
		case PAD_RIGHT:
			if (cnt <= 2)
				cnt++;
			if (cnt > 2)
				cnt = 0;
			break;
		case PAD_CROSS:
			switch (cnt) {
				case 0:
					SsVoiceVol(0, 0x3fff, 0);
					SsKeyOn(0);
					break;
				case 1:
					SsVoiceVol(0, 0x3fff, 0x3fff);
					SsKeyOn(0);
					break;
				case 2:
					SsVoiceVol(0, 0, 0x3fff);
					SsKeyOn(0);
					break;
			}
			break;
		}

		draw_background();

		short center_x = x_res / 2;

		draw_font(1, center_x - 10 * 5 / 2, 60, 0, 255, 0, "Sound Test");
		draw_menu_font(1, cnt, 0, center_x - 12 * 5 / 2 - 50, 120, "Left Channel");
		draw_menu_font(1, cnt, 1, center_x - 14 * 5 / 2, 130, "Center Channel");
		draw_menu_font(1, cnt, 2, center_x - 13 * 5 / 2 + 50, 120, "Right Channel");

		draw_list();
		}
	}
}

void passive_lag_test()
{
	char circlecnt = 0;
	char frame = 0;
	char pause = 0;
	unsigned short i = 0;
	unsigned long seconds = 0;

	GsImage image;
	GsSprite circle;

	load_numbers();
	upload_sprite(&image, &circle, &circle_array);

	circle.scalex = SCALE_ONE / (x_res == 256 ? 1.25 : 1);

	while (1) {
		if (display_is_old) {
		set_screen(x_res, 240, VMODE, interlaced);
		GsSortCls(255, 255, 255);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_LAG);
			break;
		case PAD_CROSS:
			pause = !pause;
			break;
		case PAD_SQUARE:
			frame = 0;
			seconds = 0;
			circlecnt = 0;
			break;
		}

		if (!pause) {
			circlecnt++;
			if (circlecnt > 7)
				circlecnt = 0;
			frame++;
			if (GsScreenM == VMODE_NTSC && frame == 59) {
				frame = 0;
				seconds++;
			} else if (GsScreenM == VMODE_PAL && frame == 49) {
				frame = 0;
				seconds++;
			}
			if (seconds > 356400) //99 Hours
				seconds = 0;
		}

		draw_font(0, x_res == 256 ? 12 : 32, 8, 0, 0, 0, "hours");
		draw_font(0, x_res == 256 ? 74 : 104, 8, 0, 0, 0, "minutes");
		draw_font(0, x_res == 256 ? 136 : 176, 8, 0, 0, 0, "seconds");
		draw_font(0, x_res == 256 ? 196 : 248, 8, 0, 0, 0, "frames");

		//Draw counter separators
		draw_number(x_res == 256 ? 55 : 80, 16, 0, 0, 0, 10);  //10 == :
		draw_number(x_res == 256 ? 117 : 152, 16, 0, 0, 0, 10);
		draw_number(x_res == 256 ? 179 : 224, 16, 0, 0, 0, 10);

		//Draw Hours
		draw_number(x_res == 256 ? 12 : 32, 16, 0, 0, 0, (frame / 3600) % 60 / 10);
		draw_number(x_res == 256 ? 36 : 56, 16, 0, 0, 0, (frame / 3600) % 10);
		//Draw Minutes
		draw_number(x_res == 256 ? 74 : 104, 16, 0, 0, 0, (seconds / 60) % 60 / 10);
		draw_number(x_res == 256 ? 98 : 128, 16, 0, 0, 0, (seconds / 60) % 10);
		//Draw Seconds
		draw_number(x_res == 256 ? 136 : 176, 16, 0, 0, 0, (seconds % 60) / 10);
		draw_number(x_res == 256 ? 160 : 200, 16, 0, 0, 0, seconds % 10);
		//Draw Frames
		draw_number(x_res == 256 ? 198 : 248, 16, 0, 0, 0, frame / 10);
		draw_number(x_res == 256 ? 222 : 272, 16, 0, 0, 0, frame % 10);

		for (i = 0, circle.y = 56; circle.y <= 136; circle.y += 80) {
			for (circle.x = (x_res == 256 ? 8 : 16); circle.x <= (x_res == 256 ? 197 : 256); circle.x += (x_res == 256 ? 63 : 80), i++) {
				if (i == circlecnt) {
					circle.r = 255;
					circle.g = 0;
					circle.b = 0;
				} else {
					circle.r = 0;
					circle.g = 0;
					circle.b = 255;
				}
				GsSortSprite(&circle);
				draw_number(circle.x + 20 - (x_res == 256 ? 7 : 0), circle.y + 12, 255, 255, 255, i + 1);
			}
		}
		draw_list();
		}
	}
}

void lag_test()
{
	unsigned char pos = 0;
	char offset = 0;
	char speed = 1;
	char variation = 1;
	char clicks[10] = {99, 99, 99, 99, 99, 99, 99, 99, 99, 99};
	char sound = 1;
	char change = - 1;
	short total = 0;
	short var = 0;
	short view = 0;

	GsSprite lagper;
	GsImage imagelagper;

	upload_sprite(&imagelagper, &lagper, &lagper_array);

	SsVoiceStartAddr(0, SPU_DATA_BASE_ADDR);
	SsVoicePitch(0, 0x1000 / (44100 / 16000));
	SsVoiceVol(0, 0x3fff, 0x3fff);

	srand(*((unsigned int*)0x1F801100));

	while (1) {
		if (display_is_old) {
		set_screen(x_res, 240, VMODE, interlaced);
		GsSortCls(0, 0, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_MANUALLAG);
			break;
		case PAD_CROSS:
			clicks[pos] = change * offset;
			if (pos <= 9 && clicks[pos] >= 0) {
				total += clicks[pos];
				change *= - 1;
				pos++;
			}
			break;
		case PAD_SQUARE:
			view++;
			if (view > 2)
				view = 0;
			break;
		case PAD_CIRCLE:
			variation = !variation;
			break;
		case PAD_R1:
			sound = !sound;
			break;
		}

		lagper.r = 255; lagper.g = 255; lagper.b = 255;
		lagper.x = x_res / 2 - 16; lagper.y = 96;
		GsSortSprite(&lagper);

		if (offset > 36 + var || offset < - 36 - var) //Change direction
			speed *= - 1;
		offset += speed;

		if (speed < 0 && offset > 0)
			change = - 1;
		if (speed > 0 && offset < 0)
			change = 1;

		if (offset == 1 || offset == - 1) { //one pixel off
			lagper.r = 0; lagper.g = 255; lagper.b = 0;
		}

		else if (offset == 0) { //Zero pixel off
			if (sound)
				SsKeyOn(0);

			lagper.r = 255; lagper.g = 0; lagper.b = 0;
			if (variation) {
				if (rand() % 2)
					var = rand() % 7;
				else
					var = - 1 * rand() % 7;
			} else
				var = 0;
			if (pos != 10)
				GsSortCls(255, 255, 255);
		} else
			lagper.r = lagper.g = lagper.b = 255;

		if (view == 0) { //Y Axis only
			lagper.x = x_res / 2 - 16;
			lagper.y = 96 + offset;
			GsSortSprite(&lagper);
		}
		else if (view == 1) { //X Axis only
			lagper.x = x_res / 2 - 16 + offset;
			lagper.y = 96 ;
			GsSortSprite(&lagper);
		}
		else if (view == 2) { //Both Axis move
			lagper.x = x_res / 2 - 16;
			lagper.y = 96 + offset;
			GsSortSprite(&lagper);
			lagper.x = x_res / 2 - 16 + offset;
			lagper.y = 96;
			GsSortSprite(&lagper);
		}

		for (unsigned char i = 0; i <= pos && pos != 10; i++) { //draw top left table with offsets
			if (clicks[i] != 99) {
				draw_font(0, 8, i * 8 + 12, 0, 255, 255,"%d:", i);

				if (clicks[i] > 0)
					draw_font(0, 22, i * 8 + 12, 255, 255, 255, "%d", clicks[i]);
				else if (clicks[i] < 0)
					draw_font(0, 22, i * 8 + 12, 255, 0, 0, "%d", clicks[i]);
				else
					draw_font(0, 22, i * 8 + 12, 0, 255, 0, "%d", clicks[i]);
			}
		}

		draw_font(0, x_res - 90, 12, 0, 206, 206, "Audio: %s", sound ? "on" : "off");
		draw_font(0, x_res - 95, 20, 0, 206, 206, "Timing: %s", variation ? "random" : "rhytmic");
		if (x_res == 256) {
			draw_font(0, 21, 186, 0, 255, 0, "Press X when the sprite is aligned");
			draw_font(0, 20, 194, 0, 255, 0, "[] button toggles horizontal/vertical");
		} else {
			draw_font(0, 21, 186, 0, 255, 0, "Press X when the sprite is aligned with the background");
			draw_font(0, 20, 194, 0, 255, 0, "[] button toggles horizontal and vertical movement");
		}
		draw_font(0, 20, 202, 0, 255, 0, "() button toggles rhytmic timing");
		draw_font(0, 20, 210, 0, 255, 0, "R1 button toggles audio");

		if (pos >= 10) { //end page
			draw_background();

			for (unsigned char i = 0; i < 10; i++) {
				draw_font(1, 60, 102, 0, 206, 206, "+");
				draw_font(1, 55, 142, 0, 206, 206, "_____");
				if (clicks[i] == 0) {
					draw_font(1, 70, i * 8 + 62, 0, 255, 0, "%d", clicks[i] / 10);
					draw_font(1, 75, i * 8 + 62, 0, 255, 0, "%d", clicks[i] % 10);
				} else {
					draw_font(1, 70, i * 8 + 62, 255, 255, 255, "%d", clicks[i] / 10);
					draw_font(1, 75, i * 8 + 62, 255, 255, 255, "%d", clicks[i] % 10);
				}
			}
			sound = 0; // disable beep
			float ms;

			if (GsScreenM == VMODE_NTSC)
				ms = (float)(1000.0/59.29);
			else
				ms = (float)(1000.0/49.76);

			float frames = (float)total / 10.0f;
			short fint = (short)frames;
			short fdec = (short)((frames - (float)fint + 0.005) * 100.0f);
			draw_font(1, 70 - 25, 150, 255, 255, 255, "%d/10 = %d.%0.2d frames", total, fint , fdec);

			float totalms = ms * frames;
			frames = (float)total / 10.0f;
			fint = (short)totalms;
			fdec = (short)((totalms - (float)fint) * 100.0f);
			draw_font(1, 70 - 25, 158, 255, 255, 255, "%d.%0.2d miliseconds", fint, fdec);

			if (GsScreenM == VMODE_NTSC)
				draw_font(1, x_res == 256 ? 20 : 45, 166, 0, 255, 0, "Keep in mind that frame is around 16.87 ms.");
			else
				draw_font(1, x_res == 256 ? 20 : 45, 166, 0, 255, 0, "Keep in mind that frame is around 20.09 ms.");
		}

		draw_list();
		}
	}
}

void alternate_240p480i()
{
	struct time {
		unsigned long seconds;
		unsigned char frames;
	};

	unsigned char frames = 0;
	unsigned char current = 0;
	unsigned long seconds = 0;
	char interlacing = 0;
	int dbuf = 0;
	struct time times[21];

	while (1) {
		if (display_is_old) {
		dbuf = !dbuf;
		GsSetDispEnvSimple(0, dbuf ? 0 : 256);
		GsSetDrawEnvSimple(0, dbuf ? 256 : 0, x_res, 256);
		GsSetVideoModeEx(x_res, 240, VMODE, 0, interlacing ? 1 : 0, 0);
		GsSortCls(0, 0, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_ALTERNATE);
			break;
		case PAD_CROSS:
			times[current].seconds = seconds;
			times[current].frames = frames;
			current++;
			if (current > 20)
				current = 0;
			if (current % 2)
				interlacing = !interlacing;
			break;
		}

		char x_offset = x_res == 256 ? - 16 : 0;

		draw_font(0, 32 + x_offset, 8, 0, 255, 0, "Current Resolution");
		draw_font(0, 140 + x_offset, 8, 0, 255, 0, "%d%s", interlacing ? y_res * 2 : y_res, interlacing ? "i" : "p");
		draw_font(0, 32 + x_offset, 32, 255, 255, 255, "Elapsed Timer:");
		draw_font(0, 140 + x_offset, 32, 255, 255, 255, "%02d:%02d:%02d:%02d",
			       	seconds / 3600, seconds / 60, seconds % 60, frames);

		frames++;
		if (GsScreenM == VMODE_PAL) {
			if (frames > 49) {
				frames = 0;
				seconds++;
			}
		} else if (frames > 59) {
			frames = 0;
			seconds++;
		}

		for (unsigned char i = 0; i < current; i++) {
			if (i % 2) {
				draw_font(0, 32 + x_offset, 40 + i * 8, 0, 255, 0, "Viewed at:");

				unsigned long diff_sec = times[i].seconds - times[i - 1].seconds;
				if (times[i].frames < times[i - 1].frames)
					diff_sec -= 1;

				char diff_frames = times[i].frames - times[i - 1].frames;
				if (diff_frames < 0)
					diff_frames += 60;

				draw_font(0, 200 + x_offset, 40 + i * 8, 255, 0, 0, "%02d:%02d:%02d:%02d",
					       	diff_sec / 3600, diff_sec / 60, diff_sec % 60, diff_frames);
			} else {
				draw_font(0, 32 + x_offset, 40 + i * 8, 255, 255, 0, "Switched to");

				if (i % 4 == 0)
					draw_font(0, 32 + 12 * 5 + x_offset, 40 + i * 8, 255, 255, 0, "%di at:", y_res * 2);
				else
					draw_font(0, 32 + 12 * 5 + x_offset, 40 + i * 8, 255, 255, 0, "%dp at:", y_res);
			}

			draw_font(0, 140 + x_offset, 40 + i * 8, 255, 255, 255, "%02d:%02d:%02d:%02d",
				       	times[i].seconds / 3600, times[i].seconds / 60, times[i].seconds % 60, times[i].frames);
		}

		GsDrawList();
		while (GsIsDrawing());
		display_is_old = 0;
		}
	}
}

void audio_sync_test()
{
	char pause = 0;
	int status = 0;

	SsVoiceStartAddr(0, SPU_DATA_BASE_ADDR);
	SsVoicePitch(0, 0x1000 / (44100 / 16000));
	SsVoiceVol(0, 0x3fff, 0x3fff);

	GsRectangle dot;
	dot.r = dot.g = dot.b = 255;
	dot.x = x_res / 2; dot.y = 160;
	dot.w = dot.h = 2;
	dot.attribute = 0;

	GsRectangle square;
	square.r = square.g = square.b = 255;
	if (x_res == 256) {
		square.w = 28;  square.h = 28;
	} else {
		square.w = square.h = 32;
	}
	square.x = 0; square.y = 48;

	GsRectangle ground;
	ground.r = ground.g = ground.b = 255;
	ground.x = 0; ground.y = 160;
	ground.w = x_res; ground.h = 8;
	ground.attribute = 0;

	while (1) {
		if (display_is_old) {
		GsSortCls(0, 0, 0);
		GsSetDispEnvSimple(0, 0);
		GsSetDrawEnvSimple(0, 0, x_res, 256);
		GsSetVideoModeEx(x_res, 240, VMODE, 0, interlaced, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_AUDIOSYNC);
			break;
		case PAD_CROSS:
			if (pause) {
				dot.y = 160;
				status = 0;
			}
			pause = !pause;
			break;
		}

		if (!pause) {
			if (status < 120)
				status++;

			if (status > 60)
				dot.y++;
			else
				dot.y--;
		}

		if (status >= 40) {
			square.x = 0;
			GsSortRectangle(&square);
			square.x = x_res - square.w;
			GsSortRectangle(&square);
		}
		if (status >= 60) {
			square.x = square.w;
			GsSortRectangle(&square);
			square.x = x_res - 2 * square.w;
			GsSortRectangle(&square);
		}
		if (status >= 80) {
			square.x = 2 * square.w;
			GsSortRectangle(&square);
			square.x = x_res - 3 * square.w;
			GsSortRectangle(&square);
		}
		if (status >= 100) {
			square.x = 3 * square.w;
			GsSortRectangle(&square);
			square.x = x_res - 4 * square.w;
			GsSortRectangle(&square);
		}
		if (status == 120 && !pause) {
			status = 0;
			SsKeyOn(0); //make sound
			GsSortCls(255, 255, 255); //flash screen white
		}

		GsSortRectangle(&ground);
		GsSortRectangle(&dot);

		draw_list();
		}
	}
}
