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

#include"lz4.h"

#include"resources/beep.h"

#include"font.h"
#include"help.h"
#include"patterns.h"
#include"textures.h"
#include"tests.h"

volatile int display_is_old = 1;
unsigned int prim_list[0x4000];

unsigned short input;

unsigned char VMODE = VMODE_NTSC;
unsigned char interlaced = 0;
unsigned short x_res = 320;
unsigned short y_res = 240;

void prog_vblank_handler()
{
	display_is_old = 1;
}

void load_background()
{
	const void *ptr;
	char data_buffer[41024];

	if (x_res == 256)
		ptr = (unsigned char*)backw256_array + 8;
	else
		ptr = (unsigned char*)back_array + 8;

	GsImage image;

	LZ4_decompress_fast(ptr, data_buffer, 41024);
	GsImageFromTim(&image, data_buffer);
	GsUploadImage(&image);
}

void draw_background()
{
	GsSprite back;

	back.r = back.g = back.b = 128;
	back.attribute = COLORMODE(COLORMODE_4BPP);
	back.mx = back.my = back.rotate = back.scalex = back.scaley = 0;
	back.cx = 960; back.cy = 510;
	back.w = 256; back.h = 256;
	back.u = back.v = 0;

	if (x_res != 256) {
		back.y = 0;
		back.tpage = 14;
		back.w = 64;
		back.u = 192;
		back.x = 0;
		GsSortSprite(&back);
		back.tpage = 15;
		back.w = 256;
		back.x = 64;
		back.u = 0;
		GsSortSprite(&back);
	} else {
		back.y = 0;
		back.tpage = 15;
		back.w = 256;
		back.x = 0;
		GsSortSprite(&back);
	}
}

void upload_sprite(GsImage *image, GsSprite *sprite, void *compressed_buffer)
{
	const void *ptr = (unsigned char*)compressed_buffer + 8;
	unsigned long *original_size = compressed_buffer;

	char data_buffer[*original_size];

	LZ4_decompress_fast(ptr, data_buffer, *original_size);
	GsImageFromTim(image, data_buffer);
	GsUploadImage(image);
	GsSpriteFromImage(sprite, image, 1);
}

unsigned short input_tap()
{
	static unsigned short old_input;

	psx_pad_state padbuf;
	PSX_PollPad(0, &padbuf);

	if (padbuf.type == 2 || padbuf.type == 3) {
		signed char *current_pad_x = NULL;
		signed char *current_pad_y = NULL;

		if (padbuf.type == 2) {
			current_pad_x = &padbuf.extra.analogJoy.x[1];
			current_pad_y = &padbuf.extra.analogJoy.y[1];
		} else {
			current_pad_x = &padbuf.extra.analogPad.x[1];
			current_pad_y = &padbuf.extra.analogPad.y[1];
		}

		if ((*current_pad_x / 48) > 0)
			padbuf.buttons += PAD_RIGHT;

		if ((*current_pad_x / 48) < 0)
			padbuf.buttons += PAD_LEFT;

		if ((*current_pad_y / 48) < 0)
			padbuf.buttons += PAD_UP;

		if ((*current_pad_y / 48) > 0)
			padbuf.buttons += PAD_DOWN;
	}

	input = padbuf.buttons & ~old_input;
	old_input = padbuf.buttons;

	return input;
}

void set_screen(unsigned short x_res, unsigned short y_res, unsigned char VMODE, unsigned char interlaced)
{
		static int dbuf;

		dbuf = !dbuf;

		GsSetDispEnvSimple(0, dbuf ? 0 : 256);
		GsSetDrawEnvSimple(0, dbuf ? 256 : 0, x_res, 256);
		GsSetVideoModeEx(x_res, 240, VMODE, 0, interlaced, 0);
}

void draw_list()
{
	if (y_res != 256) {
		GsRectangle border;

		border.attribute = 0;
		border.r = border.g = border.b = 0;
		border.w = 640;
		border.x = 0;
		border.y = 0;
		border.h = y_res == 240 ? 0 : 8;
		GsSortRectangle(&border);
		border.y = y_res == 224 ? 232 : 240;
		border.h = 32;
		GsSortRectangle(&border);
	}

	GsDrawList();
	while (GsIsDrawing());
	display_is_old = 0;
}

void video_options()
{
	char cnt = 1;

	while (1) {
		if (display_is_old) {
		GsSortCls(0, 0, 0);
		set_screen(x_res, 240, VMODE, interlaced);
		GsSetVideoModeEx(x_res, 240, VMODE, 0, interlaced, 0);

		draw_background();

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_DOWN:
			if (cnt == 4)
				cnt = 1;
			else
				cnt++;
			break;
		case PAD_UP:
			if (cnt == 1)
				cnt = 4;
			else
				cnt--;
			break;
		case PAD_CROSS:
			switch (cnt) {
				case 1:
					if (x_res == 320)
						x_res = 256;
					else
						x_res = 320;
					load_background();
					break;
				case 2:
					if (y_res < 240 + VMODE * 16)
						y_res += 16;
					else
						y_res = 224;
					break;
				case 3:
					interlaced = !interlaced;
					break;
				case 4:
					VMODE = !VMODE;
					if (y_res > 240)
						y_res = 240;
					break;
			}
			break;
		}

		draw_font(1, x_res / 2 - 14 * 5 / 2, 34, 0, 255, 0, "Video settings");

		short x = x_res == 256 ? 20 : 33;

		draw_menu_font(1, cnt, 1, x, 75, "Horizontal Resolution: %d", x_res);
		draw_menu_font(1, cnt, 2, x, 85, "Vertical Resolution: %d%s", interlaced ? y_res * 2 : y_res, interlaced ? "i" : "p");
		draw_menu_font(1, cnt, 3, x, 95, "Interlaced Video: %s", interlaced ? "On" : "Off");
		draw_menu_font(1, cnt, 4, x, 105, "Video Norm: %s", GsScreenM == VMODE_NTSC ? "NTSC" : "PAL");

		draw_list();
		}
	}
}

int main()
{
	PSX_Init();
	GsInit();
	SsInit();
	GsSetList(prim_list);
	GsClearMem();
	GsSetVideoMode(x_res, y_res, VMODE);
	load_custom_font();
	load_background();
	SsUpload(&beep_array, 960, SPU_DATA_BASE_ADDR); //Upload beep sound to sound ram
	SetVBlankHandler(prog_vblank_handler);

	GsImage image;
	GsSprite gillian;

	upload_sprite(&image, &gillian, &gillian_array);

	gillian.x = 221;
	gillian.y = 86;

	char patterns = 0;
	char cnt = 1;

	pad_enable_vibration(0);
	unsigned char led_on[] = {1,0x44,0,1,0x2, 0, 0, 0, 0}; //led on
	pad_escape_mode(0, 1); // Enter escape / configuration mode
	QueryPAD(0, led_on, NULL, sizeof(led_on));
	pad_escape_mode(0, 0); // Exit escape / configuration mode

	CdSendCommand(CdlStop, 0); // Stop spinning cd drive motor

	while (1) {
		if (display_is_old) {
		GsSortCls(0, 0, 0);
		set_screen(x_res, 240, VMODE, interlaced);

		draw_background();
		gillian.x = x_res == 256 ? 177 : 221;
		GsSortSprite(&gillian);

		switch (input_tap()) {
		case PAD_DOWN:
			if (!patterns) {
				if (cnt <= 16)
					cnt++;
				if (cnt > 16)
					cnt = 1;
			}
			else if (patterns) {
				if (cnt <= 12)
					cnt++;
				if (cnt > 12)
					cnt = 1;
			}
			break;
		case PAD_UP:
			if (!patterns) {
				if (cnt >= 0)
					cnt--;
				if (cnt < 1)
					cnt = 16;
			}
			if (patterns) {
				cnt--;
				if (cnt < 1)
					cnt = 12;
			}
			break;
		case PAD_TRIANGLE:
			if (patterns)
				cnt = 1;
			patterns = 0;
			break;
		case PAD_CROSS:
			if (!patterns) {
				switch (cnt) {
				case 1: patterns = 1;
					break;
				case 2: striped_test(1);
					break;
				case 3: striped_test(0);
					break;
				case 4: passive_lag_test();
					break;
				case 5: lag_test();
					break;
				case 6: scroll_test();
					break;
				case 7: grid_scroll_test();
					break;
				case 8: horizontal_stripes();
					break;
				case 9: checkerboard();
					break;
				case 10: backlight_zone();
					break;
				case 11: sound_test();
					break;
				case 12: alternate_240p480i();
					 break;
				case 13: audio_sync_test();
					break;
				case 14: draw_help(HELP_GENERAL);
				       break;
				case 15:
					video_options();
					break;
				case 16: draw_help(HELP_CREDITS);
					 break;
				}
			}

			else if (patterns) {
				switch (cnt) {
				case 1: pluge();
					break;
				case 2: color_bars();
					break;
				case 3: smpte_color_bars();
					break;
				case 4: color_bars_with_gray_reference();
					break;
				case 5: color_bleed_check();
					break;
				case 6: grid();
					break;
				case 7: linearity();
					break;
				case 8: gray_ramp();
					break;
				case 9: white_and_rgb_screens();
					break;
				case 10: sharpness();
					 break;
				case 11: convergence();
					 break;
				case 12: overscan();
					 break;
				}
			}
		}

		int x = x_res == 256 ? 27 : 40;

		if (!patterns) {
			draw_menu_font(1, cnt, 1, x, 47, "Test Patterns>"); //shadow, menucounter, order, x, y, text
			draw_menu_font(1, cnt, 2, x, 55, "Drop Shadow Test");
			draw_menu_font(1, cnt, 3, x, 63, "Striped Sprite Test");
			draw_menu_font(1, cnt, 4, x, 71, "Lag Test");
			draw_menu_font(1, cnt, 5, x, 79, "Manual Lag Test");
			draw_menu_font(1, cnt, 6, x, 88, "Scroll Test");
			draw_menu_font(1, cnt, 7, x, 96, "Grid Scroll Test");
			draw_menu_font(1, cnt, 8, x, 104, "Horizontal Stripes");
			draw_menu_font(1, cnt, 9, x, 112, "Checkerboard");
			draw_menu_font(1, cnt, 10, x, 120, "Backlit Zone Test");
			draw_menu_font(1, cnt, 11, x, 128, "Sound Test");
			draw_menu_font(1, cnt, 12, x, 136, "Alternateting 240p/480i");
			draw_menu_font(1, cnt, 13, x, 144, "Audio Sync Test");
			draw_menu_font(1, cnt, 14, x, 152, "Help");
			if (interlaced)
				draw_menu_font(1, cnt, 15, x, 160, "Video: %dx%di %s", x_res, y_res * 2, VMODE ? "PAL" : "NTSC");
			else
				draw_menu_font(1, cnt, 15, x, 160, "Video: %dx%dp %s", x_res, y_res, VMODE ? "PAL" : "NTSC");
			draw_menu_font(1, cnt, 16, x, 182, "Credits");
		}
		if (patterns) {
			draw_menu_font(1, cnt, 1, x, 47, "Pluge");
			draw_menu_font(1, cnt, 2, x, 55, "Color Bars");
			if (GsScreenM  == VMODE_NTSC)
				draw_menu_font(1, cnt, 3, x, 63, "SMPTE Color Bars");
			else
				draw_menu_font(1, cnt, 3, x, 63, "EBU Color Bars");
			draw_menu_font(1, cnt, 4, x, 71, "Color Bars with Gray Scale");
			draw_menu_font(1, cnt, 5, x, 79, "Color Bleed Check");
			draw_menu_font(1, cnt, 6, x, 88, "Grid");
			draw_menu_font(1, cnt, 7, x, 96, "Linearity");
			draw_menu_font(1, cnt, 8, x, 104, "Gray Ramp");
			draw_menu_font(1, cnt, 9, x, 112, "White & RGB Screens");
			draw_menu_font(1, cnt, 10, x, 120, "Sharpness");
			draw_menu_font(1, cnt, 11, x, 128, "Convergence & Focus");
			draw_menu_font(1, cnt, 12, x, 136, "Overscan");
		}


		draw_list();
		}
	}
}
