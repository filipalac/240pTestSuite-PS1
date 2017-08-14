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

volatile int display_is_old;

unsigned short input;

unsigned short x_res,y_res; //not using GsScreenH because it can be only 240/480

void load_background();
void draw_background();
void upload_sprite(GsImage *image, GsSprite *sprite, void *compressed_buffer);//decompress and upload image as sprite to vram
unsigned short input_tap(); //is returning global variable input 
void flip_buffer(); //double buffer
