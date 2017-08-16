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

#include"font.h"
#include"240p.h"

enum help {
	HELP_CREDITS,
	HELP_GENERAL
};

void draw_help(int option)
{
	int page = 0;
	int totalpages = 0;

	switch (option) {
		case HELP_GENERAL:
			totalpages = 0;
			break;
	}

	while (1) {
		if (display_is_old) {
		flip_buffer();
		GsSortCls(0, 0, 0);
		draw_background();

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			return;
		case PAD_RIGHT:
			if (page < totalpages)
				page++;
			break;
		case PAD_LEFT:
			if (page > 0)
				page--;
			break;
		}

		switch (option) {
		case HELP_CREDITS:
			draw_font(1, 235, 42, 255, 255, 255, "16.08.2017");

			draw_font(1, 40, 55, 0, 255, 0, "Code, Convergence and Focus Pattern");
			draw_font(1, 40, 65, 255, 255, 255, "Filip Alac");
			draw_font(1, 40, 75, 0, 255, 0, "Patterns, Concept and original creator of Suite");
			draw_font(1, 40, 85, 255, 255, 255, "Artemio Urbina");
			draw_font(1, 40, 95, 0, 255, 0, "Advisor");
			draw_font(1, 40, 105, 255, 255, 255, "Fudoh");
			draw_font(1, 40, 115, 0, 255, 0, "Menu Pixel Art");
			draw_font(1, 40, 125, 255, 255, 255, "Asher");
			draw_font(1, 40, 135, 0, 255, 0, "SDK");
			draw_font(1, 40, 145, 255, 255, 255, "PSXSDK by Nextvolume");
			draw_font(1, 39, 155, 0, 255, 0, "Info on using this suite");
			draw_font(1, 40, 165, 255, 255, 255, "http:/junkerhq.net/xrgb");
			break;
		case HELP_GENERAL:
			switch (page) {
			case 0:
		//		draw_font(1, 138, 42, 0, 255, 0, "HELP(1/3)");
				draw_font(1, 24 + 8, 40 + 16, 255, 255, 255, "The 240p Test Suite was");
				draw_font(1, 24 + 8, 48 + 16, 255, 255, 255, "designed with two goals in");
				draw_font(1, 24 + 8, 56 + 16, 255, 255, 255, "mind");

				draw_font(1, 24 + 8, 72 + 16, 255, 255, 255, "1) Evaluate 240p signals");
				draw_font(1, 24 + 8, 80 + 16, 255, 255, 255, "on TV sets and video processors; and");

				draw_font(1, 24 + 8, 96 + 16, 255, 255, 255, "2) Provide calibration");
				draw_font(1, 24 + 8, 104 + 16, 255, 255, 255, "patterns from a game");
				draw_font(1, 24 + 8, 112 + 16, 255, 255, 255, "console to help in");
				draw_font(1, 24 + 8, 120 + 16, 255, 255, 255, "properly calibrating the");
				draw_font(1, 24 + 8, 128 + 16, 255, 255, 255, "display black, white and");
				draw_font(1, 24 + 8, 136 + 16, 255, 255, 255, "color levels.");

				//draw_font(1, 227 + 16, 176 + 24, 255, 255, 0, "(cont...)");
			}
			break;
		}

		GsDrawList();
		while (GsIsDrawing());
		display_is_old = 0;
		}
	}
}
