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

#include<string.h>

#include"font.h"
#include"240p.h"

enum help {
	HELP_CREDITS,
	HELP_GENERAL,
	HELP_PLUGE,
	HELP_COLORS,
	HELP_GRID,
	HELP_BLEED,
	HELP_IRE,
	HELP_601CB,
	HELP_SHARPNESS,
	HELP_CONVERGENCE_FOCUS,
	HELP_OVERSCAN,
	HELP_SMPTE,
	HELP_LINEARITY,
	HELP_GRAY,
	HELP_WHITE,
	HELP_CHECK,
	HELP_STRIPES,
	HELP_SHADOW,
	HELP_STRIPED,
	HELP_MANUALLAG,
	HELP_HSCROLL,
	HELP_VSCROLL,
	HELP_SOUND,
	HELP_BACKLIT,
	HELP_LAG,
	HELP_ALTERNATE,
	HELP_VIDEO,
	HELP_AUDIOSYNC
};

static void center_title(char *text)
{
	short centered_x = x_res / 2 - strlen(text) * 5 / 2;
	draw_font(1, centered_x, 34, 0, 255, 0, text);
}

void draw_help(int option)
{
	int page = 1;
	int totalpages = 1;

	switch (option) {
	case HELP_GENERAL:
	case HELP_PLUGE:
	case HELP_STRIPES:
	case HELP_SHADOW:
	case HELP_BACKLIT:
	case HELP_HSCROLL:
		totalpages = 2;
		break;
	case HELP_MANUALLAG:
		totalpages = 3;
		break;
	}

	while (1) {
		if (display_is_old) {
		set_screen(x_res, 240, VMODE, interlaced);
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
			if (page > 1)
				page--;
			break;
		}

		int y = 42;
		int x = x_res == 256 ? 20 : 33;

		switch (option) {
		case HELP_CREDITS:
			draw_font(1, x_res == 256 ? 188 : 235, 34, 255, 255, 255, "2.1.2018");

			draw_font(1, x, 45, 0, 255, 0, "Code, Convergence and Focus Pattern");
			draw_font(1, x, 55, 255, 255, 255, "Filip Alac");
			if (x_res == 256)
				draw_font(1, x, 65, 0, 255, 0, "Patterns, Concept");
			else
				draw_font(1, x, 65, 0, 255, 0, "Patterns, Concept and original creator of the Suite");
			draw_font(1, x, 75, 255, 255, 255, "Artemio Urbina");
			draw_font(1, x, 85, 0, 255, 0, "Advisor");
			draw_font(1, x, 95, 255, 255, 255, "Fudoh");
			draw_font(1, x, 105, 0, 255, 0, "Menu Pixel Art");
			draw_font(1, x, 115, 255, 255, 255, "Asher");
			draw_font(1, x, 125, 0, 255, 0, "SDK");
			draw_font(1, x, 135, 255, 255, 255, "PSXSDK by Nextvolume");
			draw_font(1, x - 1, 145, 0, 255, 0, "Info on using this suite");
			draw_font(1, x, 155, 255, 255, 255, "http:/junkerhq.net/240p");
			break;
		case HELP_GENERAL:
			switch (page) {
			case 1:
				center_title("HELP (1/2)");
				draw_font(1, x, y += 8, 255, 255, 255, "The 240p Test Suite was designed");
				draw_font(1, x, y += 8, 255, 255, 255, "with two goals in mind:");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "1) Evaluate 240p signals on TV");
				draw_font(1, x, y += 8, 255, 255, 255, "sets and video procesors");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "2) Provide calibration patterns");
				draw_font(1, x, y += 8, 255, 255, 255, "from a game console to help in");
				draw_font(1, x, y += 8, 255, 255, 255, "properly calibrating the display");
				draw_font(1, x, y += 8, 255, 255, 255, "black, white and color levels.");
				y += 32;
				draw_font(1, x, y += 8, 255, 255, 255, "Help is available by pressing 'START'.");
				draw_font(1, x_res == 256 ? 185 : 240, 192, 255, 255, 0, "(cont...)");
				break;
			case 2:
				center_title("HELP (2/2)");
				draw_font(1, x, y += 8, 255, 255, 255, "This version of the suite supports:");
				draw_font(1, x, y += 8, 255, 255, 255, "320/256 vertical resolution,");
				draw_font(1, x, y += 8, 255, 255, 255, "224p/448i, 240p/480i and 256p/512i");
				draw_font(1, x, y += 8, 255, 255, 255, "in PAL and 224p/448i, 240p/480i in NTSC");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "The 240p suite is also available");
				draw_font(1, x, y += 8, 255, 255, 255, "in GameCube, Nintendo Wii, NES,");
				draw_font(1, x, y += 8, 255, 255, 255, "PC Engine/TG-16, Super CD,");
				draw_font(1, x, y += 8, 255, 255, 255, "CD-ROM2, Sega Mega Drive/Genesis,");
				draw_font(1, x, y += 8, 255, 255, 255, "Sega CD/Mega CD and Sega Dreamcast.");
				y += 32;
				draw_font(1, x, y += 8, 255, 255, 255, "Visit:");
				draw_font(1, x, y += 8, 0, 255, 0, "http://junkerhq.net/240p");
				draw_font(1, x, y += 8, 255, 255, 255, "for more information.");
				break;
			}
			break;
		case HELP_PLUGE:
			switch (page) {
			case 1:
				center_title("PLUGE (1/2)");
				draw_font(1, x, y += 8 , 255, 255, 255, "This test pattern is used to");
				draw_font(1, x, y += 8, 255, 255, 255, "adjust the black level and contrast");
				draw_font(1, x, y += 8, 255, 255, 255, "of video signal.");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "The pattern in this suite is mainly");
				draw_font(1, x, y += 8, 255, 255, 255, "designed to adjust the black level.");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "This adjustmenst ensures that anything");
				draw_font(1, x, y += 8, 255, 255, 255, "intended to be black is actually black,");
				draw_font(1, x, y += 8, 255, 255, 255, "and allows details to be seen ");
				draw_font(1, x, y += 8, 255, 255, 255, "on dark scenes");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "Reduce the brightness until the desired");
				draw_font(1, x, y += 8, 255, 255, 255, "bars are no longer visible, and then");
				draw_font(1, x, y += 8, 255, 255, 255, "slowly raise it until they are");
				draw_font(1, x, y += 8, 255, 255, 255, "just visible.");
				draw_font(1, x_res == 256 ? 185 : 240, 192, 255, 255, 0, "(cont...)");
				break;
			case 2:
				center_title("PLUGE (2/2)");
				draw_font(1, x, y += 8, 255, 255, 255, "Values for the bars are:");
				draw_font(1, x, y += 8, 255, 255, 255, "closest to the center 8,");
				draw_font(1, x, y += 8, 255, 255, 255, "central ones 16, and outer ones 24.");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "When calibrating for");
				draw_font(1, x, y += 8, 255, 255, 255, "NTSC video(not games) material,");
				draw_font(1, x, y += 8, 255, 255, 255, "the 16(7.5 IRE) bars should");
				draw_font(1, x, y += 8, 255, 255, 255, "blend in the background.");
				draw_font(1, x, y += 8, 255, 255, 255, "The 7.5 IRE in NTSC is the black level,");
				draw_font(1, x, y += 8, 255, 255, 255, "also known as setup.");
				break;
			}
			break;
		case HELP_COLORS:
			center_title("COLORBARS");
			draw_font(1, x, y += 8, 255, 255, 255, "This pattern allows you to");
			draw_font(1, x, y += 8, 255, 255, 255, "calibrate each color: Red, Green");
			draw_font(1, x, y += 8, 255, 255, 255, "and Blue");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "Adjust the white level first, ");
			draw_font(1, x, y += 8, 255, 255, 255, "using the \"Contrast\" control");
			draw_font(1, x, y += 8, 255, 255, 255, "on your TV set. Raise it until");
			draw_font(1, x, y += 8, 255, 255, 255, "you cannot distinguish between");
			draw_font(1, x, y += 8, 255, 255, 255, "the blocks under \"C\" and \"E\",");
			draw_font(1, x, y += 8, 255, 255, 255, "and lower it slowly until you");
			draw_font(1, x, y += 8, 255, 255, 255, "can clearly tell them appart.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "Do the same for each color.");
			break;
		case HELP_GRID:
			center_title("GRID");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "You can use this grid to verify that ");
			draw_font(1, x, y += 8, 255, 255, 255, "all the visible area is being ");
			draw_font(1, x, y += 8, 255, 255, 255, "displayed, and that there is no");
			draw_font(1, x, y += 8, 255, 255, 255, "distortion present.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "The full active video signal can");
			draw_font(1, x, y += 8, 255, 255, 255, "be filled with gray by pressing");
			draw_font(1, x, y += 8, 255, 255, 255, "the '[]' button.");
			break;
		case HELP_BLEED:
			center_title("COLOR BLEED");
			draw_font(1, x, y += 8, 255, 255, 255, "This pattern helps diagnose");
			draw_font(1, x, y += 8, 255, 255, 255, "color bleed caused by");
			draw_font(1, x, y += 8, 255, 255, 255, "unneeded color upsampling. ");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "You can toggle between");
			draw_font(1, x, y += 8, 255, 255, 255, "vertical bars and");
			draw_font(1, x, y += 8, 255, 255, 255, "checkerboard with 'X'.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "You can also traverse horizontal");
			draw_font(1, x, y += 8, 255, 255, 255, "resolutions by 'LEFT' and 'RIGHT'.");
			break;
		case HELP_IRE:
			center_title("100 IRE");
			draw_font(1, x, y += 8, 255, 255, 255, "You can vary IRE intensity");
			draw_font(1, x, y += 8, 255, 255, 255, "with A and B. Values are:");
			draw_font(1, x, y += 8, 255, 255, 255, "13, 25, 41, 53, 66, 82, 94");
			break;
		case HELP_601CB:
			center_title("601 COLORBARS");
			draw_font(1, x, y += 8, 255, 255, 255, "You can use color filters or the");
			draw_font(1, x, y += 8, 255, 255, 255, "blue only option in your display");
			draw_font(1, x, y += 8, 255, 255, 255, "-if available- to confirm color");
			draw_font(1, x, y += 8, 255, 255, 255, "balance.");
			break;
		case HELP_SHARPNESS:
			center_title("SHARPNESS");
			draw_font(1, x, y += 8, 255, 255, 255, "You should set the sharpness of");
			draw_font(1, x, y += 8, 255, 255, 255, "your CRT to a value that shows");
			draw_font(1, x, y += 8, 255, 255, 255, "clean black and gray transitions");
			draw_font(1, x, y += 8, 255, 255, 255, "with no white ghosting between.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "On most modern displays, the");
			draw_font(1, x, y += 8, 255, 255, 255, "sharpness control is an edge-");
			draw_font(1, x, y += 8, 255, 255, 255, "enhancement control, and most");
			draw_font(1, x, y += 8, 255, 255, 255, "probably should be set to zero,");
			draw_font(1, x, y += 8, 255, 255, 255, "or in the middle.");
			break;
		case HELP_CONVERGENCE_FOCUS:
			center_title("CONVERGENCE & FOCUS");
			draw_font(1, x, y += 8, 255, 255, 255, "With this pattern you can");
			draw_font(1, x, y += 8, 255, 255, 255, "adjust focus and convergence");
			draw_font(1, x, y += 8, 255, 255, 255, "on CRT display.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "For adjusting focus, it is");
			draw_font(1, x, y += 8, 255, 255, 255, "best to select green pattern");
			draw_font(1, x, y += 8, 255, 255, 255, "and look in the middle of");
			draw_font(1, x, y += 8, 255, 255, 255, "the screen while you adjust");
			draw_font(1, x, y += 8, 255, 255, 255, "focus.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "For adjusting convergence, it is");
			draw_font(1, x, y += 8, 255, 255, 255, "best to select white pattern.");
			break;
		case HELP_OVERSCAN:
			center_title("OVERSCAN");
			draw_font(1, x, y += 8, 255, 255, 255, "With this pattern you can");
			draw_font(1, x, y += 8, 255, 255, 255, "interactively find out the");
			draw_font(1, x, y += 8, 255, 255, 255, "overscan in pixels of each edge");
			draw_font(1, x, y += 8, 255, 255, 255, "in a display.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "Use left and right to increment");
			draw_font(1, x, y += 8, 255, 255, 255, "the overscan until you see the");
			draw_font(1, x, y += 8, 255, 255, 255, "white border, then go back one");
			draw_font(1, x, y += 8, 255, 255, 255, "pixel. The resulting number is");
			draw_font(1, x, y += 8, 255, 255, 255, "the amount of overscan in pixels");
			draw_font(1, x, y += 8, 255, 255, 255, "in each direction.");
			break;
		case HELP_SMPTE:
			center_title("SMPTE COLOR BARS");
			draw_font(1, x, y += 8, 255, 255, 255, "This pattern can be used to");
			draw_font(1, x, y += 8, 255, 255, 255, "calibrate for NTSC levels");
			draw_font(1, x, y += 8, 255, 255, 255, "regarding contrast,");
			draw_font(1, x, y += 8, 255, 255, 255, "brightness and colors. ");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "You can toggle between 75%% and");
			draw_font(1, x, y += 8, 255, 255, 255, "100%% SMPTE color bars with 'X'.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "When in PAL this pattern show");
			draw_font(1, x, y += 8, 255, 255, 255, "EBU color bars instead,");
			draw_font(1, x, y += 8, 255, 255, 255, "since setup starts at 0mV.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "You can use color filters or the");
			draw_font(1, x, y += 8, 255, 255, 255, "blue only option in your display");
			draw_font(1, x, y += 8, 255, 255, 255, "-if available- to confirm color");
			draw_font(1, x, y += 8, 255, 255, 255, "balance.");
			break;
		case HELP_LINEARITY:
			center_title("LINEARITY");
			draw_font(1, x, y += 8, 255, 255, 255, "This pattern shows 5 circles,");
			draw_font(1, x, y += 8, 255, 255, 255, "that are matched to the 10:11");
			draw_font(1, x, y += 8, 255, 255, 255, "NTSC and the 59:54 PAL pixel");
			draw_font(1, x, y += 8, 255, 255, 255, "aspect ratios.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "The linearity of the display or");
			draw_font(1, x, y += 8, 255, 255, 255, "upscaler can be verified by");
			draw_font(1, x, y += 8, 255, 255, 255, "measuring the diameter of the");
			draw_font(1, x, y += 8, 255, 255, 255, "circles.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "Of course the linearity should");
			draw_font(1, x, y += 8, 255, 255, 255, "be kept in all directions.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "Grid is also available with");
			draw_font(1, x, y += 8, 255, 255, 255, "'()' and '[]' buttons.");
			break;
		case HELP_GRAY:
			center_title("GRAY RAMP");
			draw_font(1, x, y += 8, 255, 255, 255, "This gray ramp pattern can be");
			draw_font(1, x, y += 8, 255, 255, 255, "used to check color balance.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "You should make sure the bars");
			draw_font(1, x, y += 8, 255, 255, 255, "are gray, with no red or blue");
			draw_font(1, x, y += 8, 255, 255, 255, "bias. This can be adjusted with");
			draw_font(1, x, y += 8, 255, 255, 255, "the individual color settings,");
			draw_font(1, x, y += 8, 255, 255, 255, "or the tint control in NTSC");
			draw_font(1, x, y += 8, 255, 255, 255, "displays.");
			break;
		case HELP_WHITE:
			center_title("WHITE SCREEN");
			draw_font(1, x, y += 8, 255, 255, 255, "This pattern can be changed");
			draw_font(1, x, y += 8, 255, 255, 255, "between white, black, red,");
			draw_font(1, x, y += 8, 255, 255, 255, "green and blue screens with the");
			draw_font(1, x, y += 8, 255, 255, 255, "'X' button.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "Some displays and scalers have");
			draw_font(1, x, y += 8, 255, 255, 255, "issues when changing between a");
			draw_font(1, x, y += 8, 255, 255, 255, "black 0 IRE and a white screen.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "A custom color mode is");
			draw_font(1, x, y += 8, 255, 255, 255, "available by pressing '()'.");
			break;
		case HELP_CHECK:
			center_title("CHECKERBOARD");
			draw_font(1, x, y += 8, 255, 255, 255, "This pattern shows all the");
			draw_font(1, x, y += 8, 255, 255, 255, "visible pixels in an");
			draw_font(1, x, y += 8, 255, 255, 255, "alternating white and black");
			draw_font(1, x, y += 8, 255, 255, 255, "grid array.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "You can toggle the pattern with");
			draw_font(1, x, y += 8, 255, 255, 255, "button '()', or turn on");
			draw_font(1, x, y += 8, 255, 255, 255, "auto-toggle each frame with the");
			draw_font(1, x, y += 8, 255, 255, 255, "'X' button. A frame counter is");
			draw_font(1, x, y += 8, 255, 255, 255, "also available with '[]'.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "You can also traverse horizontal");
			draw_font(1, x, y += 8, 255, 255, 255, "resolutions by 'LEFT' and 'RIGHT'.");
			break;
		case HELP_STRIPES:
			switch (page) {
			case 1:
				center_title("HORIZONTAL STRIPES (1/2)");
				draw_font(1, x, y += 8, 255, 255, 255, "lines, each one pixel in height");
				draw_font(1, x, y += 8, 255, 255, 255, "starting with a white one.");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "You can toggle the pattern with");
				draw_font(1, x, y += 8, 255, 255, 255, "button '()', or turn on");
				draw_font(1, x, y += 8, 255, 255, 255, "auto-toggle each frame with the");
				draw_font(1, x, y += 8, 255, 255, 255, "'X' button. A frame counter is");
				draw_font(1, x, y += 8, 255, 255, 255, "also available with '[]'.");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "When auto-toggle is set, you");
				draw_font(1, x, y += 8, 255, 255, 255, "should see the lines");
				draw_font(1, x, y += 8, 255, 255, 255, "alternating rapidly. On some");
				draw_font(1, x, y += 8, 255, 255, 255, "setups, the pattern doesn't");
				draw_font(1, x, y += 8, 255, 255, 255, "change at all. This means that");
				draw_font(1, x_res == 256 ? 185 : 240, 192, 255, 255, 0, "(cont...)");
				break;
			case 2:
				center_title("HORIZONTAL STRIPES (2/2)");
				draw_font(1, x, y += 8, 255, 255, 255, "the signal is being treated as");
				draw_font(1, x, y += 8, 255, 255, 255, "480i/576i and odd or even frames");
				draw_font(1, x, y += 8, 255, 255, 255, "are being discarded completely.");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "You can also display vertical");
				draw_font(1, x, y += 8, 255, 255, 255, "bars by pressing 'UP'. That");
				draw_font(1, x, y += 8, 255, 255, 255, "pattern will help you ");
				draw_font(1, x, y += 8, 255, 255, 255, "evaluate if the signal is not");
				draw_font(1, x, y += 8, 255, 255, 255, "distorted horizontaly, since");
				draw_font(1, x, y += 8, 255, 255, 255, "all lines should be one pixel");
				draw_font(1, x, y += 8, 255, 255, 255, "wide.");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "You can also traverse horizontal");
				draw_font(1, x, y += 8, 255, 255, 255, "resolutions by 'LEFT' and 'RIGHT'.");
				break;
			}
			break;
		case HELP_SHADOW:
			switch (page) {
			case 1:
				center_title("DROP SHADOW TEST (1/2)");
				draw_font(1, x, y += 8, 255, 255, 255, "This is a crucial test for 240p");
				draw_font(1, x, y += 8, 255, 255, 255, "upscan converters. It displays a");
				draw_font(1, x, y += 8, 255, 255, 255, "simple sprite shadow against a");
				draw_font(1, x, y += 8, 255, 255, 255, "background, but the shadow is");
				draw_font(1, x, y += 8, 255, 255, 255, "shown only on each other frame.");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "On a CRT this achieves a");
				draw_font(1, x, y += 8, 255, 255, 255, "transparency effect, since you");
				draw_font(1, x, y += 8, 255, 255, 255, "are watching a 30hz (25Hz)");
				draw_font(1, x, y += 8, 255, 255, 255, "shadow on a 60hz (50hz) signal.");
				draw_font(1, x, y += 8, 255, 255, 255, "No background detail should be");
				draw_font(1, x, y += 8, 255, 255, 255, "lost and the shadow should be");
				draw_font(1, x, y += 8, 255, 255, 255, "visible.");
				draw_font(1, x_res == 256 ? 185 : 240, 192, 255, 255, 0, "(cont...)");
				break;
			case 2:
				center_title("DROP SHADOW TEST (2/2)");
				draw_font(1, x, y += 8, 255, 255, 255, "The user can toggle the frame");
				draw_font(1, x, y += 8, 255, 255, 255, "used to draw the shadow with");
				draw_font(1, x, y += 8, 255, 255, 255, "button '()'. Backgrounds can be");
				draw_font(1, x, y += 8, 255, 255, 255, "switched with the 'X' button and");
				draw_font(1, x, y += 8, 255, 255, 255, "button '[]' toggles sprites. ");
				break;
			}
			break;
		case HELP_STRIPED:
			center_title("STRIPED SPRITE TEST");
			draw_font(1, x, y += 8, 255, 255, 255, "There are deinterlacers out");
			draw_font(1, x, y += 8, 255, 255, 255, "there that can display the drop");
			draw_font(1, x, y += 8, 255, 255, 255, "shadows correctly and still");
			draw_font(1, x, y += 8, 255, 255, 255, "interpret 240p as 480i. With a");
			draw_font(1, x, y += 8, 255, 255, 255, "striped sprite it should be easy");
			draw_font(1, x, y += 8, 255, 255, 255, "to tell if a processor tries to");
			draw_font(1, x, y += 8, 255, 255, 255, "deinterlace (plus interpolate).");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "You can change backgrounds with");
			draw_font(1, x, y += 8, 255, 255, 255, "'X'.");
			break;
		case HELP_MANUALLAG:
			switch (page) {
			case 1:
				center_title("MANUAL LAG TEST (1/3)");
				draw_font(1, x, y += 8, 255, 255, 255, "The main intention is to show a");
				draw_font(1, x, y += 8, 255, 255, 255, "changing pattern on the screen,");
				draw_font(1, x, y += 8, 255, 255, 255, "which can be complemented with");
				draw_font(1, x, y += 8, 255, 255, 255, "audio. This should show to some");
				draw_font(1, x, y += 8, 255, 255, 255, "degree any lag when processing");
				draw_font(1, x, y += 8, 255, 255, 255, "the signal.");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "As an added feature, the user");
				draw_font(1, x, y += 8, 255, 255, 255, "can click the 'X' button when");
				draw_font(1, x, y += 8, 255, 255, 255, "the sprite is aligned with the");
				draw_font(1, x, y += 8, 255, 255, 255, "one on the background, and the");
				draw_font(1, x, y += 8, 255, 255, 255, "offset in frames from the actual");
				draw_font(1, x, y += 8, 255, 255, 255, "intersection will be shown on");
				draw_font(1, x, y += 8, 255, 255, 255, "screen. A 1khz tone will be");
				draw_font(1, x, y += 8, 255, 255, 255, "played.");
				draw_font(1, x_res == 256 ? 185 : 240, 192, 255, 255, 0, "(cont...)");
				break;
			case 2:
				center_title("MANUAL LAG TEST (2/3)");
				draw_font(1, x, y += 8, 255, 255, 255, "This can be repeated ten");
				draw_font(1, x, y += 8, 255, 255, 255, "times and the software will");
				draw_font(1, x, y += 8, 255, 255, 255, "calculate the average. Whenever");
				draw_font(1, x, y += 8, 255, 255, 255, "the button was pressed before");
				draw_font(1, x, y += 8, 255, 255, 255, "the actual intersection frame,");
				draw_font(1, x, y += 8, 255, 255, 255, "the result will be ignored, but");
				draw_font(1, x, y += 8, 255, 255, 255, "still shown onscreen. Button '[]'");
				draw_font(1, x, y += 8, 255, 255, 255, "can be used to change the");
				draw_font(1, x, y += 8, 255, 255, 255, "direction of the sprite from");
				draw_font(1, x, y += 8, 255, 255, 255, "vertical to horizontal, or both");
				draw_font(1, x, y += 8, 255, 255, 255, "at the same time.");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "Of course the evaluation is");
				draw_font(1, x, y += 8, 255, 255, 255, "dependent on reflexes and/or");
				draw_font(1, x, y += 8, 255, 255, 255, "rhythm more than anything. The");
				draw_font(1, x_res == 256 ? 185 : 240, 192, 255, 255, 0, "(cont...)");
				break;
			case 3:
				center_title("MANUAL LAG TEST (3/3)");
				draw_font(1, x, y += 8, 255, 255, 255, "visual and audio cues are the");
				draw_font(1, x, y += 8, 255, 255, 255, "more revealing aspects which");
				draw_font(1, x, y += 8, 255, 255, 255, "the user should consider, of");
				draw_font(1, x, y += 8, 255, 255, 255, "course the interactive factor");
				draw_font(1, x, y += 8, 255, 255, 255, "can give an experienced player");
				draw_font(1, x, y += 8, 255, 255, 255, "the hang of the system when");
				draw_font(1, x, y += 8, 255, 255, 255, "testing via different");
				draw_font(1, x, y += 8, 255, 255, 255, "connections.");
				break;
			}
			break;
		case HELP_HSCROLL:
			switch (page) {
			case 1:
				center_title("SCROLL TEST (1/2)");
				draw_font(1, x, y += 8, 255, 255, 255, "This test shows either an");
				draw_font(1, x, y += 8, 255, 255, 255, "horizontal background from");
				draw_font(1, x, y += 8, 255, 255, 255, "Sonic or a vertical one from");
				draw_font(1, x, y += 8, 255, 255, 255, "Kiki Kaikai.");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "Speed can be varied with the");
				draw_font(1, x, y += 8, 255, 255, 255, "d-pad and scroll direction with");
				draw_font(1, x, y += 8, 255, 255, 255, "'()'. The '[]' button stops the");
				draw_font(1, x, y += 8, 255, 255, 255, "scroll and 'X' toggles between");
				draw_font(1, x, y += 8, 255, 255, 255, "vertical and horizontal.");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "This can be used to notice any");
				draw_font(1, x, y += 8, 255, 255, 255, "drops in framerate, or pixel");
				draw_font(1, x, y += 8, 255, 255, 255, "width inconsistencies.");
				draw_font(1, x_res == 256 ? 185 : 240, 192, 255, 255, 0, "(cont...)");
				break;
			case 2:
				center_title("SCROLL TEST (2/2)");
				draw_font(1, x, y += 8, 255, 255, 255, "Sonic is a trademark of Sega");
				draw_font(1, x, y += 8, 255, 255, 255, "Enterprises Ltd. Kiki Kaikai");
				draw_font(1, x, y += 8, 255, 255, 255, "is a trademark of Namco Bandai.");
				break;
			}
			break;
		case HELP_VSCROLL:
			center_title("GRID SCROLL TEST");
			draw_font(1, x, y += 8, 255, 255, 255, "A grid is scrolled vertically or");
			draw_font(1, x, y += 8, 255, 255, 255, "horizontally, which can be used");
			draw_font(1, x, y += 8, 255, 255, 255, "to test linearity of the signal");
			draw_font(1, x, y += 8, 255, 255, 255, "and how well the display or");
			draw_font(1, x, y += 8, 255, 255, 255, "video processor copes with");
			draw_font(1, x, y += 8, 255, 255, 255, "scrolling and framerate.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "Button 'X' can be used to toggle");
			draw_font(1, x, y += 8, 255, 255, 255, "between horizontal and vertical,");
			draw_font(1, x, y += 8, 255, 255, 255, "while the d-pad regulates speed. ");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "Button '[]' stops the scroll and");
			draw_font(1, x, y += 8, 255, 255, 255, "button '()' changes direction.");
			break;
		case HELP_SOUND:
			center_title("SOUND TEST");
			draw_font(1, x, y += 8, 255, 255, 255, "This simple test plays a beep");
			draw_font(1, x, y += 8, 255, 255, 255, "in either channel.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "It can be used to determine if");
			draw_font(1, x, y += 8, 255, 255, 255, "the audio chain is working");
			draw_font(1, x, y += 8, 255, 255, 255, "properly.");
			break;
		case HELP_BACKLIT:
			switch (page) {
			case 1:
				center_title("BACKLIT TEST (1/2)");
				draw_font(1, x, y += 8, 255, 255, 255, "This test allows you to check");
				draw_font(1, x, y += 8, 255, 255, 255, "how the display's backlit works");
				draw_font(1, x, y += 8, 255, 255, 255, "when only a small array of");
				draw_font(1, x, y += 8, 255, 255, 255, "pixels is shown. This can be");
				draw_font(1, x, y += 8, 255, 255, 255, "very revealing and can be used");
				draw_font(1, x, y += 8, 255, 255, 255, "to detect the zones in LED");
				draw_font(1, x, y += 8, 255, 255, 255, "backlit displays, or to evaluate");
				draw_font(1, x, y += 8, 255, 255, 255, "global and local dimming.");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "The user can move around the");
				draw_font(1, x, y += 8, 255, 255, 255, "white pixel arrays with the");
				draw_font(1, x, y += 8, 255, 255, 255, "d-pad, and change the size of");
				draw_font(1, x, y += 8, 255, 255, 255, "the pixel array with 'X'.");
				draw_font(1, x, y += 8, 255, 255, 255, "The '()' button allows the user");
				draw_font(1, x, y += 8, 255, 255, 255, "to hide the pixel array in");
				draw_font(1, x_res == 256 ? 185 : 240, 192, 255, 255, 0, "(cont...)");
				break;
			case 2:
				center_title("BACKLIT TEST (2/2)");
				draw_font(1, x, y += 8, 255, 255, 255, "order to alternate a fully black");
				draw_font(1, x, y += 8, 255, 255, 255, "screen.");
				y += 8;
				draw_font(1, x, y += 8, 255, 255, 255, "It might be necessary to have a");
				draw_font(1, x, y += 8, 255, 255, 255, "fully-off panel (if possible)");
				draw_font(1, x, y += 8, 255, 255, 255, "when displaying the black");
				draw_font(1, x, y += 8, 255, 255, 255, "background,  in order to");
				draw_font(1, x, y += 8, 255, 255, 255, "evaluate full-backlit displays");
				draw_font(1, x, y += 8, 255, 255, 255, "by adjusting brightness");
				draw_font(1, x, y += 8, 255, 255, 255, "accordingly for this test.");
				break;
			}
			break;
		case HELP_LAG:
			center_title("LAG TEST");
			draw_font(1, x, y += 8, 255, 255, 255, "This test is designed to be used");
			draw_font(1, x, y += 8, 255, 255, 255, "with two displays conected at");
			draw_font(1, x, y += 8, 255, 255, 255, "the same time. One being a CRT,");
			draw_font(1, x, y += 8, 255, 255, 255, "or a display with a known lag as");
			draw_font(1, x, y += 8, 255, 255, 255, "reference, and the other the");
			draw_font(1, x, y += 8, 255, 255, 255, "display to test.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "Using a camera, a picture should");
			draw_font(1, x, y += 8, 255, 255, 255, "be taken of both screens at the");
			draw_font(1, x, y += 8, 255, 255, 255, "same time. The picture will show");
			draw_font(1, x, y += 8, 255, 255, 255, "the frame discrepancy between");
			draw_font(1, x, y += 8, 255, 255, 255, "them. ");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "The circles in the bottom help");
			draw_font(1, x, y += 8, 255, 255, 255, "determine the frame even when");
			draw_font(1, x, y += 8, 255, 255, 255, "the numbers are blurry.");
			break;
		case HELP_ALTERNATE:
			center_title("ALTERNATE 240p/480i");
			draw_font(1, x, y += 8, 255, 255, 255, "Some devices have a delay when");
			draw_font(1, x, y += 8, 255, 255, 255, "the source changes between");
			draw_font(1, x, y += 8, 255, 255, 255, "resolutions, which happens in");
			draw_font(1, x, y += 8, 255, 255, 255, "some games. This test allows to");
			draw_font(1, x, y += 8, 255, 255, 255, "time that delay manually.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "Press 'X' to switch the");
			draw_font(1, x, y += 8, 255, 255, 255, "resolution");
			draw_font(1, x, y += 8, 255, 255, 255, "you are able to see the screen");
			draw_font(1, x, y += 8, 255, 255, 255, "back in your display.");
			break;
		case HELP_VIDEO:
			center_title("VIDEO OPTIONS");
			draw_font(1, x, y += 8, 255, 255, 255, "Here you can enable 480i mode");
			draw_font(1, x, y += 8, 255, 255, 255, "for the whole test suite.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "For PAL consoles, you can also");
			draw_font(1, x, y += 8, 255, 255, 255, "enable full 240p, instead of");
			draw_font(1, x, y += 8, 255, 255, 255, "224p.");
			break;
		case HELP_AUDIOSYNC:
			center_title("AUDIO SYNC");
			draw_font(1, x, y += 8, 255, 255, 255, "This test flashes the whole");
			draw_font(1, x, y += 8, 255, 255, 255, "screen white for 1 frames,");
			draw_font(1, x, y += 8, 255, 255, 255, "along with a 1khz test tone.");
			//y += 8; Need to be tested
			//draw_font(1, x, y += 8, 255, 255, 255, "You can verify the sync between");
			//draw_font(1, x, y += 8, 255, 255, 255, "audio and video with recording");
			//draw_font(1, x, y += 8, 255, 255, 255, "equipment or specialized");
			//draw_font(1, x, y += 8, 255, 255, 255, "hardware.");
			y += 8;
			draw_font(1, x, y += 8, 255, 255, 255, "Press 'X' to start/stop the test.");
			break;
		}

		draw_list();
		}
	}
}
