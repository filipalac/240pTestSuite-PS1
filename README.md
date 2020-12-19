240p Test Suite
===============

The [240p test suite] is a homebrew software suite for video game
consoles developed to help in the evaluation of upscalers, upscan
converters and line doublers.

It has tests designed with the processing of 240p signals in mind,
although when possible it includes other video modes and specific
tests for them.  These have been tested with video processors on
real hardware and a variety of displays, including CRTs and Arcade
monitors via RGB.

As a secondary target, the suite aims to provide tools for
calibrating colors, black and white levels for specific console
outputs and setups.

This is free software, with full source code available under the GPL.

[240p test suite]: http://junkerhq.net/xrgb/index.php/240p_test_suite

To use the test suite download release from github and burn .cue/.bin to CD.
There are 2 versions, one for real console which stop cd drive and
second one for emulators which doesn't(I got black screen in some emulators).
Both releases are fixed with cdmage because mkpsxiso from psxsdk
doesn't generate image correctly which may cause problems for some emulators.
You need to have modchiped psx or use swap method.
To compile suite you need to install [PSXSDK].


Contributors
------------
* Concept: Artemio Urbina [@Artemio]
* Code: Filip Aláč
* Main menu graphics: Asher
* PSXSDK: Nextvolume

* Advisor: Fudoh
* Extra patterns and collaboration: Konsolkongen & [shmups] regulars


[@Artemio]: https://twitter.com/Artemio
[shmups]: http://shmups.system11.org/
[PSXSDK:]: https://github.com/filipalac/psxsdk

Copyright 2011-2016 Artemio Urbina
Copyright 2017-2018 Filip Aláč

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
