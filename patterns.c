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
#include<psxgpu.h>

#include"240p.h"
#include"help.h"
#include"font.h"
#include"textures.h"

#define YTOP224 (y_res == 224 ? 8 : 0)
#define SCALE_TO_256 (x_res == 256 ? 3276 : 0)

void pluge()
{
	GsImage image;
	GsSprite sprite;
	
	upload_sprite(&image, &sprite, &pluge_array);

	while (1) {
		if (display_is_old) {
		flip_buffer();
		GsSortCls(0, 0, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_PLUGE);
			break;
		}

		sprite.w = 255;
		sprite.scalex = SCALE_TO_256;
		sprite.x = 0;
		sprite.tpage = 5;
		GsSortSprite(&sprite);
		sprite.w = 64;
		sprite.x = x_res == 256 ? 203 : 255;
		sprite.tpage = 6;
		GsSortSprite(&sprite);

		draw_list();
		}
	}
}

void color_bars()
{

	char grid = 0;

	GsImage image;
	GsSprite color,colorgrid;

	upload_sprite(&image, &color, &color_array);
	if (x_res == 256)
		upload_sprite(&image, &colorgrid, &colorgridw256_array);
	else
		upload_sprite(&image, &colorgrid, &colorgrid_array);

	while (1) {
		if (display_is_old) {
		flip_buffer();
		GsSortCls(0, 0, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_COLORS);
			break;
		case PAD_CROSS:
			grid = !grid;
			break;
		}

		if (!grid) {
			color.w = 255;
			color.scalex = SCALE_TO_256;
			color.x = 0;
			color.tpage = 5;
			GsSortSprite(&color);
			color.w = 64;
			color.x = x_res == 256 ? 203 : 255;
			color.tpage = 7;
			GsSortSprite(&color);
		} else {
			colorgrid.w = 256;
			colorgrid.x = 0;
			colorgrid.tpage = 10;
			GsSortSprite(&colorgrid);
			if (x_res != 256) {
				colorgrid.w = 64;
				colorgrid.x = 256;
				colorgrid.tpage = 12;
				GsSortSprite(&colorgrid);
			}
		}

		draw_list();
		}
	}
}

void smpte_color_bars()
{
	int frame_time = 90;
	char limited = 0;

	GsImage image;
	GsSprite sprite100, sprite75;

	if (GsScreenM == VMODE_NTSC) {
		upload_sprite(&image, &sprite100, &SMPTE100_array);
		upload_sprite(&image, &sprite75, &SMPTE75_array);
	} else {
		upload_sprite(&image, &sprite100, &EBU100_array);
		upload_sprite(&image, &sprite75, &EBU75_array);
	}

	while (1) {
		if (display_is_old) {
		flip_buffer();
		GsSortCls(0, 0, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_SMPTE);
			break;
		case PAD_CROSS:
			frame_time = 90;
			limited = !limited;
			break;
		}

		if (!limited) {
			sprite100.tpage = 5;
			sprite100.x = 0;
			sprite100.scalex = SCALE_TO_256;
			sprite100.h = x_res == 256 ? 255 : 256;
			sprite100.w = x_res == 256 ? 255 : 256;
			GsSortSprite(&sprite100);
			sprite100.tpage = 6;
			sprite100.x = x_res == 256 ? 203 : 256;
			sprite100.scalex = 0;
			sprite100.w = 64;
			GsSortSprite(&sprite100);
		} else {
			sprite75.tpage = 10;
			sprite75.x = 0;
			sprite75.scalex = SCALE_TO_256;
			sprite75.h = x_res == 256 ? 255 : 256;
			sprite75.w = x_res == 256 ? 255 : 256;
			GsSortSprite(&sprite75);
			sprite75.tpage = 11;
			sprite75.scalex = 0;
			sprite75.x = x_res == 256 ? 203 : 256;
			sprite75.w = 64;
			GsSortSprite(&sprite75);
		}

		if (frame_time > 0) {
			draw_font(1, x_res == 256 ? 192 : 260, 20, 255, 255, 255, "%s", limited ? "75 %" : "100 %");
			frame_time--;
		}

		draw_list();
		}
	} 
}

void color_bars_with_gray_reference()
{
	GsImage image;
	GsSprite sprite;

	upload_sprite(&image, &sprite, &colorgray_array);

	while (1) {
		if (display_is_old) {
		flip_buffer();
		GsSortCls(192, 192, 192);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_601CB);
			break;
		}

		sprite.w = x_res == 256 ? 255 : 256;
		sprite.scalex = SCALE_TO_256;
		sprite.x = 0;
		sprite.tpage = 5;
		GsSortSprite(&sprite);
		sprite.w = 64;
		sprite.x = x_res == 256 ? 203 : 256;
		sprite.tpage = 6;
		GsSortSprite(&sprite);

		draw_list();
		}
	} 
}

void color_bleed_check()
{
	char chk = 0;

	GsImage image;
	GsSprite sprite, spritechk;

	upload_sprite(&image, &sprite, &colorbleed_array);
	upload_sprite(&image, &spritechk, &colorbleedchk_array);

	while (1) {
		if (display_is_old) {
		flip_buffer();
		GsSortCls(0, 0, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
			break;
		case PAD_START:
			draw_help(HELP_BLEED);
			break;
		case PAD_CROSS:
			chk = !chk;
			break;
		}

		if (!chk) {
			sprite.w = x_res == 256 ? 240 : 256;
			sprite.x = 0;
			sprite.tpage = 5;
			GsSortSprite(&sprite);
			if (x_res != 256) {
				sprite.w = 64;
				sprite.x = 256;
				sprite.tpage = 6;
				GsSortSprite(&sprite);
			}
		} else {
			spritechk.w = x_res == 256 ? 240: 256;
			spritechk.x = 0;
			spritechk.tpage = 10;
			GsSortSprite(&spritechk);
			if (x_res != 256) {
				spritechk.w = 64;
				spritechk.x = 256;
				spritechk.tpage = 11;
				GsSortSprite(&spritechk);
			}
		}

		draw_list();
		}
	} 
}

void grid()
{
	char whitebackground = 0;
	char gridsel = 0;
	int frame_time = 90;

	GsImage image;
	GsSprite sprite224, sprite240, sprite256;

	if (x_res == 256) {
		upload_sprite(&image, &sprite224, &gridw256224_array);
		upload_sprite(&image, &sprite240, &gridw256240_array);
		if (GsScreenM == VMODE_PAL)
			upload_sprite(&image, &sprite256, &gridw256256_array);
	} else {
		upload_sprite(&image, &sprite224, &grid224_array);
		upload_sprite(&image, &sprite240, &grid240_array);
		if (GsScreenM == VMODE_PAL)
			upload_sprite(&image, &sprite256, &grid256_array);
	}

	GsRectangle background;
	background.r = background.g = background.b = 66;
	background.x = background.y = 0;
	background.w = x_res; background.h = y_res;
	background.attribute = 0;

	while (1) {
		if (display_is_old) {
		flip_buffer();
		GsSortCls(0, 0, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_GRID);
			break;
		case PAD_CROSS:
			gridsel++;
			if (gridsel > (y_res % 224 / 16))
				gridsel = 0;
			frame_time = 90;
			break;
		case PAD_SQUARE:
			whitebackground = !whitebackground;
			break;
		}

		if (whitebackground)
			GsSortRectangle(&background);

		switch (gridsel) {
		case 0:
			sprite224.y = background.y = 8;
			sprite224.h = background.h = 224;
			sprite224.w = 256;
			sprite224.x = 0;
			sprite224.tpage = 5;
			GsSortSprite(&sprite224);
			sprite224.w = 64;
			sprite224.x = 256;
			sprite224.tpage = 6;
			GsSortSprite(&sprite224);
			break;
		case 1:
			sprite240.y = background.y = 0;
			sprite240.h = background.h = 240;
			sprite240.w = 256;
			sprite240.x = 0;
			sprite240.tpage = 7;
			GsSortSprite(&sprite240);
			sprite240.w = 64;
			sprite240.x = 256;
			sprite240.tpage = 8;
			GsSortSprite(&sprite240);
			break;
		case 2:
			sprite256.y = background.y = 0;
			sprite256.h = background.h = 256;
			sprite256.w = 256;
			sprite256.x = 0;
			sprite256.tpage = 9;
			GsSortSprite(&sprite256);
			sprite256.w = 64;
			sprite256.x = 256;
			sprite256.tpage = 10;
			GsSortSprite(&sprite256);
			break;
		}
		if (frame_time > 0) {
			draw_font(1, x_res == 256 ? 192 : 230, 20, 0, 255, 0, "%dx%d", x_res, (224 + gridsel * 16));
	       		frame_time--;
		}

		draw_list();
		}
	}
}

void linearity()
{
	char show_grid = 0;
	char show_griddot = 0;
	char linsel = (GsScreenM == VMODE_PAL && y_res >= 240) ? 2 : 0;
	int frame_time = 90;

	GsImage image;
	GsSprite sprite, sprite224, sprite240pal, grid, griddot;

	if (x_res > 256) {
		upload_sprite(&image, &sprite224, &linearity224_array);
		if (y_res >= 240) {
			upload_sprite(&image, &sprite, &linearity_array);
			upload_sprite(&image, &sprite240pal, &linearity240pal_array);
		}
	} else {
		upload_sprite(&image, &sprite224, &linearityw256224_array);
		if (y_res > 224)
			upload_sprite(&image, &sprite240pal, &linearityw256224pal_array);
	}

	upload_sprite(&image, &grid, &lingrid_array);
	upload_sprite(&image, &griddot, &linearitygriddot_array);

	while (1) {
		if (display_is_old) {
		flip_buffer();
		GsSortCls(0, 0, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_LINEARITY);
			break;
		case PAD_CIRCLE:
			show_grid = !show_grid;
			show_griddot = 0;
			break;
		case PAD_SQUARE:
			show_griddot = !show_griddot;
			show_grid = 0;
			break;
		case PAD_CROSS:
			frame_time = 90;
			linsel++;
			if (linsel > (y_res / 225 * 2))
				linsel = 0;
			if (x_res < 320 && linsel == 1)
				linsel = 2;
			break;
		}

		if (show_grid) {
			grid.y = linsel == 0  ? 8 : 0;
			grid.h =  linsel == 0  ? 224 : 240;
			grid.x = 0;
			GsSortSprite(&grid);
			grid.x = 160;
			GsSortSprite(&grid);
		}
		if (show_griddot) {
			int x, y;
			for (y = 0; y != (linsel == 0 ? 28 : 30); y++) {
				for (x = 0; x != 40; x++) {
					griddot.x = x * 8;
					GsSortSprite(&griddot);
				}
				griddot.y = y * 8 + (!linsel  ? 8 : 0);
				GsSortSprite(&griddot);
			}
		}
		
		switch (linsel) {
		case 0:
			sprite224.w = 256;
			sprite224.x = 0;
			sprite224.y = 8;
			sprite224.tpage = 7;
			GsSortSprite(&sprite224);
			sprite224.w = 64;
			sprite224.x = 256;
			sprite224.tpage = 8;
			GsSortSprite(&sprite224);
			if (frame_time > 0) {
				draw_font(1, x_res == 256 ? 192 : 230, 20, 0, 255, 0, "%dx224 NTSC", x_res);
		       		frame_time--;
			}
			break;
		case 1:
			sprite.w = 256;
			sprite.x = 0;
			sprite.tpage = 5;
			GsSortSprite(&sprite);
			sprite.w = 64;
			sprite.x = 256;
			sprite.tpage = 6;
			GsSortSprite(&sprite);
			if (frame_time > 0) {
				draw_font(1, x_res == 256 ? 192 : 230, 20, 0, 255, 0, "%dx240 NTSC", x_res);
		       		frame_time--;
			}
			break;
		case 2:
			sprite240pal.w = 256;
			sprite240pal.x = 0;
			sprite240pal.y = x_res == 256 ? 8 : 0; // If x_res == 256 image is only 224p
			sprite240pal.tpage = 9;
			GsSortSprite(&sprite240pal);
			sprite240pal.w = 64;
			sprite240pal.x = 256;
			sprite240pal.tpage = 10;
			GsSortSprite(&sprite240pal);
			if (frame_time > 0) {
				draw_font(1, x_res == 256 ? 192 : 230, 20, 0, 255, 0, "%dx%s PAL", x_res, x_res == 256 ? "224" : "240");
		       		frame_time--;
			}
			break;
		}

		draw_list();
		}
	}  
} 

void gray_ramp()
{
	GsImage image;
	GsSprite sprite;

	upload_sprite(&image, &sprite, &grayramp_array);

	while (1) {
		if (display_is_old) {
		flip_buffer();
		GsSortCls(0, 0, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_GRAY);
			break;
		}

		sprite.w = 255 + x_res / 257;
		sprite.h = 255 + x_res / 257;
		sprite.scalex = SCALE_TO_256;
		sprite.y = YTOP224;
		sprite.x = 0;
		sprite.tpage = 5;
		GsSortSprite(&sprite);
		sprite.w = 64;
		sprite.y = YTOP224;
		sprite.x = x_res == 256 ? 203 : 255;
		sprite.tpage = 7;
		GsSortSprite(&sprite);

		draw_list();
		}
	}
}

void white_and_rgb_screens()
{
	int cnt = 1;
	int rgb_cnt = 1;
	unsigned char *current = 0;
	unsigned char r, g, b = 1;

	GsRectangle background;
	background.r = background.g = background.b = 249;
	background.x = 0; background.y = 0;
	background.w = x_res; background.h = y_res;
	background.attribute = 0;

	GsRectangle box;
	box.r = box.g = box.b = 1;
	box.x = x_res - 160; box.y = 13;
	box.w = 140; box.h = 8;
	box.attribute = ENABLE_TRANS | TRANS_MODE(0);

	while (1) {
		if (display_is_old) {
		flip_buffer();
		GsSortCls(r, g, b);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_WHITE);
			break;
		case PAD_CROSS:
			if (cnt == 9)
				cnt = 1;
			else
				cnt++;
			break;
		case PAD_CIRCLE:
			if (cnt == 8)
				cnt = 9;
			else 
				cnt = 8;
			break;
		}

		switch (cnt) {
		case 1:
			r = g = b = 249;
			break;
		case 2:
			r = g = b = 1;
			break;
		case 3:
			r = g = b = 17; //IRE 7.5
			break;
		case 4:
			r = 249; g = 1; b = 1;
			break;
		case 5:
			r = 1; g = 249; b = 1;
			break;
		case 6:
			r = 1; g = 1; b = 249;
			break;
		case 7:
			cnt = 1;
			break;
		case 8:
			GsSortRectangle(&box);
			draw_menu_font(0, rgb_cnt, 1, x_res - 150, 13, "R:%d", r >> 3);
			draw_menu_font(0, rgb_cnt, 2, x_res - 100, 13, "G:%d", g >> 3);
			draw_menu_font(0, rgb_cnt, 3, x_res - 50, 13, "B:%d", b >> 3);

			if (input & PAD_RIGHT && rgb_cnt != 3)
				rgb_cnt++;
			if (input & PAD_LEFT && rgb_cnt != 1)
				rgb_cnt--;

			switch (rgb_cnt) {
			case 1:
				current = &r;
				break;
			case 2:
				current = &g;
				break;
			case 3:
				current = &b;
				break;
			}

			switch (input) {
			case PAD_UP:
				if (*current <= 241)
					(*current) += 8; //1
				break;
			case PAD_R1:
				if (*current <= 209)
					(*current) += 40; //5
				break;
			case PAD_R2:
				if (*current <= 169)
					(*current) += 80; //10
				break;
			case PAD_DOWN:
				if (*current >= 9)
					(*current) -= 8;
				break;
			case PAD_L1:
				if (*current >= 41)
					(*current) -= 40;
				break;
			case PAD_L2:
				if (*current >= 81)
					(*current) -= 80;
				break;
			}
		}
				
		draw_list();
		}
	}

}

void sharpness()
{
	int frame_time = 90;
	char sharpsel = y_res >= 240 ? 0 : 1;

	GsImage image;
	GsSprite sprite, sprite224;

	if (x_res == 256)
		upload_sprite(&image, &sprite224, &sharp256224_array);
	else
		upload_sprite(&image, &sprite224, &sharpness224_array);

	if (y_res >= 240) {
		upload_sprite(&image, &sprite, &sharpness_array);
		if (x_res == 256)
			upload_sprite(&image, &sprite, &sharp256240_array);
	}


	while (1) {
		if (display_is_old) {
		flip_buffer();
		GsSortCls(0, 0, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_SHARPNESS);
			break;
		case PAD_CROSS:
			if (y_res >= 240) {
				sharpsel = !sharpsel;
				frame_time = 90;
			}
			break;
		}

		if (!sharpsel) {
			sprite.w = 256;
			sprite.x = 0;
			sprite.tpage = 5;
			GsSortSprite(&sprite);
			sprite.w = 64;
			sprite.x = 256;
			sprite.tpage = 6;
			GsSortSprite(&sprite);
		} else {
			sprite224.y = 8;
			sprite224.w = 256;
			sprite224.x = 0;
			sprite224.tpage = 7;
			GsSortSprite(&sprite224);
			sprite224.w = 64;
			sprite224.x = 256;
			sprite224.tpage = 8;
			GsSortSprite(&sprite224);
		}

		if (frame_time > 0) {
			draw_font(1, x_res == 256 ? 192 : 230, 20, 0, 255, 0, "%dx%s", x_res, sharpsel ? "224" : "240");
		       	frame_time--;
		}

		draw_list();
		}
	}
}

void convergence()
{
	int cnt = 0;

	GsImage image;
	GsSprite sprite;

	upload_sprite(&image, &sprite, &convergence_array);
	sprite.r = 128; sprite.g = 128; sprite.b = 128;

	while (1) {
		if (display_is_old) {
		flip_buffer();
		GsSortCls(0, 0, 0);

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_CROSS:
			cnt++;
			if (cnt == 7)
				cnt = 0;
			break;
		}

		switch (cnt) {
		case 0: sprite.r = 128; sprite.g = 128; sprite.b = 128;
			break;
		case 1: sprite.r = 0; sprite.g = 128; sprite.b = 128;
			break;
		case 2: sprite.r = 128; sprite.g = 128; sprite.b = 0;
			break;
		case 3: sprite.r = 128; sprite.g = 0; sprite.b = 128;
			break;
		case 4: sprite.r = 128; sprite.g = 0; sprite.b = 0;
			break;
		case 5: sprite.r = 0; sprite.g = 128; sprite.b = 0;
			break;
		case 6: sprite.r = 0; sprite.g = 0; sprite.b = 128;
			break;
		}

		sprite.w = 256;
		sprite.x = 0;
		sprite.tpage = 5;
		GsSortSprite(&sprite);
		sprite.w = 64;
		sprite.x = 256;
		sprite.tpage = 6;
		GsSortSprite(&sprite);

		draw_list();
		}
	}
}

void overscan()
{
	int cnt = 1;

	GsRectangle box;
	box.r = box.g = box.b = 140;
	box.x = 0;
	box.y = y_res == 224 ? 8 : 0;
	box.w = x_res; box.h = y_res;
	box.attribute = 0;

	while (1) {
		if (display_is_old) {
		flip_buffer();
		GsSortCls(239, 239, 239);

		GsSortRectangle(&box);

		draw_menu_font(1, cnt, 1, x_res / 2.6, 114, "Top: %d pixels", box.y - YTOP224);
		draw_menu_font(1, cnt, 2, x_res / 2.6, 122, "Bottom: %d pixels", (y_res - box.h - box.y) + YTOP224);
		draw_menu_font(1, cnt, 3, x_res / 2.6, 130, "Left: %d pixels", box.x);
		draw_menu_font(1, cnt, 4, x_res / 2.6, 138, "Right: %d pixels", (x_res - box.w - box.x));

		switch (input_tap()) {
		case PAD_TRIANGLE:
			return;
		case PAD_START:
			draw_help(HELP_OVERSCAN);
			break;
		case PAD_CROSS:
			box.x = 0;
			box.y = YTOP224;
			box.w = x_res;
			box.h = y_res;
			break;
		case PAD_UP:
			if (cnt != 1)
				cnt--;
			break;
		case PAD_DOWN:
			if (cnt != 4)
				cnt++;
			break;
		case PAD_RIGHT:
			if (cnt == 1 && box.h != 1) {
				box.y++;
				box.h--;
			}
			else if (cnt == 2 && box.h != 1) {
				box.h--;
			}
			else if (cnt == 3 && box.w != 1) {
				box.x++;
				box.w--;
			}
			else if (cnt == 4 && box.w != 1) {
				box.w--;
			}
			break;
		case PAD_LEFT:
			if (cnt == 1 && box.y - YTOP224 != 0) {
				box.y--;
				box.h++;
			}
			else if (cnt == 2 && (y_res - box.h - box.y + YTOP224) != 0) {
				box.h++;
			}
			else if (cnt == 3 && box.x != 0) {
				box.x--;
				box.w++;
			}
			else if (cnt == 4 && (x_res - box.w - box.x) != 0) {
				box.w++;
			}
			break;
		}

		draw_list();
		}
	}
}  
