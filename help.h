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

#pragma once

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

void draw_help(int option);
